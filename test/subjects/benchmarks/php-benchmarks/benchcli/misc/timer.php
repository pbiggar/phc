<?php 
/**
 * Simple timer class.
 */
class Timer
{
    var $starttime;
    var $elapsed;

    /**
     * Constructor for the Timer class
     */
    function Timer()
    {
        $this->starttime = 0;
        $this->elapsed   = 0;
    }
    /**
     * Starts the timer.
     * 
     * @return void
     */
    function start()
    {
        $this->starttime = microtime(true);
        $this->elapsed   = 0;
    }
    /**
     * Stops the timer.
     * 
     * @return void
     */
    function stop()
    {
        $this->elapsed   = microtime(true) - $this->starttime; 
        $this->starttime = 0;
    }
}
?>