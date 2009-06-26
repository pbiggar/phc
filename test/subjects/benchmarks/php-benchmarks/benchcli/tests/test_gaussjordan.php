<?php
error_reporting(E_ALL | E_STRICT);
/**
 * Class that solves matrixes with the Gauss-Jordan elimination.
 */
class GaussJordan
{
    var $eq,$nc,$s,$r,$grade,$solution;
    /**
     * Constructor for the Gauss-Jordan elimination
     * @param $eq int   Number of rows
     * @param $nc int   Number of columns
     * @param $s  array The matrix to be eliminated
     * @param $r  array The solution for the matrix
     * @return unknown_type
     */
    function __construct($eq,$nc,$s,$r)
    {
        $this->eq = $eq;
        $this->nc = $nc;
        $this->s = $s;
        $this->r = $r;
        $solution = array();
    }
    /**
     * Runs the Gauss-Jordan elimination process
     *
     * @return void
     */
    function process()
    {
        for ($d = 0; ($d < $this->eq) && ($d < $this->nc); $d++) {
            if ($this->s[$d][$d]) {
                $tmp = 1/$this->s[$d][$d];
                $this->multiplicate($d, $tmp);
            }
            for ($eqi = 0; $eqi < $this->eq; $eqi++) {
                if ($eqi == $d) continue;
                $tmp = -1 * $this->s[$eqi][$d];
                $this->multsum($d, $tmp, $eqi);
            }
        }
        $ca = array();
        $cv = array();
        for ($eqi = 0; $eqi < $this->eq; $eqi++) {
            if ((min($this->s[$eqi]) != 0) || (max($this->s[$eqi]) != 0))
            $cv[] = $eqi;
            if ((in_array($eqi, $cv)) || ($this->r[$eqi])) $ca[] = $eqi;
        }

        $c = count($ca) - count($cv);
         
        if ($c)
        $this->r = null;
        else {
            $this->grade = $this->nc - count($cv);
        }
    }
    /**
     * Multiplicates the row's values with the constant given.
     *
     * @param $row   int The row to be multiplicated
     * @param $value int The value to multiplicate with
     *
     * @return void
     */
    function multiplicate($row, $value) {

        for ($nci = 0; $nci < $this->nc; $nci++) {
            $this->s[$row][$nci] *= $value;
        }
        $this->r[$row] *= $value;
    }
    /**
     * Multiplicates and summarizes a row from one
     * to another with the given value.
     * 
     * @param $origin int The row to use as reference 
     * @param $value  int The value to multiplicated with
     * @param $dest   int The row to change
     *
     * @return void
     */
    function multsum($origin, $value, $dest) {

        for ($nci = 0; $nci < $this->nc; $nci++) {
            $this->s[$dest][$nci] += ($this->s[$origin][$nci] * $value);
        }
        $this->r[$dest] += ($this->r[$origin] * $value);
    }
}


/*
 * This solves a seeded random matrix linear system
 * with the Gauss-Jordan algorithm. It's a NxN matrix
 * with N = 100.
 *
 */
function run($n)
{

    $rows = $cols = $n;
    $seed = 20090522;
    srand($seed);
    for($i = 0; $i < $rows; $i++)
    {
        for($j = 0; $j < $cols; $j++)
        {
            $s[$i][$j] = rand(0,50);
        }
        $r[$i] = rand(200,1000);
    }
    $gauss = new GaussJordan($rows,$cols,$s,$r);
    $gauss->process();


}

run(100);
?>
