<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Get values from configure
 */

$valgrind = '/usr/bin/valgrind';
$graphviz_gc = '/usr/bin/gc';
$dot = '/usr/bin/dot';
$php_exe = '/usr/local/bin/php';
$gcc = 'ccache gcc';
$diff = '/usr/bin/diff';
$php_path = '/usr/local';
if ($php_path)
{
	$libphp = "$php_path/lib";
}
$bindir = '/home/pbiggar/phc_work/installed/bin';
$pkglibdir = '/home/pbiggar/phc_work/installed/lib/phc';
$phc_suffix = '';
$trunk_CPPFLAGS = '\'-I/usr/include  -I./src -I./3rdparty/getopt -I./src/generated -isystem/usr/local/include/php -isystem/usr/local/include/php/main -isystem/usr/local/include/php/TSRM -isystem/usr/local/include/php/Zend -DDATADIR="/home/pbiggar/phc_work/installed/share" -DPKGLIBDIR="/home/pbiggar/phc_work/installed/lib/phc" -Wall\'';
$xerces_compiled_in = 'yes';


?>
