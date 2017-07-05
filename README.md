# PHC

phc is an open source compiler for PHP with support for plugins. In addition, it
can be used to pretty-print or obfuscate PHP code, as a framework for developing
applications that process PHP scripts, or to convert PHP into XML and back,
enabling processing of PHP scripts using XML tools.

Note: phc is unmaintained. It does compile some programs, and has an advanced
optimization framework. However, these are not for production use (notably they
lack support for objects!). It has an excellent program transformation framework
though, which unfortunately was last updated for PHP 5.2, and does not support
newer features. PRs will likely still be read, and if they pass the CircleCI
build, I may merge them.

~~See http://phpcompiler.org for more details.~~ Sadly, we allowed
phpcompiler.org's registration to lapse. See [the docs](doc) or
the [website source](https://github.com/pbiggar/phpcompiler.org) for the info
that used to be there.



## Building from source

After checking out via git, run

	$ touch src/generated/* Makefile.in configure Makefile libltdl/aclocal.m4 libltdl/Makefile.in libltdl/configure libltdl/Makefile
	$ ./configure
	$ make
	$ make install

For more detail, see (the manual)(doc/manual).

### OSX

There's a little bit of work to get it building on OSX:

    $ brew install homebrew/versions/boost155 xerces-c boehmgc
    $ LDFLAGS="-L/usr/local/opt/boost155/lib -L/usr/local/Cellar/bdw-gc/7.6.0/lib" CPPFLAGS="-I/usr/local/opt/boost155/include -I/usr/local/Cellar/bdw-gc/7.6.0/include" ./configure --disable-static --disable-gc
    



## Testing

The tests are held in [test/framework/](test/framework), but tests should be run
from this directory. `test/support_files/` are files used by the tests, for
example for regression. [test/subjects/](test/subjects) are the files used to
test phc. Most are designed to test some feature or tickle some bug.
test/subjects/labels controls what tests are run on which subjects. `test/logs/`
contains logs of failed tests. test/dependencies are used to avoid running a
test if we know it wont work because a previous test failed. `test/working`
contains the working directory for each test run.

To run tests:

	$ make test # aka make check

or

	$ make installcheck

or

	$ make long-test

or

	$ php test/framework/driver.php

The latter allows command line options, and limiting the tests with regular
expressions. Run `driver.php` with the `-h` flag for details.

In order to run tests on your own php files, add the files to
`test/subjects/3rdparty/`, and list them in `test/subjects/3rdparty/labels`. In
order to generate the support files, for example if you'd like the regression
tests to succeed rather than be skipped, run

	$ make generate-test-files

By default, 3rdparty tests are treated as 'long', so need to be run with

	$ make long-test

Its also straight-forward to test PHP's phpt test files:

- run the test suite on PHP (in PHP's directory: `$ TEST_PHP_EXECUTABLE=./sapi/cli/php --keep=php`). This creates .php files from the .phpt files
- link the PHP phpt directory from `test/subjects/3rdparty`.
- update `test/subjects/3rdparty/labels`
- Run the tests using the .php files.
- This doesnt provide the `EXPECT` functionality etc, but we dont really need that in the majority of cases.
