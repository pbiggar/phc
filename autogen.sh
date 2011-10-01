#!/bin/bash

set -exou pipefail
# autotools invocations are hard to get right.

aclocal -I m4 -I libltdl
autoconf
automake

set +x
echo "To build phc, run \"./configure\" followed by \"make\""
