<?php

	$file_lists = array (
#		"run_tests/bench_lists/tiger.txt",
#		"run_tests/bench_lists/eve.txt",
#		"run_tests/bench_lists/mybloggie.txt",
		"run_tests/bench_lists/RUBiS.txt",
		"run_tests/bench_lists/RUBBoS.txt",
#		"run_tests/bench_lists/phpSQLiteAdmin.txt",
#		"run_tests/bench_lists/zend.txt",
		);

	// There are a list of files in run_test/benches.
	$all_files = read_from_bench_lists ($file_lists);

	// Each test belongs to a category
	$categories = array (
			"test/subjects/benchmarks/RUBBoS/PHP",
			"test/subjects/benchmarks/RUBiS",
			"test/subjects/benchmarks/webapps/eveactive_1.0",
			"test/subjects/benchmarks/webapps/mybloggie2.1.3_beta",
			"test/subjects/benchmarks/webapps/phpSQLiteAdmin-0.2",
			"test/subjects/benchmarks/webapps/tigerPhpNewsSystem_1.0_beta_build39",
			"test/subjects/benchmarks/zend/individual",
			);

	$flags = array (
		"",
		"--flow-insensitive ",
		"--call-string-length=1 ",
		"--flow-insensitive --call-string-length=1 ",
		);



	// What stats do we want to find:
	$stats = array (
#		"IR_Nodes_dereferenced_reads_Array_access",
#		"IR_Nodes_dereferenced_reads_Field_access",
#		"IR_Nodes_dereferenced_writes_Assign_array",
#		"IR_Nodes_dereferenced_writes_Assign_field",
		"bbs_analysed",
#		"bbs_analysed_in_iteration_0",
#		"bbs_analysed_in_iteration_1",
#		"bbs_analysed_in_iteration_2",
#		"bbs_analysed_in_iteration_3",
#		"bbs_analysed_in_iteration_4",
#		"bbs_analysed_in_iteration_5",
#		"defs",
#		"function_call_sites",
#		"functions_with_1_receivers",
#		"initialised_vars",
#		"may_defs",
#		"modelled_functions_analysed",
#		"num_array_access",
#		"num_array_def_sites",
#		"num_assign_array",
#		"num_assign_var",
#		"num_bin_op_lhs",
#		"num_blocks_removed",
#		"num_branches_replaced_with_direction",
#		"num_contexts",
#		"num_definite_reference_edges",
#		"num_field_edges",
#		"num_function_parameter",
#		"num_implicit_array_defs",
#		"num_implicit_object_defs",
#		"num_iterations",
#		"num_points_to_edges",
#		"num_possible_reference_edges",
#		"num_pre_op_var",
#		"num_reference_edges",
#		"num_return",
#		"num_statement_blocks",
#		"num_statements_after",
#		"num_statements_before",
#		"num_unary_op_var",
#		"num_unreachable_classes",
#		"num_unreachable_methods/functions",
#		"starred_defs",
#		"starred_initialised_vars",
#		"starred_may_defs",
		"starred_uses",
#		"statements_optimised",
#		"storage_nodes_deref_reads_Array_access",
#		"storage_nodes_deref_reads_Field_access",
#		"storage_nodes_deref_writes_Assign_array",
#		"storage_nodes_deref_writes_Assign_field",
#		"total_classes_used",
#		"total_num_bbs",
#		"total_num_methods/functions",
#		"total_num_types",
#		"total_num_unique_vars",
#		"total_num_vars",
#		"types_array_access",
#		"types_array_index",
#		"types_assign_array",
#		"types_assign_var",
#		"types_bin_op_lhs",
#		"types_bin_op_rhs",
#		"types_function_parameter",
#		"types_pre_op_var",
#		"types_return",
#		"types_unary_op_var",
#		"unstarred_defs",
#		"unstarred_may_defs",
#		"unstarred_uses",
#		"uses",
	);


	// Start looking in the database
	$db_filename = $argv[1];

	echo "Looking in database: $db_filename\n";
	$DB = new PDO ("sqlite:$db_filename");


	// Check that we have some result in the database for the file in question
	check_presence ($DB, $stats, $all_files);




	function read_from_bench_lists ($lists)
	{
		$result = array ();

		foreach ($lists as $list)
		{
			l ("Using file list: $list");
			$lines = file ($list, FILE_SKIP_EMPTY_LINES | FILE_IGNORE_NEW_LINES);
			$result = array_merge ($result, $lines);
		}

		return $result;
	}



	
	function check_presence ($db, $stats, $files)
	{
		global $flags;
		foreach ($stats as $stat)
		{
			foreach ($files as $file)
			{
				foreach ($flags as $flag)
				{
					get_stat ($db, $stat, $flag, $file);
				}
			}
		}
	}

	function get_stat ($db, $stat, $flag, $file)
	{
		$full_flag = get_full_flag ($flag, $file);
		$pdos = q($db,
				"SELECT num FROM results"
				.	" WHERE file == '$file'"
				.	" AND flags == '$full_flag'"
				.	" AND test == '$stat'");

		$result = $pdos->fetchColumn (0);


		if ($result == 0)
		{
			die ("...");
			l ("returning zero for missing stat: $stat, '$flag', $file");
			return 0;
		}

		l ("returning $result for found stat: $stat, '$flag', $file");
	}

	function get_full_flag ($flag, $file)
	{
		$name = dirname ($file);
		return "--include --include-harder -c -d include_path=$name $flag";
	}

	function q ($db, $query)
	{
		l ("$query;");
		return $db->query ($query);
	}

	function l ($msg)
	{
		echo "$msg\n";
	}

?>
