.. |phc| replace:: **phc**


Porting
=======

Porting and Packaging
---------------------


We need porters, packagers and maintainers
******************************************

Now that |phc| has a plugin architecture, it is no longer necessary for users
to integrate their source with it. As a result, it is much more useful to
package |phc| and integrate it within various distributions' package
management systems. If you are interested in packaging |phc| for your
favourite OS, please `contact us <http://www.phpcompiler.org/mailinglist.html>`_.

Currently, |phc| runs on x86 Linux, and is mostly tested using Ubuntu. If you
have access to other machines, architectures or operating systems, and would be
willing to test |phc| on it, please `contact us
<http://www.phpcompiler.org/mailinglist.html>`_.

Packaging hints
***************

Do not strip the binaries. Since the plugins use ``dlopen()``, and link
dynamically against the |phc| binary, the plugins will not work unless the
symbol information is available.

Test suite
**********

.. todo:: update this paragraph

|phc| is shipped with its tests, which can be run after compilation: ::

   make test


You can also add your own code to ``test/subjects/3rdparty/``, and test it by running: ::

   make long-test

to run the entire suite. Note that many tests still fail. Please submit the
results to us on the `mailing list <http://phpcompiler.org/mailinglist.html>`_.

|phc| packages
**************

See the `downloads page <http://www.phpcompiler.org/downloads.html>`_ for
existing packages. In addition, we're looking for people to create and/or
maintain packages for more systems, including Debian/Ubuntu (especially
Debian/Ubuntu), Gentoo, Slackware, Darwin and Solaris.
