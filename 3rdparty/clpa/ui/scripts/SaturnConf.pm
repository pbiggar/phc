##
# Authors:
#   Ryan Propper   <rpropper@stanford.edu>
#
# Copyright (c) 2006,
#   The Board of Trustees of The Leland Stanford Junior University
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
# 
# 3. The names of the contributors may not be used to endorse or promote
# products derived from this software without specific prior written
# permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
##

package SaturnConf;

use strict;

sub readConfigFile {
  my($self, $fileName) = @_;
  my $configOptions;

  if (not (-e $fileName)) {
    print "Could not find configuration file $fileName\n";
    exit 1;
  }

  open(CONFIG_FILE, "$fileName");
  while (my $curLine = <CONFIG_FILE>) {
    chomp $curLine;
    if($curLine =~ /^(\w+) /) {
      my $key = $1;
      $curLine =~ s/^\w+ //;
      $configOptions->{$key} = $curLine;
    }
  }
  close(CONFIG_FILE);

  return $configOptions;
}

sub print_configuration_error {
  my $key = shift;
  print "ERROR: Configuration file missing '$key'\n";
  exit 1;
}

# keys which must be in the configuration or failure
sub queryConfig {
  my ($self,$configOptions,$key) = @_;

  my $value = $configOptions->{$key} or print_configuration_error $key;
  return $value;
}

# keys which might be in the configuration
sub maybeConfig {
  my ($sefl,$configOptions,$key) = @_;
  my $value = $configOptions->{$key};
  return $value;
}

1;
__END__
