<?php
/*

	This implementation is derived from the Java implementation by
	Mario Wolczko, Sun Microsystem, Sep 1996, based on the Smalltalk
	implementation by John Maloney of the DeltaBlue aglorithm descibed in:
	
	"The DeltaBlue Algorithm: An Incremental Constraint Hierarchy Solver"
    by Bjorn N. Freeman-Benson and John Maloney
    January 1990 Communications of the ACM,
    also available as University of Washington TR 89-08-06.

*/

error_reporting(E_ALL | E_STRICT);

class Variable {

  var $value;               // my value; changed by constraints
  var $constraints;      // normal constraints that reference me
  var $determinedBy; // the constraint that currently determines
                                  // my value (or null if there isn't one)
  var $mark;                // used by the planner to mark constraints
  var $walkStrength;   // my walkabout strength
  var $stay;            // true if I am a planning-time constant
  var $name;             // a symbolic name for reporting purposes


  function __construct($name, $initialValue)
  {
    $this->value = $initialValue;
    $this->constraints= new OrderedCollection();
    $this->determinedBy= null;
    $this->mark= 0;
    $this->walkStrength = $GLOBALS['WEAKEST'];
    $this->stay= true;
    $this->name= $name;
  }
  
  // Add the given constraint to the set of all constraints that refer to me.
  function addConstraint($c)
  {
    $this->constraints->add($c);
  }

  // Remove all traces of c from this variable.
  
  function removeConstraint($c)
  {
    $this->constraints->remove($c);
    if ($this->determinedBy === $c) $this->determinedBy = null;
  }

}


class OrderedCollection{
	var $elms;
	function __construct(){
		$this->elms = Array();
	}
	function add($elm){
		$this->elms[] = $elm;
	}
	function at($index)
	{
		return $this->elms[$index];
	}
	function size()
	{
		return count($this->elms);
	}
	function removeFirst()
	{
		return array_pop($this->elms);
	}
	function remove($elm)
	{
		$index = 0;
		$skipped = 0;
		for($i = 0; $i < count($this->elms); $i++)
		{
			$value = $this->elms[$i];
			if($value !== $elm)
			{
				$this->elms[$index] = $value;
				$index++;
			}
			else
			{
				$skipped++;
			}
		}
		for($i = 0; $i < $skipped; $i++)
		array_pop($this->elms);
	}
}

class Strength
{
	var $strengthValue, $name;

	function __construct($strengthValue, $name)
	{
		$this->strengthValue = $strengthValue;
		$this->name = $name;
	}

	static function stronger($s1, $s2)
	{
		return $s1->strengthValue < $s2->strengthValue;
	}

	static function weaker($s1, $s2)
	{
		return $s1->strengthValue > $s2->strengthValue;
	}

	static function weakestOf($s1, $s2)
	{
		return Strength::weaker($s1, $s2) ? $s1 : $s2;
	}

	static function strongest($s1, $s2)
	{
		return $this->stronger($s1, $s2) ? $s1 : $s2;
	}

	function nextWeaker()
	{
		switch($this->strengthValue)
		{
			case 0: return new Strength(6, "weakest");
			case 1: return new Strength(5, "weakDefault");
			case 2: return new Strength(4, "normal");
			case 3: return new Strength(3, "strongDefault");
			case 4: return new Strength(2, "preferred");
			case 5: return new Strength(0, "required");
		}
	}
}

$REQUIRED = new Strength(0, "required");
define('REQUIRED', $REQUIRED->strengthValue);

$STRONG_PREFERRED = new Strength(1, "strongPreferred");
define('STRONG_PREFERRED', $STRONG_PREFERRED->strengthValue);

$PREFERRED = new Strength(2, "preferred");
define('PREFERRED', $PREFERRED->strengthValue);

$STRONG_DEFAULT	= new Strength(3, "strongDefault");
define('STRONG_DEFAULT', $STRONG_DEFAULT->strengthValue);

$NORMAL = new Strength(4, "normal");
define('NORMAL', $NORMAL->strengthValue);

$WEAK_DEFAULT = new Strength(5, "weakDefault");
define('WEAK_DEFAULT', $WEAK_DEFAULT->strengthValue);

$WEAKEST = new Strength(6, "weakest");
define('WEAKEST', $WEAKEST->strengthValue);




//------------------------ constraints ------------------------------------

// I am an abstract class representing a system-maintainable
// relationship (or "constraint") between a set of variables. I supply
// a strength instance variable; concrete subclasses provide a means
// of storing the constrained variables and other information required
// to represent a constraint.

class Constraint {

  var $strength; // the strength of this constraint

  function __construct($strength)
  {
  	 global $planner;
  	 $this->planner = $planner;
     $this->strength = $strength;
  }



  // Normal constraints are not input constraints. An input constraint
  // is one that depends on external state, such as the mouse, the
  // keyboard, a clock, or some arbitrary piece of imperative code.
  function isInput() { return false; }

  // Activate this constraint and attempt to satisfy it.
  function addConstraint()
  {
    $this->addToGraph();
    $this->planner->incrementalAdd($this);
  }

  // Deactivate this constraint, remove it from the constraint graph,
  // possibly causing other constraints to be satisfied, and destroy
  // it.
  function destroyConstraint()
  {
    if ($this->isSatisfied()) $this->planner->incrementalRemove($this);
    $this->removeFromGraph();
  }


  // Attempt to find a way to enforce this constraint. If successful,
  // record the solution, perhaps modifying the current dataflow
  // graph. Answer the constraint that this constraint overrides, if
  // there is one, or nil, if there isn't.
  // Assume: I am not already satisfied.
  //
  function satisfy($mark)
  {
    $this->chooseMethod($mark);
    if (!$this->isSatisfied()) {
      if ($this->strength === $GLOBALS['REQUIRED']) {
		echo ("Could not satisfy a required constraint");
      }
      return null;
    }
    // constraint can be satisfied
    // mark inputs to allow cycle detection in addPropagate
    $this->markInputs($mark);
    $out= $this->output();
    $overridden= $out->determinedBy;
    if ($overridden != null) $overridden->markUnsatisfied();
    $out->determinedBy= $this;
    if (!$this->planner->addPropagate($this, $mark)) {
      echo ("Cycle encountered");
      return null;
    }
    $out->mark= $mark;
    return $overridden;
  }

}



//-------------unary constraints-------------------------------------------

// I am an abstract superclass for constraints having a single
// possible output variable.
//
class UnaryConstraint extends Constraint {

  var $myOutput; // possible output variable
  var $satisfied; // true if I am currently satisfied

  function __construct($v, $strength)
  {
    Constraint::__construct($strength);
    $this->myOutput= $v;
    $this->satisfied= false;
    $this->addConstraint();
  }

  // Answer true if this constraint is satisfied in the current solution.
  function isSatisfied() { return $this->satisfied; }

  // Record the fact that I am unsatisfied.
  function markUnsatisfied() { $this->satisfied= false; }

  // Answer my current output variable.
  function  output() { return $this->myOutput; }

  // Add myself to the constraint graph.
  function addToGraph()
  {
    $this->myOutput->addConstraint($this);
    $this->satisfied= false;
  }

  // Remove myself from the constraint graph.
  function removeFromGraph()
  {
    if ($this->myOutput != null) $this->myOutput->removeConstraint($this);
    $satisfied= false;
  }

  // Decide if I can be satisfied and record that decision.
  function chooseMethod($mark)
  {
    $this->satisfied= $this->myOutput->mark != $mark
               && Strength::stronger($this->strength, $this->myOutput->walkStrength);
  }

  function markInputs($mark) {}   // I have no inputs

  function inputsKnown($mark) { return true; }

  // Calculate the walkabout strength, the stay flag, and, if it is
  // 'stay', the value for the current output of this
  // constraint. Assume this constraint is satisfied."
  function recalculate()
  {
    $this->myOutput->walkStrength= $this->strength;
    $this->myOutput->stay= !$this->isInput();
    if ($this->myOutput->stay) $this->execute(); // stay optimization
  }


}


// I am a unary input constraint used to mark a variable that the
// client wishes to change.
//
class EditConstraint extends UnaryConstraint {

  function __construct($v, $str)
  {
  UnaryConstraint::__construct($v, $str);
  }

  // I indicate that a variable is to be changed by imperative code.
  function isInput() 
  { 
  return true; 
  }

  function execute() {} // Edit constraints do nothing.

}

// I mark variables that should, with some level of preference, stay
// the same. I have one method with zero inputs and one output, which
// does nothing. Planners may exploit the fact that, if I am
// satisfied, my output will not change during plan execution. This is
// called "stay optimization".
//
class StayConstraint extends UnaryConstraint {

  // Install a stay constraint with the given strength on the given variable.
  function  __construct($v, $str) 
  { 
  UnaryConstraint::__construct($v, $str); 
  }

  function execute() {} // Stay constraints do nothing.

}




//-------------binary constraints-------------------------------------------


// I am an abstract superclass for constraints having two possible
// output variables.
//
class BinaryConstraint extends Constraint {

  var $v1;
  var $v2; // possible output variables
  var $direction; // one of the following...
  var $backward= -1;    // v1 is output
  var $nodirection= 0;  // not satisfied
  var $forward= 1;      // v2 is output


  function __construct($var1, $var2, $strength) {
    Constraint::__construct($strength);
    $this->v1= $var1;
    $this->v2= $var2;
    $this->direction= $this->nodirection;
    $this->addConstraint();
  }

  // Answer true if this constraint is satisfied in the current solution.
  function isSatisfied() { return $this->direction != $this->nodirection; }

  // Add myself to the constraint graph.
  function addToGraph()
  {
    $this->v1->addConstraint($this);
    $this->v2->addConstraint($this);
    $this->direction = $this->nodirection;
  }

  // Remove myself from the constraint graph.
  function removeFromGraph()
  {
    if ($this->v1 != null) $this->v1->removeConstraint($this);
    if ($this->v2 != null) $this->v2->removeConstraint($this);
    $this->direction= $this->nodirection;
  }

  // Decide if I can be satisfied and which way I should flow based on
  // the relative strength of the variables I relate, and record that
  // decision.
  //
  function chooseMethod($mark)
  {
    if ($this->v1->mark == $mark) 
      $this->direction=
	$this->v2->mark != $mark && Strength::stronger($this->strength, $this->v2->walkStrength)
	  ? $this->forward : $this->nodirection;

    if ($this->v2->mark == $mark) 
      $this->direction=
	$this->v1->mark != $mark && Strength::stronger($this->strength, $this->v1->walkStrength)
	  ? $this->backward : $this->nodirection;

    // If we get here, neither variable is marked, so we have a choice.
    if (Strength::weaker($this->v1->walkStrength, $this->v2->walkStrength))
      $this->direction=
	Strength::stronger($this->strength, $this->v1->walkStrength) ? $this->backward : $this->nodirection;
    else
      $this->direction=
	Strength::stronger($this->strength, $this->v2->walkStrength) ? $this->forward : $this->nodirection;
  }

  // Record the fact that I am unsatisfied.
  function markUnsatisfied() { $this->direction= $this->nodirection; }

  // Mark the input variable with the given mark.
  function markInputs($mark)
  {
    $this->input()->mark= $mark;
  }
  
  function inputsKnown($mark)
  {
    $i= $this->input();
    return $i->mark == $mark || $i->stay || $i->determinedBy == null;
  }
  
  // Answer my current output variable.
  function output() { return $this->direction==$this->forward ? $this->v2 : $this->v1; }

  // Answer my current input variable
  function input() { return $this->direction==$this->forward ? $this->v1 : $this->v2; }

  // Calculate the walkabout strength, the stay flag, and, if it is
  // 'stay', the value for the current output of this
  // constraint. Assume this constraint is satisfied.
  //
  function recalculate()
  {
    $in= $this->input();
    $out= $this->output();
    $out->walkStrength= Strength::weakestOf($this->strength, $in->walkStrength);
    $out->stay= $in->stay;
    if ($out->stay) $this->execute();
  }

}


// I constrain two variables to have the same value: "v1 = v2".
//
class EqualityConstraint extends BinaryConstraint {

  // Install a constraint with the given strength equating the given variables.
  function __construct($var1, $var2, $strength)
  {
  	$par = get_parent_class($this);
  	BinaryConstraint::__construct($var1, $var2, $strength);
  }

  // Enforce this constraint. Assume that it is satisfied.
  function execute() {
    $this->output()->value= $this->input()->value;
  }

}


// I relate two variables by the linear scaling relationship: "v2 =
// (v1 * scale) + offset". Either v1 or v2 may be changed to maintain
// this relationship but the scale factor and offset are considered
// read-only.
//
class ScaleConstraint extends BinaryConstraint {

  var $scale; // scale factor input variable
  var $offset; // offset input variable
  var $planner;
  // Install a scale constraint with the given strength on the given variables.
  function __construct($src, $scale, $offset,
		         $dest, $strength)
  {
    global $planner;
    $this->planner = $planner;
    // Curse this wretched language for insisting that constructor invocation
    // must be the first thing in a method...
    // ..because of that, we must copy the code from the inherited
    // constructors.
    $this->strength= $strength;
    $this->v1= $src;
    $this->v2= $dest;
    $this->direction= $this->nodirection;
    $this->scale= $scale;
    $this->offset= $offset;
    $this->addConstraint();
  }

  // Add myself to the constraint graph.
  function addToGraph()
  {
    parent::addToGraph();
    $this->scale->addConstraint($this);
    $this->offset->addConstraint($this);
  }

  // Remove myself from the constraint graph.
  function removeFromGraph()
  {
    parent::removeFromGraph();
    if ($this->scale != null) $this->scale->removeConstraint($this);
    if ($this->offset != null) $this->offset->removeConstraint($this);
  }

  // Mark the inputs from the given mark.
  function markInputs($mark)
  {
    parent::markInputs($mark);
    $this->scale->mark= $this->offset->mark= $mark;
  }

  // Enforce this constraint. Assume that it is satisfied.
  function execute()
  {
    if ($this->direction == $this->forward) 
      $this->v2->value= $this->v1->value * $this->scale->value + $this->offset->value;
    else
      $this->v1->value= ($this->v2->value - $this->offset->value) / $this->scale->value;
  }

  // Calculate the walkabout strength, the stay flag, and, if it is
  // 'stay', the value for the current output of this
  // constraint. Assume this constraint is satisfied.
  function recalculate()
  {
    $in= $this->input();
    $out= $this->output();
    $out->walkStrength = Strength::weakestOf($this->strength, $in->walkStrength);
    $out->stay= $in->stay && $this->scale->stay &&  $this->offset->stay;
    if ($out->stay) $this->execute(); // stay optimization
  }
}

    
// ------------------------------------------------------------


// A Plan is an ordered list of constraints to be executed in sequence
// to resatisfy all currently satisfiable constraints in the face of
// one or more changing inputs.

class Plan {

  var $v;

  function __construct()  { $this->v= new OrderedCollection(); }

  function addConstraint($c) { $this->v->add($c); }

  function size() { return $this->v->size(); }

  function constraintAt($index) {
    return $this->v->at($index); }

  function execute()
  {
    for ($i= 0; $i < $this->size(); ++$i) {
      $c= $this->constraintAt($i);
      $c->execute();
    }
  }

}


// ------------------------------------------------------------

// The DeltaBlue planner

class Planner {

  var $currentMark= 0;

  // Select a previously unused mark value.
  function newMark() { return ++$this->currentMark; }

  function __construct()
  {
    $this->currentMark= 0;
  }

  // Attempt to satisfy the given constraint and, if successful,
  // incrementally update the dataflow graph.  Details: If satifying
  // the constraint is successful, it may override a weaker constraint
  // on its output. The algorithm attempts to resatisfy that
  // constraint using some other method. This process is repeated
  // until either a) it reaches a variable that was not previously
  // determined by any constraint or b) it reaches a constraint that
  // is too weak to be satisfied using any of its methods. The
  // variables of constraints that have been processed are marked with
  // a unique mark value so that we know where we've been. This allows
  // the algorithm to avoid getting into an infinite loop even if the
  // constraint graph has an inadvertent cycle.
  //
  function incrementalAdd($c)
  {
    $mark= $this->newMark();
    $overridden= $c->satisfy($mark);
    while ($overridden != null) {
      $overridden= $overridden->satisfy($mark);
    }
  }


  // Entry point for retracting a constraint. Remove the given
  // constraint and incrementally update the dataflow graph.
  // Details: Retracting the given constraint may allow some currently
  // unsatisfiable downstream constraint to be satisfied. We therefore collect
  // a list of unsatisfied downstream constraints and attempt to
  // satisfy each one in turn. This list is traversed by constraint
  // strength, strongest first, as a heuristic for avoiding
  // unnecessarily adding and then overriding weak constraints.
  // Assume: c is satisfied.
  //
  function incrementalRemove($c)
  {
    $out= $c->output();
    $c->markUnsatisfied();
    $c->removeFromGraph();
    $unsatisfied= $this->removePropagateFrom($out);
    $strength= $GLOBALS['REQUIRED'];
    do {
      for ($i= 0; $i < $unsatisfied->size(); ++$i) {
	$u= $unsatisfied->at($i);
	if ($u->strength == $strength)
	  $this->incrementalAdd($u);
      }
      $strength= $strength->nextWeaker();
    } while ($strength != $GLOBALS['WEAKEST']);
  }

  // Recompute the walkabout strengths and stay flags of all variables
  // downstream of the given constraint and recompute the actual
  // values of all variables whose stay flag is true. If a cycle is
  // detected, remove the given constraint and answer
  // false. Otherwise, answer true.
  // Details: Cycles are detected when a marked variable is
  // encountered downstream of the given constraint. The sender is
  // assumed to have marked the inputs of the given constraint with
  // the given mark. Thus, encountering a marked node downstream of
  // the output constraint means that there is a path from the
  // constraint's output to one of its inputs.
  //
  function addPropagate($c,$mark)
  {
    $todo= new OrderedCollection();
    $todo->add($c);
    while ($todo->size() > 0) {
      $d= $todo->removeFirst();
      if ($d->output()->mark == $mark) {
			$this->incrementalRemove($c);
		return false;
		
      }
      $d->recalculate();
      $this->addConstraintsConsumingTo($d->output(), $todo);
    }
    return true;
  }


  // The given variable has changed. Propagate new values downstream.
  function propagateFrom($v)
  {
    $todo= new OrderedCollection();
    $this->addConstraintsConsumingTo($v, $todo);
    while ($this->todo->size() > 0)  {
      $c = $todo->removeFirst();
      $c->execute();
      $this->addConstraintsConsumingTo($c->output(), $todo);
    }
  }

  // Update the walkabout strengths and stay flags of all variables
  // downstream of the given constraint. Answer a collection of
  // unsatisfied constraints sorted in order of decreasing strength.
  //
  function removePropagateFrom($out)
  {
    $out->determinedBy= null;
    $out->walkStrength= $GLOBALS['WEAKEST'];
    $out->stay= true;
    $unsatisfied= new OrderedCollection();
    $todo= new OrderedCollection();
    $todo->add($out);
    while ($todo->size() > 0) {
      $v = $todo->removeFirst();
      for ($i= 0; $i < $v->constraints->size(); ++$i) {
	$c=  $v->constraints->at($i);
	if (!$c->isSatisfied())
	  $unsatisfied->add($c);
      }
      $determiningC= $v->determinedBy;
      for ($i= 0; $i < $v->constraints->size(); ++$i) {
	$nextC= $v->constraints->at($i);
	if ($nextC !== $determiningC && $nextC->isSatisfied()) {
	  $nextC->recalculate();
	  $todo->add($nextC->output());
	}
      }
    }
    return $unsatisfied;
  }

  // Extract a plan for resatisfaction starting from the outputs of
  // the given constraints, usually a set of input constraints.
  //
  function extractPlanFromConstraints($constraints)
  {
    $sources= new OrderedCollection();
    for ($i= 0; $i < $constraints->size(); ++$i) {
      $c= $constraints->at($i);
      if ($c->isInput() && $c->isSatisfied())
	$sources->add($c);
    }
    return $this->makePlan($sources);
  }

  // Extract a plan for resatisfaction starting from the given source
  // constraints, usually a set of input constraints. This method
  // assumes that stay optimization is desired; the plan will contain
  // only constraints whose output variables are not stay. Constraints
  // that do no computation, such as stay and edit constraints, are
  // not included in the plan.
  // Details: The outputs of a constraint are marked when it is added
  // to the plan under construction. A constraint may be appended to
  // the plan when all its input variables are known. A variable is
  // known if either a) the variable is marked (indicating that has
  // been computed by a constraint appearing earlier in the plan), b)
  // the variable is 'stay' (i.e. it is a constant at plan execution
  // time), or c) the variable is not determined by any
  // constraint. The last provision is for past states of history
  // variables, which are not stay but which are also not computed by
  // any constraint.
  // Assume: sources are all satisfied.
  //
  function makePlan($sources)
  {
    $mark= $this->newMark();
    $plan= new Plan();
    $todo= $sources;
    while ($todo->size() > 0) {
      $c = $todo->removeFirst();
      if ($c->output()->mark != $mark && $c->inputsKnown($mark)) {
	// not in plan already and eligible for inclusion
	$plan->addConstraint($c);
	$c->output()->mark= $mark;
	$this->addConstraintsConsumingTo($c->output(), $todo);
      }
    }
    return $plan;
  }

  function addConstraintsConsumingTo($v, $coll)
  {
    $determiningC= $v->determinedBy;
    $cc= $v->constraints;
    for ($i= 0; $i < $cc->size(); ++$i) {
      $c= $cc->at($i);
      if ($c !== $determiningC && $c->isSatisfied())
	$coll->add($c);
    }
  }

}

//------------------------------------------------------------


$planner = new Planner();
  function chainTest($n)
  {
    global $planner;

    $prev= null;
    $first= null;
    $last= null;

    // Build chain of n equality constraints
    for ($i= 0; $i <= $n; $i++) {
      $name= "v".$i;
      $v= new Variable($name,0);
      if ($prev != null)
			new EqualityConstraint($prev, $v, $GLOBALS['REQUIRED']);
      if ($i == 0) $first= $v;
      if ($i == $n) $last= $v;
       $prev= $v;
    }

    new StayConstraint($last, $GLOBALS['STRONG_DEFAULT']);
    $editC= new EditConstraint($first, $GLOBALS['PREFERRED']);
    $editV= new OrderedCollection();
    $editV->add($editC);
    $plan=$planner->extractPlanFromConstraints($editV);
    for ($i= 0; $i < 100; $i++) {
      $first->value= $i;
      $plan->execute();
      
      if ($last->value != $i)
	echo ("Chain test failed!");
    }
    $editC->destroyConstraint();
  }


  // This test constructs a two sets of variables related to each
  // other by a simple linear transformation (scale and offset). The
  // time is measured to change a variable on either side of the
  // mapping and to change the scale and offset factors.
  //
  function projectionTest($n)
  {
  	global $planner;  
    $planner= new Planner();

    $scale= new Variable("scale", 10);
    $offset= new Variable("offset", 1000);
    $src= null;
    $dst= null;

    $dests= new OrderedCollection();

    for ($i= 0; $i < $n; ++$i) {
      $src= new Variable("src".$i, $i);
      $dst= new Variable("dst".$i, $i);
      $dests->add($dst);
      new StayConstraint($src, $GLOBALS['NORMAL']);
      new ScaleConstraint($src, $scale, $offset, $dst, $GLOBALS['REQUIRED']);
    }

    change($src, 17);
    if ($dst->value != 1170) echo ("Projection test 1 failed!");

    change($dst, 1050);
    if ($src->value != 5) echo ("Projection test 2 failed!");

    change($scale, 5);
    for ($i= 0; $i < $n - 1; ++$i) {
      if ($dests->at($i)->value != $i * 5 + 1000)
	echo ("Projection test 3 failed!");
    }

    change($offset, 2000);
    for ($i= 0; $i < $n - 1; ++$i) {
      if ($dests->at($i)->value != $i * 5 + 2000)
	echo ("Projection test 4 failed!");
    }
  }

  function change($var, $newValue)
  {
  	global $planner;
    $editC= new EditConstraint($var, $GLOBALS['PREFERRED']);
    $editV= new OrderedCollection();
    $editV->add($editC);
    $plan= $planner->extractPlanFromConstraints($editV);
    for ($i= 0; $i < 10; $i++) {
      $var->value= $newValue;
      $plan->execute();
    }
    $editC->destroyConstraint();
  }
  
 function deltaBlue() {
  chainTest(100);
  projectionTest(100);
}

function run($length)
{
for ($i = 0; $i < $length; ++$i)
    deltaBlue();
}

run(10);
?>
