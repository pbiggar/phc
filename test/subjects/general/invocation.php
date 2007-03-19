<?php
	$x->x;
	$x->$x;
	$x->x();
	$x->$x();

	$x->$$x;

	$x->x->x;
	$x->$x->$x;
	$x->x()->x();
	$x->$x()->$x();

	$x->x[3];
	$x->x[3](); // Precedence inversion 
	$x->x[3]()->y[3]; // Precedence inversion
	$x->x[3]()->y[3](); // Precedence inversion (twice)

	$x->{2 + 3};
	$x->{2 + 3}();
?>
