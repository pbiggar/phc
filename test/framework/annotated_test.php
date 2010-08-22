<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that all scripts parse, with expected errors taken into account.
 */

require_once ("lib/async_test.php");

// We annotate tests in the deja-gnu style - in a comment, wrapped in
// braces, in the form "name: value". Annotations are processed before and
// after the bundle is run, even if the annotation is not specified. This
// allows editing the command line (as in phc-option), asserting contents of
// the output, or checking exit codes (including default values).
abstract class Test_annotation
{
	function __construct ()
	{
		$this->values = array ();
	}

	function add_value ($options, $value)
	{
		phc_assert (preg_match ("~{$this->value_regex}~", $value), "Value ($value )provided does not match regex ({$this->value_regex})");
		$this->options[] = array_merge ($this->get_default_options(), $options);
		$this->values[] = $value;
	}

	// Classes with a default value are added automatically with the default, if they are not otherwise added.
	function get_default_value ()
	{
		return NULL;
	}

	// Merge these with the actual options
	function get_default_options ()
	{
		return array ();
	}

	function get_dependencies () { return array ();}
	function pre_process ($bundle) {}
	function post_process ($bundle) {}
}

class PHC_option_annotation extends Test_annotation
{
	function __construct ()
	{
		parent::__construct ();
		$this->name = "phc-option";
		$this->value_description = "Command-line option to phc";
		$this->value_regex = "\S+";
	}

	function pre_process ($bundle)
	{
		foreach ($this->values as $value)
			$bundle->commands[0] .= " $value";
	}
};

class PHC_exit_code_annotation extends Test_annotation
{
	function __construct ()
	{
		parent::__construct ();
		$this->name = "phc-exit-code";
		$this->value_description = "phc exit-code";
		$this->value_regex = "\!?\d+";
	}

	function post_process ($bundle)
	{
		phc_assert (count ($this->values) == 1, "Cant have more than 1 exit code");

		$expected = $this->values[0];
		if ($expected[0] === "!")
		{
			$complement = true;
			$expected[0] = "0";
		}
		else
			$complement = false;

		$expected = (int)$expected;

		if (($complement && $expected === $bundle->exits[0])
			|| 
			(!$complement && $expected !== $bundle->exits[0]))
			return "Incorrect exit code: {$bundle->exits[0]} (expected: $expected)";
	}

	function get_default_value ()
	{
		return "0";
	}
};

/* Warnings and errors both use stderr */
class PHC_output_annotation extends Test_annotation
{
	function __construct ()
	{
		parent::__construct ();
		$this->name = "phc-stdout";
		// either
		$this->value_regex = "(!?/.*/)|([^/])|([^/].*[^/])";
	}

	function get_default_options ()
	{
		return array (
			"regex" => false,		// use a regex
			"stderr" => false,	// use stderr (default, use stdout)
			"prefix" => "",		// Error prefix (ie "Error", "Warning")
			"location" => false,	// Use location info (filename: linenumber)
			);
	}

	function post_process ($bundle)
	{
		foreach ($this->values as $value)
		{
			$options = array_shift ($this->options);

			$negate = false;
			// Process the options
			if (!$options["regex"])
				$value = preg_quote ($value, "/");
			else
			{
				if ($value[0] == "!")
				{
					$negate = true;
					$value = substr ($value, 1); // remove !
				}

				phc_assert ($value[0] == "/", "regexes must start with \"/\" or \"!/\"");
				phc_assert ($value[strlen($value)-1] == "/", "regexes must end with \"/\"");

				// remove '/' at front and back
				$value = substr ($value, 1, strlen ($value) - 2);
			}

			if ($options["stderr"])
			{
				$out = $bundle->errs[0];

				// tests which expect stderr will only work on this test.
				$bundle->expected_failure = true;
			}
			else
				$out = $bundle->outs[0];

			if ($options["prefix"])
				$value = "{$options['prefix']}: $value";

			if ($options["location"])
			{
				$pattern = "!^[^:]+:\d+: $value\n"
					."Note that line numbers are inaccurate, and will be fixed "
					."in a later release\n!ms";
			}
			else
				$pattern = "/$value/ms";

			$result = preg_match ($pattern, $out, $matches);

			// Potential errors
			$suffix = "\"$value\" using pattern \"$pattern\"";
			if ($negate)
			{
				if ($result === 1)
					return "{$options['prefix']} found ({$matches[0]}), not expected: $suffix";
			}
			else
			{
				if ($result === 0)
					return "{$options['prefix']} not found, expected: $suffix";

				if ($result === FALSE)
					return "Test annotation error with: $suffix";

				if ($result !== 1)
					return "Unexpected error with: $suffix";
			}
		}
	}
}

// Just create a dependency, with the specifed name.
class Annotation_translator extends Test_annotation
{
	function __construct ($name, $description, $translations, $extras = array())
	{
		parent::__construct ();
		$this->name = $name;
		$this->description = $description;
		$this->translations = $translations;
		$this->extras = $extras;
		$this->value_regex = ".*";

		// Allow passing strings when arrays expected
		if (!is_array ($translations))
			$this->translations = array ($translations);

		if (!is_array ($extras))
			$this->extras = array ($extras);
	}

	function get_dependencies ()
	{
		$result = array ();
		foreach ($this->values as $value)
			foreach ($this->translations as $translation)
				$result[] = "$translation: $value";

		// extras just go in as is
		foreach ($this->extras as $extra)
			$result[] = "$extra";

		// Having processed the dependencies, we dont want to use them again.
		$this->values = array ();
		$this->extras = array ();

		return $result;
	}
}

function get_available_annotations ()
{
	$annotations = array (
				new PHC_option_annotation,
				new PHC_output_annotation,
				new PHC_exit_code_annotation,
				// All the others can be converted to PHC_output_annotation

				// Errors
				new Annotation_translator (
					"phc-regex-error",
					"Error in PHP script, as a regex",
					"phc-stdout (stderr,regex,prefix=Error,location)",
					"phc-exit-code: !0"),
				new Annotation_translator (
					"phc-error",
					"Error in PHP script",
					"phc-stdout (stderr,prefix=Error,location)",
					"phc-exit-code: !0"),
				new Annotation_translator (
					"phc-usage-error",
					"Incorrect usage of phc command line",
					"phc-stdout (stderr,prefix=Error)",
					"phc-exit-code: !0"),

				// Warnings
				new Annotation_translator (
					"phc-regex-warning",
					"Warning about PHP script, as a regex",
					"phc-stdout (stderr,regex,prefix=Warning,location)"),
				new Annotation_translator (
					"phc-warning",
					"Warning about PHP script",
					"phc-stdout (stderr,prefix=Warning,location)"),

				// Output
				new Annotation_translator (
					"phc-regex-output",
					"Extract of phc output matches regex",
					"phc-stdout (stdout,regex)"),
				new Annotation_translator (
					"phc-output",
					"Extract of phc output",
					"phc-stdout (stdout)"),
				new Annotation_translator (
					"phc-debug",
					"Extract of phc debugging information",
					"phc-stdout (stderr,name=Debug)"),

				);

	$result = array ();
	foreach ($annotations as $annotation)
		$result [$annotation->name] = $annotation;

	return $result;
}

// Converts from the form "(stderr,prefix=Error,location)" to a hashtable of
// keyword,value pairs. If no value given, the keyword is set with true.
function parse_options ($options)
{
	if ($options == "")
		return array ();

	$split = explode (",", $options);
	foreach ($split as $key_pair)
	{
		if (strpos ($key_pair, "=") === FALSE)
			$result[$key_pair] = true;
		else
		{
			list ($key, $pair) = explode ("=", $key_pair);
			$result[$key] = $pair;
		}
	}

	return $result;
}

class Annotated_test extends AsyncTest
{
	function get_test_subjects ()
	{
		return get_all_scripts();
	}

	function run_test ($subject)
	{
		$bundle = new AsyncBundle ($this, $subject);

		$bundle->annotations = $this->get_annotations ($subject);
		$bundle->commands[0] = get_phc_command_line ($subject);
		$bundle->final = "finish";

		foreach ($bundle->annotations as $annotation)
			$annotation->pre_process ($bundle);

		$bundle->start ();
	}

	function finish ($bundle)
	{
		// Check for annotations
		foreach ($bundle->annotations as $annotation)
		{
			$failure = $annotation->post_process ($bundle);
			if ($failure)
			{
				$this->async_failure ($failure, $bundle);
				return;
			}
		}

		$this->async_success ($bundle);

		// Mark if the success was an expected failure
		if (isset ($bundle->expected_failure) && $bundle->expected_failure)
		{
			$this->solo_tests++;
			write_dependencies ($this->get_name (), $bundle->subject, false);
		}
	}

	function get_annotations ($subject)
	{
		$out = file_get_contents ($subject);

		$available = get_available_annotations();
		$triples = array ();

		// match the annotations 
		$lines = explode ("\n", $out);
		$pregs = array ("/#(.*)$/", "/\/\/(.*)$/", "/\/\*(.*)\*\//");
		foreach ($lines as $line)
		{
			foreach ($pregs as $preg) // Match single line comments
			{
				if (preg_match ("$preg", $line, $line_match))
				{
					if (preg_match (		// match "{ name (options): value }"
							"/\s*
								{						# start matching string
									\s*
									(\S+				# start match with name
									\s*
									(\(.*?\))?		# match optional argument
									:
									\s*
									\S.*\S)			# end match with value
									\s*
								}						# finish match
							\s*/x",
							$line_match[1], $comment_match))
					{
						$triples[] = $comment_match[1];
					}
				}
			}
		}

		// Extract the annotations, adding dependencies and options.
		$result = array ();
		while (count ($triples) > 0)
		{
			$triple = array_shift ($triples);

			// match "name (options): value
			preg_match (
					"/^
						(\S+)				# match name
						\s*
						(?:				# dont put this group into the result
							\(
								(.*?)		# match options, but not the brackets
							\)	
						)?					# options is optional
						:
						\s*
						(\S.*\S)			# match value
						\s*
					$/x",
					$triple, $triple_match);

			$name = $triple_match[1];
			$options = parse_options ($triple_match[2]);
			$value = $triple_match[3];
			phc_assert (isset($available[$name]), 
					"Annotation $name not available, in $subject");

			$available[$name]->add_value ($options, $value);
			$result[$name] = $available[$name];

			$triples = array_merge ($available[$name]->get_dependencies (), $triples);
		}

		// Add default that hasnt been added.
		foreach ($available as $name => $annotation)
		{
			if (count ($annotation->values) == 0 && $annotation->get_default_value() !== NULL)
			{
				$annotation->add_value ($annotation->get_default_options (), $annotation->get_default_value ());
				$result[] = $annotation;
			}
		}

		return $result;
	}

	# we override tests run in order to add a line at the end
	function run ()
	{
		parent::run ();
		$num_skipped = $this->solo_tests;
		echo "($num_skipped solo tests)\n";
	}
}
array_push($tests, new Annotated_test());

?>
