<?php
/**
 * This smaps-parser requires linux with kernel 2.6.14 or newer.
 *
 */
class Smapsparser
{
    var $results;
    var $usage;
    function Smapsparser()
    {
        $usage = array();
    }
    function parseSmapsData($data)
    {
        $lines             = explode("\n",$data);
        $i                 = 0;
        $last              = array();
        $result            = array();
        $result["objects"] = array();
        foreach ($lines as $line) {
            $matches = array();
            if (preg_match('/[a-z0-9]+[-][a-z0-9]+/',$line)) {
                if (preg_match('/[\d]{2}:[\d]{2}[\s][\d]+[\s]+(?<name>.*)/', $line,$matches)) {
                    if(!empty($last))
                    $result["objects"][] = $last;
                    $last["name"]        = $matches["name"];
                }
            } else if (preg_match('/(?<name>[a-zA-Z_]+):/', $line,$match_type)) {
                preg_match('/(?<amount>\d+)[\s]kB/', $line, $match_amount);
                $last[$match_type["name"]] = $match_amount["amount"];
                if (!isset($result[$match_type["name"]])) {
                    $result[$match_type["name"]] = 0;
                }
                $result[$match_type["name"]] += $match_amount["amount"];
            }
        }
        $result["objects"][] = $last;
        $this->usage[]       = $result;
    }
    function getUsage()
    {
        return $this->usage;
    }
    /**
     * Compare elements based on Private_Dirty
     *
     */
    static function cmpKey($a,$b)
    {
        if ($a["Private_Dirty"] == $b["Private_Dirty"]) {
            return 0;
        }
        return ($a["Private_Dirty"] < $b["Private_Dirty"]) ? 1 : -1;
    }
    /**
     * Get element index of peak memory usage
     * 
     * @return int The index of $this->used's peak
     */
    function getPeak()
    {
        $maxi   = 0;
        $maxval = 0;
        $i      = 0;
        
        foreach ($this->usage as $mem_array) {
            if ($maxval < $mem_array["Size"]) {
                $maxi   = $i;
                $maxval = $mem_array["Size"];
                
            }
            $i++;
        }
        return $maxi;
    }
    /**
     * Clear the memory usage of the parser
     */
    function clear()
    {
        unset($results);
        unset($usage);        
    }
    /**
     * Prints the top n memory consuming files based on Dirty Private RSS, 
     * for the maximum peak of memory consumption.
     *
     * @param int    $n        The number of files to be printed
     * @param string $resource If specified, it will append to this file instead
	 *                         of stdout
     * 
     * @return void
     */
    function printMaxUsage($n,$resource = "php://stdout")
    {
        
        $i = 0;
        if ($resource == "php://stdout") {
            $fh = fopen($resource, "w");
        } else {
            $fh = fopen($resource, "a+");
        }
        $peak = $this->usage[$this->getPeak()];
        $this->sortMemUsage($peak["objects"]);
        fprintf($fh, "VM Size total: %10skB\n", $peak['Size']);
        fprintf($fh, "RSS          : %10skB Total\n", $peak['Rss']);
        fprintf($fh, "             : %10skB Shared total\n", $peak['Shared_Dirty'] + $peak["Shared_Clean"]);
        fprintf($fh, "               %10skB Private Clean\n", $peak['Private_Clean']);
        fprintf($fh, "               %10skB Private Dirty\n", $peak['Private_Dirty']);
        fprintf($fh, "%10s %10s %10s %-15s\n", "vm size", "Clean", "Dirty", "File name");
        fprintf($fh, "%'-59s\n", "-");
        foreach ($peak["objects"] as $key) {
            $i++;
            if ($i > $n) {
                break;
            }
            // If it's anonymous, don't print it.
            if ($key["name"] != "") {
                fprintf($fh, "%8skB %8skB %8skB %-18s\n", $key['Size'], $key["Private_Clean"], $key["Private_Dirty"], $key["name"]);
            } else {
                $i--;
            }
        }
        fprintf($fh, "%s", "\n");
    }

    /**
     * Sorts the memory usage from the array
     *
     * @param &array &$array The of parsed smaps results to be sorted
     * 
     * @return void
     */
    function sortMemUsage(&$array)
    {
        usort($array, "Smapsparser::cmpKey");
    }
    /**
     * Reads the Smaps data of the given PID
     *
     * @param int $pid The PID to read Smaps data from
     *
     * @return File contents in form of string or if file not exists
     * 	       false is returned.
     */
    function readSmapsData($pid)
    {
        if (file_exists("/proc/$pid/smaps")) {
            return file_get_contents("/proc/$pid/smaps");
        }
        return false;
    }

}
?>