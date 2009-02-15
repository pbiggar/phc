<?php

	// Reduced by hand from mediawiki LinkHolderArray.php. Reported by Mike Dupont
class test {
	/**
	 * Reduce memory usage to reduce the impact of circular references
	 */
	function __destruct() {
		foreach ( $this as $name => $value ) {

		/**
		the following line crashes
		*/
			unset( $this->$name );
		}
	}

}

// Actually call it.
$x = new test();
unset ($x);

