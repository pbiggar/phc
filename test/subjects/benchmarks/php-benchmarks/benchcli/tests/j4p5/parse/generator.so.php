<?php

/*
File: metascanner.so.php
License: GPL
Purpose: Scanner for reading parser grammars.

There is a parser generator that uses this scanner to read files containing
grammar production rules and generate the resulting tables useful to the
parser class. Assuming you have such tables already generated, you will not
need to include this file.
*/

$GLOBALS['func_def'] = '';

function mk_action($code) {
  return define_function( '&$type, &$text, $match, &$state, &$context', $code);
}
/* create_function + caching of identical functions + serialization support */
function define_function( $args, $code) {
  static $counter;
  static $cache = array();
  $s = $args."--".$code;
  if (!isset($cache[$s])) {
    $counter ++;
    $name = "__lambda_$counter";
    $php = "function $name ($args) {\n$code\n}\n";
    eval( $php );
    $GLOBALS['func_def'] .= $php;
    $cache[$s] = $name;
  }
  return $cache[$s];
}

class grammar_scanner extends preg_scanner {
	function __construct() {
		parent::__construct(0);
		$oob = mk_action('$context++; $state="code";');
		$ocb = mk_action('$context--; if ($context <= 0) $state = "INITIAL";');
		
		$ob = preg_pattern('({)', 'openbrace', 0, $oob);
		{
		$this->add_state('INITIAL', array(
			# regex type ignore next_state action
			preg_pattern('(\s+)', 'whitespace', 1, ''),
			preg_pattern('(#[^\n]*)', 'comment', 1, ''),
			preg_pattern('(EPSILON)', 'epsilon', 0, ''),
			preg_pattern("(c\W|\w+'*)", 'token', 0, ''),
			preg_pattern('(:)', 'colon', 0, ''),
			preg_pattern('(\|)', 'union', 0, ''),
			preg_pattern('(\*)', 'star', 0, ''),
			preg_pattern('(\?)', 'hook', 0, ''),
			preg_pattern('(\+)', 'plus', 0, ''),
			preg_pattern('(\()', 'leftparen', 0, ''),
			preg_pattern('(\))', 'rightparen', 0, ''),
			$ob,
		));
		}
		{
		$this->add_state('code', array(
			# regex type ignore next_state action
			preg_pattern('(\'(?:\\.|[^\'])*\')', 'sstring', 0, ''),
			preg_pattern('("(?:\\.|[^"])*")', 'dstring', 0, ''),
			preg_pattern('((?m)(?:#|//).*?$)', 'linecomment', 0, ''),
			preg_pattern('(/\*.*?\*/)', 'blockcomment', 0, ''),
			$ob,
			preg_pattern('(})', 'closebrace', 0, $ocb),
			preg_pattern('([^\'"#/}{]+|.)', 'php', 0, ''),
		));
		}
	}
}

/* math/recursive.so.php */

function recursive_closure($callable, $queue) {
	bug_unless(is_callable($callable));
	bug_unless(is_array($queue));
	$seen = array();
	while (!empty($queue)) {
		$subject = array_shift($queue);
		if (isset($seen[$subject])) continue;
		$seen[$subject] = true;
		foreach (call_user_func($callable, $subject) as $element) $queue[] = $element;
	}
	return array_keys($seen);
}


/*
File: generator.so.php
License: GPL
Purpose: Generates LR parser tables and scanners.

If you're persisting your parser tables in a separate file, then you don't need
to include this code except in the program that makes parser tables. It is
probably a good idea to do such persistence
*/

function gen_mark() {
	static $k = 0;
	return $k++;
}

class recursive_descent_parser {
	private $peek;
	protected $lex;
	function __construct($lex) {
		$this->lex = $lex;
		$this->peek = null;
	}
	function parse_terminal($type) {
		$t = $this->next();
		if ($t->type != $type) $this->bomb($type, $t);
		return $t->text;
	}
	
	function bomb($wanted, $got) {
		echo "Grammar Syntax Error - wanted $wanted. Got:<br/>\n";
		pr($got);
		$this->lex->report_error();
		throw new parse_error("Grammar Syntax Error - wanted $wanted. Got: $got->type");
	}
	
	function can_parse_terminal($type) {
		return $this->peek() == $type;
	}
	
	function peek() {
		if ($this->peek === null) $this->peek = $this->lex->next();
		return $this->peek->type;
	}
	function next() {
		if ($this->peek === null) return $this->lex->next();
		else {
			$peek = $this->peek;
			$this->peek = null;
			return $peek;
		}
	}
}

class grammar_parser extends recursive_descent_parser {
	function __construct() {
		parent::__construct(new grammar_scanner());
	}
	
	function parse_file($name) {
		$this->lex->start(file_get_contents($name));
		return $this->parse_grammar();
	}
	
	function parse_grammar() {
		$g = new grammar();
		while ($this->can_parse_production()) {
			$p = $this->parse_production();
			$g->add($p);
		}
		return $g;
	}
	
	function parse_production() {
		$head = $this->parse_terminal('token');
		$this->parse_terminal('colon');
		$body = $this->parse_body();
		$p = new production($head);
		$p->add($body);
		while ($this->can_parse_terminal('union')) {
			$this->parse_terminal('union');
			$p->add($this->parse_body());
		}
		return $p;
	}
	
	function can_parse_production() {
		# Cheesy - we peek for a token.
		return $this->can_parse_terminal('token');
	}
	
	function parse_body() {
		$r = $this->parse_regex();
		$a = $this->parse_action();
		return new production_body($r, $a);
	}
	
	function parse_action() {
		# startcode:
		$this->parse_terminal('openbrace');
		# action, given startcode above:
		$code = $this->parse_code();
		$this->parse_terminal('closebrace');
		return $code;
	}
	
	function parse_code() {
		$code = '';
		while (1) switch ($this->peek()) {
			case 'openbrace':
			$this->parse_terminal('openbrace');
			$inside = $this->parse_code();
			$this->parse_terminal('closebrace');
			$code .= "{" . $inside . "}"; 
			break;
			
			case 'php':
			case 'sstring':
			case 'dstring':
			case 'linecomment':
			case 'blockcomment':
			$t = $this->next();
			$code .= $t->text;
			break;
			
			default:
			return $code;
		}
	}
	
	function parse_regex() {
		$t = $this->parse_term();
		if (!$this->can_parse_term()) return $t;
		$them = array($t);
		while ($this->can_parse_term()) {
			$them[] = $this->parse_term();
		}
		return nfa_concat($them);
	}
	
	function parse_term() {
		$f = $this->parse_factor();
		switch ($this->peek()) {
			case 'star':
			$this->next();
			$f->kleene();
			break;
			
			case 'plus':
			$this->next();
			$f->plus();
			break;
			
			case 'hook':
			$this->next();
			$f->hook();
			break;
		}
		return $f;
	}
	
	function can_parse_term() {
		return $this->can_parse_factor();
	}
	
	function can_parse_factor() {
		switch ($this->peek()) {
			case 'leftparen':
			case 'token':
			case 'epsilon':
			return true;
		}
		return false;
	}
	
	function parse_factor() {
		switch ($this->peek()) {
			case 'leftparen':
			$this->next();
			$a = $this->parse_alternates();
			$this->parse_terminal('rightparen');
			return $a;
			
			case 'token':
			$t = $this->parse_terminal('token');
			$n = new enfa(); $n->recognize($t); return $n;
			
			case 'epsilon':
			$t = $this->parse_terminal('epsilon');
			$n = new enfa(); $n->add_epsilon($n->initial, $n->final); return $n;
		}
		die('CFG/PG got stuck parsing factors.');
	}
	
	function parse_alternates() {
		$r = $this->parse_regex();
		if (!$this->can_parse_terminal('union')) return $r;
		$them = array($r);
		while ($this->can_parse_terminal('union')) {
			$this->next();
			$them[] = $this->parse_regex();
		}
		return nfa_union($them);
	}
	
}

class production_body {
	function production_body($nfa, $action) {
		$this->nfa = $nfa;
		$this->code = preg_replace('/{(\d+)}/', '$tokens[\\1]', $action);
	}
}

class production {
	function production($head) {
		$this->head = $head;
		$this->branches = array();
	}
	function add($body) {
		$this->branches[] = $body;
	}
	function determinize() {
		$them = array();
		foreach($this->branches as $branch) {
			$mark = gen_mark();
			$nfa = $branch->nfa;
			$this->code[$mark] = $branch->code;
			$nfa->mark[$nfa->final] = $mark;
			$them[] = $nfa;
		}
		$union = nfa_union($them);
		$this->dfa = $union->determinize();
		unset($this->branches);
	}
	function minimize() {
		$this->dfa = $this->dfa->minimize();
	}
}

class grammar {
	function __construct() {
		$this->rules = array();
	}
	function add($prod) {
		$head = $prod->head;
		if ($this->has_rule($head)) throw new Exception ("Already have a rule for $head.");
		$prod->determinize();
		$prod->minimize();
		$this->rules[$head] = $prod;
	}
	function has_rule($head) {
		return isset($this->rules[$head]);
	}
	
	function make_dpda() {
		$i = new intermediate_parser_form($this->rules);
		return $i->compose_program();
	}
}

abstract class parse_step {
	abstract function phrase();
	abstract function instruction();
}

class eat_step extends parse_step {
	function __construct($label) {
		$this->label = $label;
	}
	function phrase() {
		return "eat it and go to state ".$this->label;
	}
	function instruction() {
		return array('go', $this->label);
	}
}

class reduce_step extends parse_step {
	function __construct($mark) {
		$this->mark = $mark;
	}
	function phrase() {
		return "reduce via code block $this->mark";
	}
	function instruction() {
		return array('do', $this->mark);
	}
}

class fold_step extends parse_step {
	function __construct($mark, $dest) {
		$this->mark = $mark;
		$this->dest = $dest;
	}
	function phrase() {
		return "fold back to state $this->dest via code block $this->mark";
	}
	function instruction() {
		return array('fold', $this->mark, $this->dest);
	}
}

class push_step extends parse_step {
	function __construct($gamma, $after) {
		$this->gamma = $gamma;
		$this->after = $after;
	}
	function phrase() {
		return "push to state $this->gamma, returning to state $this->after";
	}
	function instruction() {
		return array('push', $this->gamma, $this->after);
	}
}

class if_state {
	function __construct($id, $start, $final, $mark, $tDelta, $nDelta) {
		$this->id = $id;
		$this->start = $start;
		$this->final = $final;
		$this->mark = $mark;
		$this->tDelta = $tDelta;
		$this->nDelta = $nDelta;
		$this->steps = array(); # [glyph => parser step]
	}
	function add_step($glyph, $step) {
		if (isset($this->steps[$glyph])) echo (
			"State $this->id thought that it should ".
			$this->steps[$glyph]->phrase().
			" in the presence of $glyph, but is instead being told to ".
			$step->phrase().
			".<br>\n"
		);
		$this->steps[$glyph] = $step;
	}
	function delta() {
		$delta = array();
		foreach ($this->steps as $glyph => $step) $delta[$glyph] = $step->instruction();
		return $delta;
	}
	function is_initial() { return $this->id == $this->start; }
	function set_default($step) { $this->add_step('[default]', $step); }
}
class if_head {
	function __construct($symbol, $start, $epsilon) {
		$this->symbol = $symbol; # Name of nonterminal
		$this->start = $start; # a state label
		$this->epsilon = $epsilon; # True if rule can recognize epsilon.
	}
}
class intermediate_parser_form {
	private $action, $head, $label, $Q;
	function __construct($rules) {
		$this->NT = array_keys($rules);
		$this->action = array(); # [mark => action]
		$this->head = array(); # [symbol => if_head]
		$this->symbol = array(); # [label => head]
		$this->Q = array(); # [label => if_state]
		foreach ($rules as $head => $prod) $this->add_rule($head, $prod);
		
		$this->epsilon_extend_heads();
		$this->compute_head_closures();
		$this->add_shifts_and_pushes();
		$this->add_pops_and_folds();
	}
	private function add_pops_and_folds() {
		// Final States:
		foreach ($this->Q as $q) if ($q->final) {
			$q->set_default(new reduce_step($q->mark));
			/*
			However, if the state is terminal to a left-recursive head,
			then also add "fold" rules: Replace the current stack frame
			with result of running the code, if the terminal matches
			the lt_close of NOT the current rule, but rather of the
			state AFTER that first transition.
			*/
			$start = $this->Q[$q->start];
			$symbol = $this->symbol[$q->id];
			$left_recursive = isset($start->nDelta[$symbol]);
			if ($left_recursive) {
				$dest = $start->nDelta[$symbol];
				$front = $this->token_eating_front($dest);
				# echo "TEF state $dest: ".implode(" ", $front)."<br>";
				foreach ($front as $label) {
					foreach ($this->Q[$label]->tDelta as $glyph => $not_important) {
						$q->add_step($glyph, new fold_step($q->mark, $dest));
					}
				}
			}
			/*
			This, then, is the only place that S/R conflicts could arise.
			I'll call them "fold/reduce" conflicts for now.
			
			FR conflicts can always be eliminated by adding variables to the
			grammar, but there should be another way:
			
			If the precidence of the next terminal is higher than
			the highest-precidence terminal scanned this stack
			frame, then push. If it's lower, then reduce. If it's
			the same, then look at the (current) token's
			associativity. Left-associative means fold.
			Right-associative means push.
			
			If rule branches did not allow regular expressions, then
			it would be possible to do all of these calculations
			up front.
			
			*/
		}
	}
	private function add_shifts_and_pushes() {
		foreach ($this->Q as $q) {
			foreach ($q->tDelta as $glyph => $label) $q->add_step($glyph, new eat_step($label));
			$qSym = $this->symbol[$q->id];
			foreach ($q->nDelta as $symbol => $label) {
				$head = $this->head[$symbol];
				$processing_self_recursion = ($qSym == $symbol);
				if ($q->is_initial() and $processing_self_recursion) {
					// We are dealing with left recursion.
					// Therefore, no steps are needed here.
					continue;
					// We can prove that mutual recursion gets caught later on.
				}
				if ($head->epsilon) {
					// There had better not be any other options, else
					// we have nondeterminism.
					$q->set_default(new push_step($symbol, $label));
					if ((count($q->nDelta) > 1) or count($q->tDelta)) {
						# throw new Exception("Epsilon Nondeterminism in ".$this->symbol[$q->id]." w.r.t. ".$head->symbol);
					}
				}
				else {
					foreach ($head->lt_close as $glyph) {
						$q->add_step($glyph, new push_step($symbol, $label));
					}
				}
			}
		}
	}
	
	private function epsilon_extend_heads() {
		/*
		The heads come in knowing if they match epsilon directly,
		but it takes work (done below) to tell if the empty string
		is in their language.
		*/
		do {
			$learned = false;
			foreach ($this->head as $head) if (!$head->epsilon) {
				foreach($this->epsilon_closure_for_state($head->start) as $label) {
					if ($this->Q[$label]->final) {
						$head->epsilon = true;
						$learned = true;
					}
				}
			}
		} while ($learned);
	}
	
	public function epsilon_for_state($label) {
		$epsilon = array();
		foreach($this->Q[$label]->nDelta as $glyph => $dest)
			if ($this->head[$glyph]->epsilon) $epsilon[$dest] = 1;
		return array_keys($epsilon);
	}
	public function eclose_of_pushes_from($label) {
		$pushes = array_keys($this->Q[$label]->nDelta);
		$out = array();
		foreach ($pushes as $symbol) $out = array_merge($out, $this->head[$symbol]->eclose);
		return $out;
	}
	private function token_eating_front($label) {
		$queue = $this->epsilon_closure_for_state($label);
		return recursive_closure(array($this, 'eclose_of_pushes_from'), $queue);
	}
	private function epsilon_closure_for_state($label) {
		return recursive_closure(array($this, 'epsilon_for_state'), array($label));
	}
	private static function add_deltas(&$set, $delta, $what) {
		foreach ($delta as $glyph=>$dest) {
			if (isset($set[$glyph])) throw new Exception("Epsilon Nondeterminism before $glyph while processing $what.");
			$set[$glyph] = $dest;
		}
	}
	private function compute_head_closures() {
		# Epsilon closure and level sets:
		foreach ($this->head as $head) {
			$head->eclose = $this->epsilon_closure_for_state($head->start);
			$t_set = array();
			$n_set = array();
			foreach ($head->eclose as $label) {
				$q = $this->Q[$label];
				intermediate_parser_form::add_deltas($t_set, $q->tDelta, "nonterminal $head->symbol");
				intermediate_parser_form::add_deltas($n_set, $q->nDelta, "nonterminal $head->symbol");
			}
			$head->t_set = $t_set;
			$head->n_set = $n_set;
		}
		# Leftmost terminal closure:
		foreach ($this->head as $head) $this->compute_lt_closure($head);
	}
	private function compute_lt_closure($head) {
		$closure = $head->t_set;
		$seen = array($head->symbol => true);
		$queue = array_keys($head->n_set);
		while (count($queue)) {
			$symbol = array_shift($queue);
			if (isset($seen[$symbol])) continue;
			$seen[$symbol] = true;
			$H = $this->head[$symbol];
			intermediate_parser_form::add_deltas($closure, $H->t_set, "LT closure for $head->symbol, looking at $H->symbol");
			$queue = array_merge($queue, array_keys($H->n_set));
		}
		$head->lt_close = array_keys($closure);
	}
	private function add_rule($head, $prod) {
		foreach($prod->code as $mark => $code) $this->action[$mark] = $code;
		$dfa = $prod->dfa;
		$start = $dfa->initial;
		$this->head[$head] = new if_head($head, $start, $dfa->final[$start]);
		foreach($dfa->states as $q) {
			$tDelta = array();
			$nDelta = array();
			foreach ($dfa->delta[$q] as $glyph => $label)
				if (in_array($glyph, $this->NT)) {
					$nDelta[$glyph] = $label;
				} else {
					$tDelta[$glyph] = $label;
				}
			$this->Q[$q] = new if_state(
				$q,
				$dfa->initial,
				$dfa->final[$q],
				$dfa->mark[$q],
				$tDelta,
				$nDelta
			);
			$this->symbol[$q] = $head;
		}
	}
	public function compose_program() {
		foreach ($this->action as $k => $body) {
		  $this->action[$k] = define_function( '$tokens', preg_replace('/{(\d+)}/', '$tokens[\\1]', $body));
		}
		return array(
			'start' => $this->symbol_start_states(),
			'delta' => $this->dpda_transition_function(),
			'action' => $this->action,
		);
	}
	private function dpda_transition_function() {
		$delta = array();
		foreach ($this->Q as $label => $q) $delta[$label] = $q->delta();
		return $delta;
	}
	private function symbol_start_states() {
		$start = array();
		foreach ($this->head as $symbol => $head) $start[$symbol] = $head->start;
		return $start;
	}
}


function generate_parser_from_file($filename) {
	$rdp = new grammar_parser();
	$g = $rdp->parse_file($filename);
	return $g->make_dpda();
}
function generate_scanner_from_file($filename, $init_context) {
	$metascanner = new metascanner();
	$metascanner->start(file_get_contents($filename));
	return scanner_parser()->parse('scanner', $metascanner)->scanner($init_context);
}
function location_of_scanner_grammar() {
	return dirname(__FILE__).'/metascanner.y';
}
function scanner_parser() {
	return new easy_parser(generate_parser_from_file(location_of_scanner_grammar()));
}
class metascanner extends preg_scanner {
	function __construct() {
		parent::__construct(0);
		/* Make some action functions */ {
		$ocb = mk_action('$context++; $state="code";');
		$ccb = mk_action('$context--; if ($context <= 0) $state = "rule";');
		$m1 = mk_action('$text = substr($text,1);');
		$m11 = mk_action('$text = substr($text,1,strlen($text)-2);');
		$go_rule = mk_action("\$state = 'rule';");
		$go_regex = mk_action("\$state = 'regex';");
		$test_reserved_word = mk_action("if (\$text=='ignore') \$type='ignore';");
		}
		/* Make the patterns */ {
		$nl = preg_pattern('([\n\r]+)', 'newline', 1, $go_regex);
		$cb = preg_pattern('(})', 'closebrace', 0, $go_rule);
		$ws = preg_pattern('(\s+)', 'whitespace', 1, '');
		$cm = preg_pattern('(#[^\n\r]*)', 'comment', 1, '');
		$id = preg_pattern('(\w+)', 'identifier', 0, $test_reserved_word);
		$dir = preg_pattern('(%(?:\w+))', 'directive', 0, $m1);
		$div = preg_pattern('(%%)', 'divider', 0, $go_regex);
		$scope_tag = preg_pattern('(\<(?:\w+)>)', 'scope_tag', 0, $m11);
		$ob = preg_pattern('(\{)', 'openbrace', 0, '');
		$regex = preg_pattern('(\S+)', 'regex', 0, $go_rule);
		$modifier = preg_pattern('(/(?:[misxU]+))', 'modifier', 0, $m1);
		$openbrace_rule = preg_pattern('({)', 'openbrace', 0, $ocb);
		}
		/* Set up the "code" subscanner */ {
		$this->add_state('code', array(
			# regex type ignore next_state action
			preg_pattern('(\'(?:\\.|[^\'])*\')', 'sstring', 0, ''),
			preg_pattern('("(?:\\.|[^"])*")', 'dstring', 0, ''),
			preg_pattern('((?m)(?:#|//).*?$)', 'linecomment', 0, ''),
			preg_pattern('(/\*.*?\*/)', 'blockcomment', 0, ''),
			$openbrace_rule,
			preg_pattern('(})', 'closebrace', 0, $ccb),
			preg_pattern('([^\'"#/}{]+|.)', 'php', 0, ''),
		));
		}
		/* Set up the rest of the scanner */ {
		$this->add_state('INITIAL', array(
			$dir, $div,
			$ws, $cm, $id,
		));
		$this->add_state('regex', array(
			$nl, $cb,
			$ws, $cm, $id,
			$scope_tag, $ob, $regex,
		));
		$this->add_state('rule', array(
			$nl, $cb,
			$ws, $cm, $id,
			$openbrace_rule,
			$modifier,
		));
		}
	}
	static function make_regex($expression, $flags) {
		#$c = metascanner::suitable_delimiter($expression);
		#return "$c$expression$c$flags";
		// use a form suitable for independent use AND grouping
		return "((?$flags)$expression)";
	}
	static function suitable_delimiter($expression) {
		foreach(array('/', '%', '#', '=', '!') as $c) {
			if (strpos($expression, $c) === false) return $c;
		}
		bug("Can't think of a suitable delimiter for expression: $expression");
	}
}
class preg_scanner_definition {
	function __construct($deflist) {
		$this->is = array();
		$this->pattern = array();
		$this->add_scope('s', 'INITIAL');
		foreach ($deflist as $def) {
			$type = array_shift($def);
			foreach ($def as $id) $this->add_scope($type, $id);
		}
	}
	function add_scope($type, $id) {
		if ($type=='s') $this->is[] = $id;
		$this->pattern[$id] = array();
	}
	function add_rule($scope_list, $rule) {
		foreach ($scope_list as $s) {
		  $this->pattern[$s][]=$rule;
		}
	}
	function add_rule_list($scope_list, $rule_list) {
		foreach ($rule_list as $rule) $this->add_rule($scope_list, $rule);
	}
	function add_common_rule($rule) {
		$this->add_rule($this->is, $rule);
	}
	function scanner($init_context) {
		return new preg_scanner($init_context, $this->pattern);
	}
}
