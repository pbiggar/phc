<?php

	require ("parsing/scalar_array.php");

	$scalar_array = $short_scalar_array;

	foreach ($scalar_array as $scalar)
	{
		foreach ($scalar_array as $i)
		{
			echo "Working with ";
			var_dump ($scalar);

			echo "\nUnset single level (", gettype($i), ": $i)\n";
			$x = $scalar;

			// Ignore strings
			if (is_string ($x))
			{
				echo "skip\n";
				continue;
			}

			unset ($x[$i]);
			var_dump ($x);

			foreach ($scalar_array as $j)
			{
				echo "\nUnset two levels (", gettype ($i), ": $i, ", gettype ($j), ": $j)\n";
				$x = $scalar;

				// Ignore strings
				if (is_string ($x[$i]))
				{
					echo "skip\n";
					continue;
				}

				unset ($x[$i][$j]);
				var_dump ($x);

				foreach ($scalar_array as $k)
				{
					echo "\nUnset 3 levels (", gettype ($i), ": $i, ", gettype ($j), ": $j, ", gettype ($k), ": $k))\n";
					$x = $scalar;

					// Ignore strings
					if (is_string ($x[$i][$j]))
					{
						echo "skip\n";
						continue;
					}

					unset ($x[$i][$j][$k]);
					var_dump ($x);
				}
			}
		}
	}
	
?>
