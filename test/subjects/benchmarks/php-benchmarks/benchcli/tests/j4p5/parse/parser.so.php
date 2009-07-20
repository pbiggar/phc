<?php

/* misc subset */

class Bug extends Exception {}
function bug_unless($assertion, $gripe='Bug found.') { if (!$assertion) throw new Bug($gripe); }
function span($class, $text, $title='') {
	$title = htmlspecialchars($title);
	if ($title) $extra = " title=\"$title\"";
	else $extra = '';
	echo "<span class=\"$class\"{$extra}>".$text."</span>\n";
}


/*
File: set.so.php
License: GPL
Purpose: We should really have a "set" data type. It's too useful.
*/

class set {
	function set($list=array()) { $this->data = array_count_values($list); }
	function has($item) { return isset($this->data[$item]); }
	function add($item) { $this->data[$item] = true; }
	function del($item) { unset($this->data[$item]); }
	function all() { return array_keys($this->data); }
	function one() { return key($this->data); }
	function count() { return count($this->data); }
}


/*
File: automata.so.php
License: GPL
Purpose: Contains various utilities for operating on finite automata.
*/

/*
First, we care about finality-extended e-NFAs. These are the basis for most
of the remainder of the systems.


Let it be noted early that pushdown automata will be constructed in terms
of (determinized) FAs which will interpret automata death as an indication
that the system needs to do something with the PDA stack.

We'll form the left-recursive closure of the available non-terminals following
the dieing state. If the next terminal is found in that set, then we also know
what to push and what state to enter. (Alternatively, we know the first step
in a recursive set of "pushes" which don't accept the terminal until the stack
looks the way it should.) Ambiguity here can be considered a bug in the
grammar specification. It makes the PDA non-deterministic. While it may be
possible to remove this non-determinism in some limited cases, I don't think
it's actually necessary.

We can, by this procedure, form a set of PDA rules for what to do with any
given terminal, assuming that the state transitions in the production DFA
call for a non-terminal. We thus have a special category of rule

There is another possibility: We are in a "final" state and we don't have
and edge or a push that accepts the next token. In this case, we assume that
we have recognized a complete production rule.

We call its associated code block, which is expected to return a syntax tree
node. Then, we pop the stack. The symbol on the stack should tell which
DFA to jump into and what state it will be in after recognizing a member of
the production known to the called DFA.

We can convert this entire idea to the normal definition of a DPDA by:
1. Selecting disjoint state labels for every DFA.
2. Keeping all DFA transitions in the same table.

That done, a stack symbol is merely also a state label.

*/

define("FA_NO_MARK", 99999);	# A sentinel value. Real marks should be less.

function gen_label() {
	# Won't return the same number twice. Note that we use state labels
	# for hash keys all over the place. To prevent PHP from doing the
	# wrong thing when we merge such hashes, we tack a letter on the
	# front of the labels.
	static $count = 0;
	$count ++;
	return 's'.$count;
}

class enfa {
	# Extended epsilon NFA in normal form.
	function enfa() {
		# $this->alphabet = array();	# We don't care
		$this->states = array();	# Contains a list of labels
		
		# These are hashes with state labels for keys:
		$this->delta = array();	# sub-hash from symbol to label-list
		$this->epsilon = array();	# label-list
		$this->mark = array();		# distinguishing mark
		
		# Now we can add the initial and final states:
		$this->initial = $this->add_state(gen_label());
		$this->final = $this->add_state(gen_label());
	}
	
	function eclose($label_list) {
		$states = array_count_values($label_list);
		$queue = array_keys($states);
		while (count($queue) > 0) {
			$s = array_shift($queue);
			foreach($this->epsilon[$s] as $t) if (!isset($states[$t])) {
				$states[$t] = true;
				$queue[] = $t;
			}
		}
		return array_keys($states);
	}
	
	function any_are_final($label_list) {
		return in_array($this->final, $label_list);
	}
	
	function best_mark($label_list) {
		$mark = FA_NO_MARK;
		foreach($label_list as $label) {
			$mark = min($mark, $this->mark[$label]);
		}
		return $mark;
	}
	
	function add_state($label) {
		if (isset($this->delta[$label])) {
			die ("Trying to add existing state to an NFA.");
		}
		$this->states[] = $label;
		$this->delta[$label] = array();
		$this->epsilon[$label] = array();
		$this->mark[$label] = FA_NO_MARK;
		return $label;
	}
	
	function add_epsilon($src, $dest) {
		$this->epsilon[$src][] = $dest;
	}
	
	function start_states() {
		return $this->eclose(array($this->initial));
	}
	
	function add_transition($src, $glyph, $dest) {
		$lst = & $this->delta[$src];
		if (empty($lst[$glyph])) $lst[$glyph] = array($dest);
		else $lst[$glyph][] = $dest;
	}
	
	function step($label_list, $glyph) {
		$out = array();
		foreach($label_list as $label) {
			if (isset($this->delta[$label][$glyph])) {
				$out = array_merge($out, $this->delta[$label][$glyph]);
			}
		}
		return $this->eclose($out);
	}
	
	function accepting($label_list) {
		# Return a set of those glyphs which will not kill the NFA.
		# Assume that any necessary epsilon closure is already done.
		
		# Note that there is a certain amount of unavoidable cleverness
		# in the algorithm. I don't care the values of $out, so it
		# doesn't matter that they happen also to be some arbitrary
		# transition lists.
		$out = array();
		foreach($label_list as $label) $out = array_merge($out, $this->delta[$label]);
		return array_keys($out);
	}
	
	/*
	Now that we have the basics down, I'd like some functions that
	let me make convenient modifications to an NFA. In particular,
	I would like to:
	
	1: Recognize a particular sequence of glyphs
	2: Accept the union of the current NFA and some other
	3: Perform the Kleene closure
	4: Similar for the common + and ? operators
	5: Accept the concatenation of this and some other NFA.
	
	Fortunately, these all boil down to a fairly simple set of steps.
	
	One slightly complicated part is that I'd also like to be able
	to carry these "distinguishing marks" through the system so that
	they can instruct the final PDA on which production matched.
	
	The other more complicated part is that these production rules are
	really transducers. Each rule has certain parts which must go into
	a parse tree node. It turns out that this is a relatively hard
	problem in the short run, and not necessary for a solution to the
	ultimate goal of getting PHP programs into a "tree-of-lists" structure.
	*/
	
	function recognize($glyph) {
		$this->add_transition($this->initial, $glyph, $this->final);
	}
	
	function plus() {
		# Recognize the current NFA one or more times:
		$this->add_epsilon($this->final, $this->initial);
	}
	
	function hook() {
		# Recognize the current NFA zero or one times:
		$this->add_epsilon($this->initial, $this->final);
	}
	
	function kleene() {
		# kleen-star closure over the current NFA:
		$this->hook();
		$this->plus();
	}
	
	function copy_in($nfa) {
		# Used by the union and concatenation operations.
		# Highly magical. Counts on a few things....
		foreach (array('states', 'delta', 'epsilon', 'mark') as $part) {
			$this->$part = array_merge($this->$part, $nfa->$part);
		}
	}
	
	function determinize() {
		# Now I can write the code that converts
		# an NFA into an equivalent DFA.
		
		$map = new state_set_labeler();
		$start = $this->start_states();
		$queue = array($start);
		
		$dfa = new dfa();
		$i = $map->label($start);
		$dfa->add_state($i);
		$dfa->initial = $i;
		$dfa->mark[$i] = $this->best_mark($start);
		
		while (count($queue) > 0) {
			$set = array_shift($queue);
			$label = $map->label($set);
			foreach ($this->accepting($set) as $glyph) {
				$dest = $this->step($set, $glyph);
				$dest_label = $map->label($dest);
				if (!$dfa->has_state($dest_label)) {
					$dfa->add_state($dest_label);
					$dfa->mark[$dest_label] = $this->best_mark($dest);
					$queue[] = $dest;
				}
				$dfa->add_transition($label, $glyph, $dest_label);
			}
			if ($this->any_are_final($set)) $dfa->final[$label] = true;
		}
		
		return $dfa;
	}
	
}

/*
Note that you should really throw away any NFA once you have
used one of the below functions on it, because the result will contain
indentically named state labels from the originals. We could fix this
apparent problem, but it would mean establishing a state-renaming function
for NFAs. Because I don't care to do this just now, and it's not important
anyway, I'm not doing it.
*/
function nfa_union($nfa_list) {
	$out = new enfa();
	foreach($nfa_list as $nfa) {
		$out->copy_in($nfa);
		$out->add_epsilon($out->initial, $nfa->initial);
		$out->add_epsilon($nfa->final, $out->final);
	}
	return $out;
}

function nfa_concat($nfa_list) {
	$out = new enfa();
	$last_state = $out->initial;
	foreach($nfa_list as $nfa) {
		$out->copy_in($nfa);
		$out->add_epsilon($last_state, $nfa->initial);
		$last_state = $nfa->final;
	}
	$out->add_epsilon($last_state, $out->final);
	return $out;
}



class dfa {
	/*
	A DFA has a simpler representation than that of an NFA.
	It also has a bit of a different interface.
	*/
	
	function dfa() {
		# $this->alphabet = array();	# We don't care
		$this->states = array();	# Contains a list of labels
		$this->initial = '';		# Set this later.
		
		# These are hashes with state labels for keys:
		$this->final = array();	# Just a bit for each state
		$this->delta = array();	# sub-hash from symbol to label
		$this->mark = array();		# distinguishing mark
	}
	
	function add_state($label) {
		if ($this->has_state($label)) {
			die ("Trying to add existing state to an DFA.");
		}
		$this->states[] = $label;
		$this->final[$label] = false;
		$this->delta[$label] = array();
		$this->mark[$label] = FA_NO_MARK;
		return $label;
	}
	
	function has_state($label) {
		return isset($this->delta[$label]);
	}
	
	function add_transition($src, $glyph, $dest) {
		$this->delta[$src][$glyph] = $dest;
	}
	
	function step($label, $glyph) {
		return @$this->delta[$label][$glyph];
	}
	
	function accepting($label) {
		return array_keys($this->delta[$label]);
	}
	
	function minimize() {
		/*
		We'll use the table-filling algorithm to find pairs of
		distinguishable states. When that algorithm is done, any states
		not distinguishable are equivalent. We'll return a new DFA.
		*/
		
		$map = $this->indistinguishable_state_map($this->table_fill());
		$dist = array();
		foreach($map as $p => $q) $dist[$q] = $q;
		
		$dfa = new dfa();
		foreach($dist as $p) $dfa->add_state($p);
		foreach($dist as $p) {
			foreach ($this->delta[$p] as $glyph => $q) $dfa->add_transition($p, $glyph, $map[$q]);
			$dfa->final[$p] = $this->final[$p];
			$dfa->mark[$p] = $this->mark[$p];
		}
		$dfa->initial = $map[$this->initial];
		
		return $dfa;
	}
	function indistinguishable_state_map($table) {
		# Assumes that $table is filled according to the table filling
		# algorithm.
		$map = array();
		$set = new set($this->states);
		while ($set->count()) {
			$p = $set->one();
			foreach($set->all() as $q) if (!$table->differ($p, $q)) {
				$map[$q] = $p;
				$set->del($q);
			}
		}
		return $map;
	}
	function table_fill() {
		/*
		We use a slight modification of the standard base case:
		Two states are automatically distinguishable if their marks
		differ.
		*/
		
		# Base Case:
		$table = new distinguishing_table();
		
		foreach($this->states as $s1) foreach($this->states as $s2) {
			if ($this->mark[$s1] != $this->mark[$s2]) $table->distinguish($s1, $s2);
		}
		
		# Induction: 
		do { /* nothing */ } while (!$this->filling_round($table));
		
		return $table;
	}
	
	function filling_round(&$table) {
		$done = true;
		
		foreach($this->states as $s1) foreach($this->states as $s2) {
			if ($s1 == $s2) continue;
			if (!$table->differ($s1, $s2)) {
				# Try to find a reason why the two states
				# differ. If so, then mark them different
				# and clear $done. Note that if the table
				# has no record of either state, then we
				# can't yet make a determination.
				$different = $this->compare_states($s1, $s2, $table);
				if ($different) {
					$table->distinguish($s1, $s2);
					$done = false;
					break;
				}
			}
		}
		# ("Done Round<br/>");
		return $done;
	}
	
	function compare_states($p, $q, $table) {
		$sigma = array_unique(array_merge($this->accepting($p), $this->accepting($q)));
		# "Comparing $p and $q - shared vocabulary: [ ".implode(' : ', $sigma)." ] - ");
		if ($p == $q) {
			# "Same State<br/>";
			return false;
		}
		
		foreach($sigma as $glyph) {
			$p1 = $this->step($p, $glyph);
			$q1 = $this->step($q, $glyph);
			if (!($p1 and $q1) or $table->differ($p1, $q1)) {
				# "<font color=green>They differ on $glyph - $p1/$q1<br/></font>");
				return true;
			}
		}
		
		# ("No difference found (yet)<br/>");
		return false;
	}
	
}

class distinguishing_table {
	function distinguishing_table() {
		$this->dist = array();
	}
	function key($s1, $s2) {
		$them = array($s1, $s2);
		sort($them);
		return implode("|", $them);
	}
	function distinguish($s1, $s2) {
		$key = $this->key($s1, $s2);
		$this->dist[$key] = true;
	}
	function differ($s1, $s2) {
		$key = $this->key($s1, $s2);
		return isset($this->dist[$key]);
	}
}

	
class state_set_labeler {
	function state_set_labeler() {
		$this->map=array();
	}
	function label($list) {
		sort($list);
		$key = implode(':', $list);
		if (empty($this->map[$key])) $this->map[$key] = gen_label();
		return $this->map[$key];
	}
}

/*
Now we can turn any production rule (head + set <body, action>) into a
DFA that recognizes the rule and can even invoke the correct action based
on a set of distinguishing marks. Any given final state in the DFA will
be marked with exactly the best matching action number.

A remaining problem is that of transduction. We would like to mark certain
glyphs with a symbol indicating that they cause the corresponding parse node
to go into the correct slot of a special parsing data structure which makes
for convenient reference within an action part of a rule. In other words,
we would really ideally like to turn NFTs into DFTs. It seems, at the moment,
that the transduction might still be non-deterministic. This not so much of
a problem as a big hassle.

However, if we always make the entire matched glyph list available in the form
of a list of parse nodes, then the action that corresponds to a given rule
branch is free to do fancy things.

All that remains is to build a PDA from a collection of DFAs.

These various DFAs will mostly have some transitions that are predicated on
non-terminal symbols in the CFG. We have to find all such transitions and deal
with them specially.
*/


/*
File: lex.so.php
License: GPL
Purpose: Provides a simple lexical analysis framework
Purpose: useful in so many ways. (Minilanguages are a
Purpose: fabulous way to save programming time.)
*/


class token {
	function __construct($type, $text, $start, $stop) {
		$this->type = $type;
		$this->text = $text;
		$this->start = $start;
		$this->stop = $stop;
	}
}
function null_token() { return new token('','','',''); }
// we want a serializable structure.
/*
class preg_pattern {
	function __construct($regex, $type, $ignore, $action) {
		$this->regex = $regex;
		$this->type = $type;
		$this->ignore = $ignore;
		$this->action = $action; # This is the name of a function.
	}
	function test($string) {
		if (preg_match($this->regex.'A', $string, $match)) return $match;
	}
}
*/
function preg_pattern($regex, $type, $ignore, $action) {
  return array($regex, $type, $ignore, $action);
}
function preg_pattern_test($pattern, $string) {
  if (preg_match($pattern.'A', $string, $match)) return $match;
}

class stream {
	function __construct($string) {
		$this->string = $string;
		$this->col = 0;
		$this->line = 1;
	}
	function consume($str) {
		$len = strlen($str);
		$this->string = substr($this->string, $len);
		$this->col += $len;
	}
	function test($pattern) {
		if ($match = preg_pattern_test($pattern,$this->string)) {
			$this->consume($match[0]);
			return $match;
		}
	}
	function default_rule() {
		if (!strlen($this->string)) return null_token();
		
		$start = $this->pos();
		$ch = $this->string[0];
		$this->consume($ch);
		$stop = $this->pos();
		return new token('c'.$ch, $ch, $start, $stop);
	}
	function pos() {
		return new point($this->line, $this->col);
	}
}
class point {
	function __construct($line, $col) {
		$this->line = $line;
		$this->col = $col;
	}
}

abstract class token_source {
	abstract function next();
	abstract function report_instant_description();
	function report_error() {
		$this->report_instant_description();
		echo "The next few tokens are:<br/>\n";
		for ($i=0; $i<15; $i++) {
			$tok = $this->next();
			span('term', htmlSpecialChars($tok->text), $tok->type);
		}
	}
}

class preg_scanner extends token_source {
	function report_instant_description() {
		echo "Scanner State: $this->state<br/>\n";
	}
	function __construct($init_context, $p = NULL) {
		bug_unless(func_num_args());
		$this->pattern = $p?$p:array('INITIAL'=>array());
		$this->state = 'INITIAL';
		$this->init_context = $init_context;
		$this->context = $init_context;
	}
	function add_state($name, $cluster) {
		bug_unless(is_array($cluster));
		$this->pattern[$name] = $cluster;
	}
	function start($string) {
		$this->context = $this->init_context;
		$this->stream = new stream($string);
		$this->megaregexp = array();
		foreach ($this->pattern as $key=>$blah) {
		  $s='';
		  foreach ($this->pattern[$key] as $pattern) {
		    if ($s) $s.='|';
		    $s .= $pattern[0];
		  }
		  $s = '('.$s.')';
		  $this->megaregexp[$key] = $s;
		}
	}
	function next() {
		$start = $this->stream->pos();
		bug_unless(is_array($this->pattern[$this->state]), 'No state called '.$this->state);
		# much faster implementation of the lexer, by leveraging PCRE a bit better.
		if ($match = $this->stream->test($this->megaregexp[$this->state])) {
		  $text = $match[0];
		  $tmp = array_flip($match);
		  $index = $tmp[$text] -1;
		  $pattern = $this->pattern[$this->state][$index];
                  $type = $pattern[1]; //->type;
                  $action = $pattern[3]; //->action;
                  if ($action) $action($type, $text, $match, $this->state, $this->context);
                  if ($pattern[2]) return $this->next();
                  $stop = $this->stream->pos();
                  return new token($type, $text, $start, $stop);
		}
		return $this->stream->default_rule();
	}
}
$GLOBALS['wasted']=0;

/*
File: parser.so.php
License: GPL
Purpose: Contains the code necessary to operate the left-recursive parsers
Purpose: whose execution tables are generated by the parser generator.
*/

class parse_stack_frame {
	private $symbol, $semantic;
	public $state;
	function __construct($symbol, $state) {
		$this->symbol = $symbol;
		$this->state = $state;
		$this->semantic = array();
	}
	function shift($semantic) { $this->semantic[] = $semantic; }
	function fold($semantic) { $this->semantic = array($semantic); }
	function semantic() { return $this->semantic; }
	function trace() { return "$this->symbol : $this->state"; }
}
class parse_error extends Exception {}
abstract class parser {
	function __construct($pda) {
		$this->pda = $pda;
		$this->action = $pda['action'];
		$this->start = $pda['start'];
		$this->delta = $pda['delta'];
	}
	function report() {
		# pr($this->action);
		pr($this->start);
		foreach($this->delta as $label => $d) {
			echo "<h3>State $label</h3>";
			foreach($d as $glyph => $step) echo $glyph." -&gt; ". implode(':', $step)."<br>";
		}
	}
	function get_step($label, $glyph) {
		$d = $this->delta[$label];
		if (isset($d[$glyph])) return $d[$glyph];
		if (isset($d['[default]'])) return $d['[default]'];
		return array('error');
	}
	function parse($symbol, $lex, $strategy = null) {
		$stack = array();
		$tos = $this->frame($symbol);
		$token = $lex->next();
		while (true) {
			$step = $this->get_step($tos->state, $token->type);
			# echo implode(':', $step)."<br>";
			switch($step[0]) {
				case 'go':
				$tos->shift($token->text);
				$tos->state = $step[1];
				$token = $lex->next();
				break;
				
				case 'do':
				$semantic = $this->reduce($step[1], $tos->semantic());
				if (empty($stack)) {
					$strategy->assert_done($token, $lex);
					return $semantic;
				} else {
					$tos = array_pop($stack);
					$tos->shift($semantic);
				}
				break;
				
				case 'push':
				$tos->state = $step[2];
				$stack[] = $tos;
				$tos = $this->frame($step[1]);
				break;
				
				case 'fold':
				$tos->fold($this->reduce($step[1], $tos->semantic()));
				$tos->state = $step[2];
				break;
				
				case 'error':
				$stack[] = $tos;
				$strategy->stuck($token, $lex, $stack);
				break;
				
				default:
				throw new parse_error("Impossible. Bad PDA has $step[0] instruction.");
			}
		}
	}
	function frame($symbol) { return new parse_stack_frame($symbol, $this->start[$symbol]); }
	abstract function reduce($action, $tokens);
}

class easy_parser extends parser {
	function __construct($pda, $strategy = null) {
		parent::__construct($pda);
		$this->call = $this->action; //array();
		$this->strategy = ($strategy ? $strategy : new default_parser_strategy());
		/*
		foreach($this->action as $k => $body) {
		  $this->call[$k] = create_function( '$tokens', preg_replace('/{(\d+)}/', '$tokens[\\1]', $body));
		}
		*/
	}
	function reduce($action, $tokens) {
		return $this->call[$action]($tokens);
	}
	function parse($symbol, $lex, $strategy = null) {
		return parent::parse($symbol, $lex, $this->strategy);
	}
}

abstract class parser_strategy {
	abstract function stuck($token, $lex, $stack);
	abstract function assert_done($token, $lex);
}
function send_parse_error_css_styles() {
	?>
	<style>
	.term { border: 1px solid green; margin: 2px; }
	.char { border: 1px solid red; margin: 2px; }
	.nonterm { border: 1px solid blue; margin: 10px; }
	.wierd { border: 1px solid purple; margin: 2px; }
	pre { line-height: 1.5; }
	</style>
	<?php
}
class default_parser_strategy extends parser_strategy {
	function stuck($token, $lex, $stack) {
		send_parse_error_css_styles();
		?>
		<hr/>The LR parser is stuck. Source and grammar do not agree.<br/>
		Looking at token:
		<?php
		span('term', $token->text, $token->type);
		echo ' [ '.$token->type.' ]';
		echo "<br/>\n";
		$lex->report_error();
		echo "<hr/>\n";
		echo "Backtrace Follows:<br/>\n";
		# pr($stack);
		while (count($stack)) {
			$tos = array_pop($stack);
			echo $tos->trace()."<br/>\n";
		}
		throw new parse_error("Can't tell what to do with ".$token->type.".");
	}
	function assert_done($token, $lex) {
		if ($token->type) $this->stuck($token, $lex, array());
	}
}


?>