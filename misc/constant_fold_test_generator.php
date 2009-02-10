<?php

	include "test/framework/lib/header.php";

	/* For each type of scalar, create an expression with each other type of
	 * scalar and each operator. Put all errors and warnings into a file each,
	 * with regexes created for the testing framework. Put all other expressions
	 * into a single file. */

	$scalars = array ("0", "1", "5", "-1", "-10000", "true", "false", "\"String\"", "\"num3\"", "\"3\"", "6.702", "40.4e3", "0x786F");

	$bin_ops = array ("+", "-", "/", "*", "%", "^", "&", "|", ".", "==", "===", "!=", "<>", "!==", "<=", ">=", "&&", "||", "<<", ">>");

	$unary_ops = array ( "~", "!");


	// These ops dont really make sense, and probably dont even parse (using a const on lhs)
//	$bad_ops = array (  "+=", "-=", "*=", "/=", ".=",
//	"%=", "&=", "|=", "^=", "<<=", ">>=");


	// Initialize
	$good = array ();
	$bad = array ();
	$dont = array ();


	// Run the tests
	foreach ($scalars as $s1)
	{
		foreach ($scalars as $s2)
		{
			foreach ($bin_ops as $b)
			{
				// dont repeat tests with the same operator and 2nd operand
				if (empty ($dont["$b$s2"]))
					if (!test ("$s1 $b $s2")) 
						$dont["$b$s2"] = true;
			}

		}
		foreach ($unary_ops as $u)
		{
			test ("$u $s1");
		}
	}


	// Create test files
	$good = join ("\n", $good);
	$good = "<?php\n$good\n?>";
	$filename = "test/subjects/parsing/constant_folding.php";
	file_put_contents ($filename, $good);

	$i = 0;
	foreach ($bad as $b)
	{
		list ($string, $out, $err, $exit) = $b;
		$out = trim ($out);
		$out = homogenize_all ($out, $filename);
		$out = convert_to_phc_annotation ($out);

		// make an error template
		$string =	"<?php\n"
						. "var_dump ($string); // { $out }\n"
						. "?>";

		// error or warning
		if ($exit)
			file_put_contents ("test/subjects/errors/constant_folding$i.php", $string);
		else
			file_put_contents ("test/subjects/warnings/constant_folding$i.php", $string);

		$i++;
	}


	function test ($str)
	{
		list ($out, $err, $exit) = complete_exec ("echo '<?php \$x = $str ?>' | php");

		if ($exit || $out)
		{
			global $bad;
			$bad[] = array ($str, $out, $err, $exit);
			return false; // indicate we dont want to test this again
		}
		else
		{
			global $good;
			$good[]  = "var_dump ($str);";
			return true;
		}
	}

	function convert_to_phc_annotation ($string)
	{
		$string = preg_replace ("/Warning/", "phc-warning", $string);
		return $string;
	}



?>
