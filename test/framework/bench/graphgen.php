<?php
/*
*
* Generates source files for generating graphs with bargraph.pl
*
* Usage: php test/framework/bench/graphgen.php <path of database> <destination directory for output>
*
*/
	$BENCHES = array (
			"test/subjects/benchmarks/RUBBoS/PHP/",
			"test/subjects/benchmarks/RUBiS/",
			"test/subjects/benchmarks/webapps/eveactive_1.0/",
			"test/subjects/benchmarks/webapps/phpSQLiteAdmin-0.2/",
			"test/subjects/benchmarks/webapps/tigerPhpNewsSystem_1.0_beta_build39/",
			"test/subjects/benchmarks/zend/individual/",
			"test/subjects/benchmarks/shootout/"
			);

	$FLAGS = array (
		" --flow-insensitive --call-string-length=1",
		" --call-string-length=1",
		" --flow-insensitive ",
		" "
		);

	// Start looking in the database
	$db_filename = $argv[1];
	
	// Should be a directory
	$DEST = $argv[2];

	$DB = new PDO ("sqlite:$db_filename");

	peak_aliases_per_var ($DB, $BENCHES, $FLAGS, $DEST);
	types_per_variable ($DB, $BENCHES, $FLAGS, $DEST );
	receivers_per_call ($DB, $BENCHES, $FLAGS, $DEST);
	precision_in_rw ($DB, $BENCHES, $FLAGS, $DEST);
	ifs_replaced_constants ($DB, $BENCHES, $FLAGS, $DEST);
	unreachable_statements ($DB, $BENCHES, $FLAGS, $DEST);

	
	function	peak_aliases_per_var (PDO $DB, $BENCHES, $FLAGS, $DEST)
	{
		$fh = fopen ($DEST."papv.txt", "w");
		fwrite ($fh, "=stackcluster;0;1;2;3;4;5+;\ncolors=grey7,grey6,grey5,grey4,grey3,grey2\nlegendx=6400\nlegendy=1500\nfontsz=7\n=nogridy\nextraops=set label \"fci = flow and context insensitive\\nci = context insensitive\\nfi = flow insensitive\\nfcs = flow and context sensitive\" at 3,1700 left font \"Times,10\"\nxlabelshift=0,1\n");

		foreach ($BENCHES as $bench)
		{
			$i = 0;
			foreach ($FLAGS as $flags)
			{
				$res = 0;
				for ($j = 0; $j <= 10; $j++)
				{
					$res = get_stat ($DB, "vars_with_".$j."_aliases", $flags, $bench);	
					if (j <= 5)
					{
						if ($res == -1)
							$stat_matrix[$i][$j] = 0;
						else
							$stat_matrix[$i][$j] = $res;
					}
					else
					{
						if ($res != -1)
							$stat_matrix[$i][5] += $res;
					}
				}
				
				//while (($res = get_stat ($DB, "vars_with_".$j."aliases", $flags, $bench)) != -1)
/*				while (($res = get_stat ($DB, "defs", $flags, $bench)) != -1)
				{	
					$stat_matrix[$i][5] = $res;	
					$j++;	
				}*/
				$i++;
			}
			fwrite ($fh, "multimulti=$bench
fci	".$stat_matrix[0][0]."  ".$stat_matrix[0][1]."  ".$stat_matrix[0][2]."  ".$stat_matrix[0][3]."  ".$stat_matrix[0][4]."  ".$stat_matrix[0][5]."
ci		".$stat_matrix[1][0]."  ".$stat_matrix[1][1]."  ".$stat_matrix[1][2]."  ".$stat_matrix[1][3]."  ".$stat_matrix[1][4]."  ".$stat_matrix[1][5]."
fi		".$stat_matrix[2][0]."  ".$stat_matrix[2][1]."  ".$stat_matrix[2][2]."  ".$stat_matrix[2][3]."  ".$stat_matrix[2][4]."  ".$stat_matrix[2][5]."
fcs	".$stat_matrix[3][0]."  ".$stat_matrix[3][1]."  ".$stat_matrix[3][2]."  ".$stat_matrix[3][3]."  ".$stat_matrix[3][4]."  ".$stat_matrix[3][5]."
\n");
		}
		var_dump ($stat_matrix);
	
		fclose($fh);	
	}

	function	types_per_variable (PDO $DB, $BENCHES, $FLAGS, $DEST)
	{
		$fh = fopen ($DEST."tpv.txt", "w");
		fwrite ($fh, "=stackcluster;1;2;3;4;5+;\ncolors=grey7,grey6,grey5,grey4,grey3,grey2\nfontsz=7\nlegendx=6400\nlegendy=1500\n=nogridy\nextraops=set label \"fci = flow and context insensitive\\nci = context insensitive\\nfi = flow insensitive\\nfcs = flow and context sensitive\" at 3,1700 left font \"Times,10\"\nxlabelshift=0,1\n");

		foreach ($BENCHES as $bench)
		{
			$i = 0;
			foreach ($FLAGS as $flags)
			{
				$res = 0;
				for ($j = 0; $j <= 10; $j++)
				{
					$res = get_stat ($DB, "num_vars_".$j."_types", $flags, $bench);	
					if (j <= 5)
					{
						if ($res == -1)
							$stat_matrix[$i][$j] = 0;
						else
							$stat_matrix[$i][$j] = $res;
					}
					else
					{
						if ($res != -1)
							$stat_matrix[$i][5] += $res;
					}
				}
						$i++;
			}
			fwrite ($fh, "multimulti=$bench
fci	".$stat_matrix[0][1]."  ".$stat_matrix[0][2]."  ".$stat_matrix[0][3]."  ".$stat_matrix[0][4]."  ".$stat_matrix[0][5]."
ci		".$stat_matrix[1][1]."  ".$stat_matrix[1][2]."  ".$stat_matrix[1][3]."  ".$stat_matrix[1][4]."  ".$stat_matrix[1][5]."
fi		".$stat_matrix[2][1]."  ".$stat_matrix[2][2]."  ".$stat_matrix[2][3]."  ".$stat_matrix[2][4]."  ".$stat_matrix[2][5]."
fcs	".$stat_matrix[3][1]."  ".$stat_matrix[3][2]."  ".$stat_matrix[3][3]."  ".$stat_matrix[3][4]."  ".$stat_matrix[3][5]."
\n");	
		}
		var_dump ($stat_matrix);
	}

	function	receivers_per_call (PDO $DB, $BENCHES, $FLAGS, $DEST)
	{
		$fh = fopen ($DEST."rpc.txt", "w");
		// Not currently used, this line needs to be updated if to be used in the future	
		fwrite ($fh, "=stackcluster;0;1;2;3;4;5+;\ncolors=grey7,grey6,grey5,grey4,grey3,grey2\nlegendx=6855\nlegendy=600\n=nogridy\n=noupperright\nxlabel=Receivers Per Call\nextraops=set size 1,1.2\n=table\n");

		foreach ($BENCHES as $bench)
		{
			$i = 0;
			foreach ($FLAGS as $flags)
			{
				$res = 0;
				for ($j = 0; $j <= 10; $j++)
				{	
					$res = get_stat ($DB, "methods_with_".$j."_receivers", $flags, $bench);	
					if (j <= 5)
					{
						if ($res == -1)
							$stat_matrix[$i][$j] = 0;
						else
							$stat_matrix[$i][$j] = $res;
					}
					else
					{
						if ($res != -1)
							$stat_matrix[$i][5] += $res;
					}
				}
		
				$i++;
			}
			fwrite ($fh, "multimulti=$bench
fci	".$stat_matrix[0][0]."  ".$stat_matrix[0][1]."  ".$stat_matrix[0][2]."  ".$stat_matrix[0][3]."  ".$stat_matrix[0][4]."  ".$stat_matrix[0][5]."
ci		".$stat_matrix[1][0]."  ".$stat_matrix[1][1]."  ".$stat_matrix[1][2]."  ".$stat_matrix[1][3]."  ".$stat_matrix[1][4]."  ".$stat_matrix[1][5]."
fi		".$stat_matrix[2][0]."  ".$stat_matrix[2][1]."  ".$stat_matrix[2][2]."  ".$stat_matrix[2][3]."  ".$stat_matrix[2][4]."  ".$stat_matrix[2][5]."
fcs	".$stat_matrix[3][0]."  ".$stat_matrix[3][1]."  ".$stat_matrix[3][2]."  ".$stat_matrix[3][3]."  ".$stat_matrix[3][4]."  ".$stat_matrix[3][5]."
\n");	
		}


	}


	
	function	precision_in_rw (PDO $DB, $BENCHES, $FLAGS, $DEST)
	{
		$fh = fopen ($DEST."pirw.txt", "w");
		// Not currently used, this line needs to be updated if to be used in the future	
		fwrite ($fh, "=stackcluster;Array;Field;\ncolors=grey7,grey2\nlegendx=5700\nlegendy=1500\nfontsz=7\n=nogridy\n=noupperright\nxlabel=Precision in Reads/Writes\nextraops=set label \"fci = flow and context insensitive\\nci = context insensitive\\nfi = flow insensitive\\nfcs = flow and context sensitive\" at 1,17 left font \"Times,10\"\n=table\n");
		
		$ir_nodes_reads = array ("IR_Nodes_dereferenced_reads_Array_access",
								"IR_Nodes_dereferenced_reads_Variable_variable",
								"IR_Nodes_dereferenced_reads_Field_access",	
								"IR_Nodes_dereferenced_reads_Array_next");

		$strg_nodes_reads = array ("storage_nodes_deref_reads_Array_access",
										"storage_nodes_deref_reads_Variable_variable",
										"storage_nodes_deref_reads_Field_access",
										"storage_nodes_deref_reads_Array_next");

		$ir_nodes_writes = array("IR_Nodes_dereferenced_writes_Assign_array",
										"IR_Nodes_dereferenced_writes_Assign_var_var",
										"IR_Nodes_dereferenced_writes_Assign_field",
										"IR_Nodes_dereferenced_writes_Assign_next");

		$strg_nodes_writes = array ("storage_nodes_deref_writes_Assign_array",
											"storage_nodes_deref_writes_Assign_var_var",
											"storage_nodes_deref_writes_Assign_field",
											"storage_nodes_deref_writes_Assign_next");


		foreach ($BENCHES as $bench)
		{
			$i = 0;
			foreach ($FLAGS as $flags)
			{
				for ($j = 0; $j < 4; $j++)
				{
					$num = (real) get_stat ($DB, $strg_nodes_reads[$j], $flags, $bench);
					$denom = (real) get_stat ($DB, $ir_nodes_reads[$j], $flags, $bench);
	
					if ($num == -1)
						$stat_matrix[$i][$j] = 0;
					else
						$stat_matrix[$i][$j] = $num/$denom;

				}
				$i++;
			}
			fwrite ($fh, "multimulti=$bench
fci	".$stat_matrix[0][0]."  ".$stat_matrix[0][2]."
ci		".$stat_matrix[1][0]."  ".$stat_matrix[1][2]."
fi		".$stat_matrix[2][0]."  ".$stat_matrix[2][2]."
fcs	".$stat_matrix[3][0]."  ".$stat_matrix[3][2]."
\n");	
		}
		foreach ($BENCHES as $bench)
		{
			$i = 0;
			foreach ($FLAGS as $flags)
			{
				for ($j = 0; $j < 4; $j++)
				{
					$num = (real) get_stat ($DB, $strg_nodes_writes[$j], $flags, $bench);	
					$denom = (real) get_stat ($DB, $ir_nodes_writes[$j], $flags, $bench);
 					
					if ($num == -1)
						$stat_matrix[$i][$j] = 0;
					else
						$stat_matrix[$i][$j] = $num/$denom;
				}
				$i++;
			}
			fwrite ($fh, "multimulti=$bench
fci	".$stat_matrix[0][0]."  ".$stat_matrix[0][2]."
ci		".$stat_matrix[1][0]."  ".$stat_matrix[1][2]."
fi		".$stat_matrix[2][0]."  ".$stat_matrix[2][2]."
fcs	".$stat_matrix[3][0]."  ".$stat_matrix[3][2]."
\n");	
		}

	}




	
	function ifs_replaced_constants (PDO $DB, $BENCHES, $FLAGS, $DEST)
	{
		$fh = fopen ($DEST."irc.txt", "w");
		fwrite ($fh, "=stackcluster;Branches After Optimisation;Branches Replaced With Constants;Branches Removed with DCE;\ncolors=grey7,grey6,grey5,grey4,grey3,grey2\nlegendx=2200\nlegendy=1400\nfontsz=7\n=nogridy\nextraops=set label \"fci = flow and context insensitive\\nci = context insensitive\\nfi = flow insensitive\\nfcs = flow and context sensitive\" at 3,3500 left font \"Times,10\"\nxlabelshift=0,1\n");

		foreach ($BENCHES as $bench)
		{
			$i = 0;
			foreach ($FLAGS as $flags)
			{
				$stat_matrix[$i][0] = (int) get_stat ($DB, "num_branches_after", $flags, $bench);
				$stat_matrix[$i][1] = get_stat ($DB, "num_branches_replaced_with_direction", $flags, $bench);
				$stat_matrix[$i][2] = get_stat ($DB, "num_branches_before", $flags, $bench) - $stat_matrix[$i][0] - $stat_matrix[$i][1];
				$i++;
			}	
		fwrite ($fh, "multimulti=$bench
fci	".$stat_matrix[0][0]."  ".$stat_matrix[0][1]."  ".$stat_matrix[0][2]."
ci		".$stat_matrix[1][0]."  ".$stat_matrix[1][1]."  ".$stat_matrix[1][2]."
fi		".$stat_matrix[2][0]."  ".$stat_matrix[2][1]."  ".$stat_matrix[2][2]."
fcs	".$stat_matrix[3][0]."  ".$stat_matrix[3][1]."  ".$stat_matrix[3][2]."
\n");	
		}
	}
	
	function	unreachable_statements (PDO $DB, $BENCHES, $FLAGS, $DEST)
	{
		$fh = fopen ($DEST."se.txt", "w");
		fwrite ($fh, "=stackcluster;Statements Remaining;Statements Eliminated;\ncolors=grey7,grey6,grey5,grey4,grey3,grey2\nlegendx=5600\nlegendy=1500\nfontsz=7\n=nogridy\nextraops=set label \"fci = flow and context insensitive\\nci = context insensitive\\nfi = flow insensitive\\nfcs = flow and context sensitive\" at 2.6,4100 left\nxlabelshift=0,1\n");

		foreach ($BENCHES as $bench)
		{
			$i = 0;
			foreach ($FLAGS as $flags)
			{
				$stat_matrix[$i][0] = get_stat ($DB, "num_statements_after", $flags, $bench);
				$stat_matrix[$i][1] = (int) get_stat ($DB, "num_statements_before", $flags, $bench) - (int) $stat_matrix[$i][0];
				$i++;
			}
		
		fwrite ($fh, "multimulti=$bench
fci	".$stat_matrix[0][0]."  ".$stat_matrix[0][1]."
ci		".$stat_matrix[1][0]."  ".$stat_matrix[1][1]."
fi		".$stat_matrix[2][0]."  ".$stat_matrix[2][1]."
fcs	".$stat_matrix[3][0]."  ".$stat_matrix[3][1]."
\n");	
		}
	}
	
	function get_stat ($db, $stat, $flag, $file)
	{
		$full_flag = get_full_flag ($flag, $file);
		$pdos = $db->query(
				"SELECT num FROM combined_results"
				.	" WHERE file == '$file'"
				.	" AND flags == '$flag'"
				.	" AND test == '$stat'");

		$result = $pdos->fetchColumn (0);

		if ($result === false)
		{
			return -1;
		}

		return $result;
	}

	function get_full_flag ($flag, $file)
	{	
		return "--include --include-harder -c -d include_path=$file $flag";
	}


?>
