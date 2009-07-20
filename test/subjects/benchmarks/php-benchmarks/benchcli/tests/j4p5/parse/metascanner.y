# Grammar for metascan

scanner: definition_list divider {return new preg_scanner_definition({0});}
| scanner rule {{0}->add_common_rule({1}); return {0};}
| scanner scope {{0}->add_rule_list({1}[0], {1}[1]); return {0};}

definition_list: definition* {return $tokens;}
definition: directive identifier+ {return $tokens;}

scope_list: scope_tag+ {return $tokens;}
scope:	scope_list rule {return array({0}, array({1}));}
| scope_list openbrace rule_list closebrace {return array({0}, {2});}

rule: regex modlist identifier behaviour action {return preg_pattern(metascanner::make_regex({0}, {1}), {2}, {3}, {4});}
rule_list: rule* {return $tokens;}
modlist: modifier* {return implode('', $tokens);}

behaviour: EPSILON {return 0;}
| ignore {return 1;}

action: EPSILON {return '';}
| openbrace code closebrace {return mk_action({1});}

code: (sstring|dstring|linecomment|blockcomment|php| openbrace code closebrace)* {return implode('', $tokens);}
