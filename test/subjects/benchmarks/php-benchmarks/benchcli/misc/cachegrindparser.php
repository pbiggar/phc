<?php
class Cachegrindparser
{
    /**
     * Parses the returning string from a cachegrind call
     *
     * @param string $text The text to parse
     *
     * @return array An array of the results.
     */
    function parse($text)
    {
        $match_names = array (    "instruction"
        ,    "instruction_l1_miss"
        ,    "instruction_l2_miss"

        ,	  "data"
        ,	  "data_read"
        ,	  "data_write"

        ,	  "data_l1_miss"
        ,	  "data_l1_miss_read"
        ,    "data_l1_miss_write"

        ,    "data_l2_miss"
        ,    "data_l2_miss_read"
        ,    "data_l2_miss_write"
        
        ,    "l2"
        ,    "l2_read"
        ,    "l2_write"
                    
        ,    "l2_miss"
        ,    "l2_miss_read"
        ,    "l2_miss_write"
                    
        ,    "branch"
        ,    "branch_conditional"
        ,    "branch_indirect"
                    
        ,    "branch_misprediction"
        ,    "branch_conditional_misprediction"
        ,    "branch_indirect_misprediction");

        $start     = "^==\d+==";
        $middle    = ":\s+";
        $number    = "([0-9,]+)";
        $rw        = "\s*\(\s*$number rd\s*\+\s*$number wr\)";
        $branch_rw = "\s*\(\s*$number cond\s*\+\s*$number ind\)";
        $end       = "$.";
        preg_match("/"
        ."$start I\s+refs$middle$number$end"
        ."$start I1\s+misses$middle$number$end"
        ."$start L2i\s+misses$middle$number$end"
        .".*"
        ."$start D\s+refs$middle$number$rw$end"
        ."$start D1\s+misses$middle$number$rw$end"
        ."$start L2d\s+misses$middle$number$rw$end"
        .".*"
        ."$start L2\s+refs$middle$number$rw$end"
        ."$start L2\s+misses$middle$number$rw$end"
        .".*"
        ."$start Branches$middle$number$branch_rw$end"
        ."$start Mispredicts$middle$number$branch_rw$end"
        ."/ms", $text, $matches);

        array_shift($matches); // strip off the

        // remove commas
        foreach ($matches as &$match) {
            $match = preg_replace("/,/", "", $match);
        }

        unset($match); // remove the reference from match
        // make key-value pairs
        $results = array_combine($match_names, $matches);

        return $results;
    }
}
?>