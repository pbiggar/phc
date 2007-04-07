<!--
	All of this magic explained in Section 10.2 on
	http://ie.php.net/manual/en/language.basic-syntax.php
-->

<script language="php">
	echo "script tags ok\n";
</script>

<script    language = 'php'      >
	// It seems spaces arent allowed between the '<' and "script" or "/script"
	echo "spaced script tags ok\n";
</script           >

<script    language ='php'      >
	echo "with single quotes ok\n";
</script           >

<!--
	ASP style tags are "less portable", whatever that means. They need the
	php.ini directive "asp_tags". Short tags (aka sgml tags) are also not
	recommended, and come via the "short_tags" php directive.
-->

<?
	echo "sgml style ok\n";
?>

<?= 
	"special sgml style echo ok\n";
?>


<% echo "ASP style ok\n"; %>
<%= "asp style special echo ok\n"; %>

<?PHP

	/* It seems we get a syntax error for capital PHP in the opening tag */
	/* This causes some code from phpMyAdmin and squirellmail to fail */
	echo "test success\n";

?>

<?pHP

	/* Any capitalization seesm be ok for the interpreter */
	echo "test success\n";

?>

