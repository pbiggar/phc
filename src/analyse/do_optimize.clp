import "optimize.clp".
import "cfgdot.clp".

analyze session_name("cfg").

% Alias-analysis (ahem)
import "address_taken.clp".

% Dead-code elimination.
import "dce.clp".

% Copy propagation
%import "copyprop.clp".

import "errors.clp".

% After optimizations, iterate, generating a new version of the CFG, until it
% converges.
import "do_versioning.clp".

% Turn the CFG back into a list of statements with gotos and labels.
import "linearize_cfg.clp".
