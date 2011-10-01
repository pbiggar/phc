#!/bin/bash

set -x
function add-autoconf-archive-dir {
  if [ -d "$1" ] ; then
    AUTOCONF_ARCHIVES+=" -I $1"
  fi
}

# Ubuntu
add-autoconf-archive-dir "/usr/share/aclocal"

# Mac OS X - MacPorts
# As of late-2010, MacPorts uses autoconf-archive from 2008.
add-autoconf-archive-dir "/opt/local/share/aclocal"

# Mac OS X - homebrew
add-autoconf-archive-dir "/usr/local/share/aclocal"

# autotools invocations are hard to get right.

aclocal -I m4 -I libltdl $AUTOCONF_ARCHIVES
autoconf
automake

set +x
echo "To build phc, run \"./configure\" followed by \"make\""
