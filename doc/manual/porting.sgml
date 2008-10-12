<chapter id="porting">
<title id="porting.title">Porting and Packaging</title>

<section>
<title>We need porters, packagers and maintainers</title>

<para>
	Now that &phc has a plugin architecture, it is no longer necessary for users
	to integrate their source with it. As a result, it is much more useful to
	package &phc and integrate it within various distributions' package
	management systems. If you are interested in packaging &phc for your
	favourite OS, please <ulink
	url="http://www.phpcompiler.org/mailinglist.html">contact us</ulink>.
</para>

<para>
	Currently, &phc runs on x86 Linux, and is mostly tested using Ubuntu. If you
	have access to other machines, architectures or operating systems, and would
	be willing to test &phc on it, please <ulink
	url="http://www.phpcompiler.org/mailinglist.html">contact us</ulink>.
</para>

</section>
<section>

<title>Packaging hints</title>

<para>
	Do not strip the binaries. Since the plugins use <code>dlopen()</code>, and
	link dynamically against the &phc binary, the plugins will not work unless
	the symbol information is available.
</para>

</section>
<section>

<title>Test suite</title>

<!-- TODO: update this paragraph -->
<para>
	&phc is shipped with its tests, which can be run after compilation:
</para>

<screen>
make test
</screen>

<para>
	You can also add your own code to <filename>test/subjects/3rdparty</filename>, and test it by running:
</para>

<screen>
make long-test
</screen>

<para>
	to run the entire suite. Note that many tests still fail. Please submit the
	results to us on the <ulink
	url="http://phpcompiler.org/mailinglist.html">mailing list</ulink>.
</para>

</section>
<section>

<title>&phc packages</title>

<para>
	See the <ulink url="http://www.phpcompiler.org/src">downloads page</ulink>
	for existing packages. In addition, we're looking for people to create
	and/or maintain packages for more systems, including Debian/Ubuntu
	(especially Debian/Ubuntu), Gentoo, Slackware, Darwin and Solaris.
</para>

</section>
