<?php

  // Check passes are only run once (based on issue 119)

	// { phc-output: Success }
  // { phc-option: --run plugins/tests/run_once.la }

  // Passes are run multiple times during lowering. However, we don't want plugins to be called in the same way. This is a construct that calls back to passes for lowering. The run_once plugin prints success if each of its callbacks are only called once. That once should be during the main pipeline, not during any lowering passes. So the plugin will print "success" if we've got this right.
  while($i < 5)
    $i++;
  
?>
