<?php

	function simplecall() {
  for ($i = 0; $i < 1000000; $i++) 
    strlen("hallo");
}

simplecall ();


?>
