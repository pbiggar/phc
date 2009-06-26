<?php
// This file is dynamically generated from js.l and js.y by metaphp's CFG parser
// Do not waste your time editing it or reading it. Move along. Thank you.

function __lambda_1 (&$type, &$text, $match, &$state, &$context) {
$context++; $state="code";
}
function __lambda_2 (&$type, &$text, $match, &$state, &$context) {
$context--; if ($context <= 0) $state = "rule";
}
function __lambda_3 (&$type, &$text, $match, &$state, &$context) {
$text = substr($text,1);
}
function __lambda_4 (&$type, &$text, $match, &$state, &$context) {
$text = substr($text,1,strlen($text)-2);
}
function __lambda_5 (&$type, &$text, $match, &$state, &$context) {
$state = 'rule';
}
function __lambda_6 (&$type, &$text, $match, &$state, &$context) {
$state = 'regex';
}
function __lambda_7 (&$type, &$text, $match, &$state, &$context) {
if ($text=='ignore') $type='ignore';
}
function __lambda_8 (&$type, &$text, $match, &$state, &$context) {
$context--; if ($context <= 0) $state = "INITIAL";
}
function __lambda_9 ($tokens) {
return new preg_scanner_definition($tokens[0]);
}
function __lambda_10 ($tokens) {
$tokens[0]->add_common_rule($tokens[1]); return $tokens[0];
}
function __lambda_11 ($tokens) {
$tokens[0]->add_rule_list($tokens[1][0], $tokens[1][1]); return $tokens[0];
}
function __lambda_12 ($tokens) {
return $tokens;
}
function __lambda_13 ($tokens) {
return array($tokens[0], array($tokens[1]));
}
function __lambda_14 ($tokens) {
return array($tokens[0], $tokens[2]);
}
function __lambda_15 ($tokens) {
return preg_pattern(metascanner::make_regex($tokens[0], $tokens[1]), $tokens[2], $tokens[3], $tokens[4]);
}
function __lambda_16 ($tokens) {
return implode('', $tokens);
}
function __lambda_17 ($tokens) {
return 0;
}
function __lambda_18 ($tokens) {
return 1;
}
function __lambda_19 ($tokens) {
return '';
}
function __lambda_20 ($tokens) {
return mk_action($tokens[1]);
}
function __lambda_21 (&$type, &$text, $match, &$state, &$context) {
$state='text';
}
function __lambda_22 (&$type, &$text, $match, &$state, &$context) {
 $text = hexdec($text); 
}
function __lambda_23 (&$type, &$text, $match, &$state, &$context) {
 $text = $text-0; 
}
function __lambda_24 (&$type, &$text, $match, &$state, &$context) {
$state='INITIAL';
}
function __lambda_25 ($tokens) {
 return new js_program($tokens[0]); 
}
function __lambda_26 ($tokens) {
 return new js_source(); 
}
function __lambda_27 ($tokens) {
 $tokens[0]->addStatement($tokens[1]); return $tokens[0]; 
}
function __lambda_28 ($tokens) {
 $tokens[0]->addFunction(new js_function_definition($tokens[1])); return $tokens[0]; 
}
function __lambda_29 ($tokens) {
 return array($tokens[1],array(),$tokens[5]); 
}
function __lambda_30 ($tokens) {
 return array($tokens[1],$tokens[3],$tokens[6]); 
}
function __lambda_31 ($tokens) {
 return new js_function_definition(array('',array(),$tokens[4])); 
}
function __lambda_32 ($tokens) {
 return new js_function_definition(array($tokens[1],array(),$tokens[5])); 
}
function __lambda_33 ($tokens) {
 return new js_function_definition(array('',$tokens[2],$tokens[5])); 
}
function __lambda_34 ($tokens) {
 return new js_function_definition(array($tokens[1],$tokens[3],$tokens[6])); 
}
function __lambda_35 ($tokens) {
return array($tokens[0]);
}
function __lambda_36 ($tokens) {
 $tokens[0][]=$tokens[2]; return $tokens[0]; 
}
function __lambda_37 ($tokens) {
return $tokens[0];
}
function __lambda_38 ($tokens) {
 return new js_nop(); 
}
function __lambda_39 ($tokens) {
 return new js_print($tokens[2]); 
}
function __lambda_40 ($tokens) {
 return new js_print(new js_literal_string($tokens[1],0)); 
}
function __lambda_41 ($tokens) {

    return new js_print(js_plus(new js_literal_string($tokens[1],0), $tokens[3]));

}
function __lambda_42 ($tokens) {
return new js_nop();
}
function __lambda_43 ($tokens) {
return new js_block($tokens[1]);
}
function __lambda_44 ($tokens) {
 return array($tokens[0]);
}
function __lambda_45 ($tokens) {
 $tokens[0][]=$tokens[1]; return $tokens[0];
}
function __lambda_46 ($tokens) {
 
  return new js_var($tokens[1]);

}
function __lambda_47 ($tokens) {
 return array($tokens[0]); 
}
function __lambda_48 ($tokens) {
 return @array($tokens[0],$tokens[1]);
}
function __lambda_49 ($tokens) {
 return $tokens[1]; 
}
function __lambda_50 ($tokens) {
 return new js_nop();
}
function __lambda_51 ($tokens) {
return new js_statement($tokens[0]);
}
function __lambda_52 ($tokens) {

  return new js_if($tokens[2], $tokens[4], $tokens[6]);

}
function __lambda_53 ($tokens) {

  return new js_if($tokens[2], $tokens[4]);

}
function __lambda_54 ($tokens) {
 return new js_do($tokens[4],$tokens[1]); 
}
function __lambda_55 ($tokens) {
 return new js_while($tokens[2], $tokens[4]); 
}
function __lambda_56 ($tokens) {
return new js_for_in($tokens[2], $tokens[4], $tokens[6]);
}
function __lambda_57 ($tokens) {

    $k=2;
    if ($tokens[$k]==';') { $a1=new js_nop(); $k++; } 
    else { $a1=$tokens[$k]; $k+=2; }
    if ($tokens[$k]==';') { $a2=new js_nop(); $k++; } 
    else { $a2=$tokens[$k]; $k+=2; }
    if ($tokens[$k]==')') { $a3=new js_nop(); $k++; } 
    else { $a3=$tokens[$k]; $k+=2; }
    $a4=$tokens[$k];
    return new js_for($a1,$a2,$a3,$a4);

}
function __lambda_58 ($tokens) {

    $k=5;
    if ($tokens[$k]==';') { $a2=new js_nop(); $k++; }
    else { $a2=$tokens[$k]; $k+=2; }
    if ($tokens[$k]==')') { $a3=new js_nop(); $k++; }
    else { $a3=$tokens[$k]; $k+=2; }
    $a4=$tokens[$k];
    return new js_for( new js_var($tokens[3]), $a2, $a3, $a4);

}
function __lambda_59 ($tokens) {
return new js_for_in( new js_var($tokens[3]), $tokens[5], $tokens[7]);
}
function __lambda_60 ($tokens) {
return @new js_continue($tokens[1]);
}
function __lambda_61 ($tokens) {
return @new js_break($tokens[1]);
}
function __lambda_62 ($tokens) {
return @new js_return($tokens[1]);
}
function __lambda_63 ($tokens) {
return new js_with($tokens[2],$tokens[4]);
}
function __lambda_64 ($tokens) {

  return new js_switch($tokens[2], $tokens[4]);

}
function __lambda_65 ($tokens) {
if ($tokens[1]=='}') return array(); else return $tokens[1];
}
function __lambda_66 ($tokens) {

  return $tokens[1];

}
function __lambda_67 ($tokens) {

  return array_merge($tokens[1],$tokens[2]);

}
function __lambda_68 ($tokens) {

  return array_merge($tokens[1],$tokens[2],$tokens[3]);

}
function __lambda_69 ($tokens) {
$tokens[0][] = $tokens[1]; return $tokens[0];
}
function __lambda_70 ($tokens) {
return new js_case($tokens[1],$tokens[3]);
}
function __lambda_71 ($tokens) {
return array(new js_case(0, $tokens[2]));
}
function __lambda_72 ($tokens) {
return new js_label($tokens[0], $tokens[1]);
}
function __lambda_73 ($tokens) {
return new js_throw($tokens[1]);
}
function __lambda_74 ($tokens) {
return new js_try($tokens[1],$tokens[2], NULL);
}
function __lambda_75 ($tokens) {
return new js_try($tokens[1], NULL, $tokens[2]);
}
function __lambda_76 ($tokens) {
return new js_try($tokens[1], $tokens[2], $tokens[3]);
}
function __lambda_77 ($tokens) {
return new js_catch($tokens[2], $tokens[4]);
}
function __lambda_78 ($tokens) {
 return $tokens[1];
}
function __lambda_79 ($tokens) {
 return new js_this();
}
function __lambda_80 ($tokens) {
 return new js_identifier($tokens[0]);
}
function __lambda_81 ($tokens) {
 return $tokens[0]; 
}
function __lambda_82 ($tokens) {
 return new js_literal_null(); 
}
function __lambda_83 ($tokens) {
 return new js_literal_boolean($tokens[0]); 
}
function __lambda_84 ($tokens) {
 return new js_literal_number($tokens[0]); 
}
function __lambda_85 ($tokens) {
return TRUE;
}
function __lambda_86 ($tokens) {
return FALSE;
}
function __lambda_87 ($tokens) {
return new js_literal_string($tokens[0]);
}
function __lambda_88 ($tokens) {
return new js_literal_array($tokens[1]);
}
function __lambda_89 ($tokens) {
$tokens[0][] = $tokens[2]; return $tokens[0];
}
function __lambda_90 ($tokens) {
return new js_literal_null();
}
function __lambda_91 ($tokens) {
return new js_literal_object();
}
function __lambda_92 ($tokens) {
return new js_literal_object($tokens[1]);
}
function __lambda_93 ($tokens) {
return array($tokens[0],$tokens[2]);
}
function __lambda_94 ($tokens) {
$p=explode(':', $tokens[0]); return array(new js_literal_string($p[0],0),$tokens[1]);
}
function __lambda_95 ($tokens) {
$tokens[0][]=$tokens[2];$tokens[0][]=$tokens[4];return $tokens[0];
}
function __lambda_96 ($tokens) {
$p=explode(':', $tokens[2]); $tokens[0][]=new js_literal_string($p[0],0);$tokens[0][]=$tokens[3]; return $tokens[0];
}
function __lambda_97 ($tokens) {
return new js_literal_string($tokens[0],0);
}
function __lambda_98 ($tokens) {
return new js_literal_number($tokens[0]);
}
function __lambda_99 ($tokens) {
return new js_accessor($tokens[0],$tokens[2],1);
}
function __lambda_100 ($tokens) {
return new js_accessor($tokens[0],new js_identifier($tokens[2]),0);
}
function __lambda_101 ($tokens) {
return new js_new($tokens[1]);
}
function __lambda_102 ($tokens) {
return new js_call($tokens[0],$tokens[1]);
}
function __lambda_103 ($tokens) {
return array(); 
}
function __lambda_104 ($tokens) {
return (array)$tokens[1];
}
function __lambda_105 ($tokens) {
$tokens[0][]=$tokens[2];return $tokens[0];
}
function __lambda_106 ($tokens) {
return new js_post_pp($tokens[0]);
}
function __lambda_107 ($tokens) {
return new js_post_mm($tokens[0]);
}
function __lambda_108 ($tokens) {
return new js_delete($tokens[1]);
}
function __lambda_109 ($tokens) {
return new js_void($tokens[1]);
}
function __lambda_110 ($tokens) {
return new js_typeof($tokens[1]);
}
function __lambda_111 ($tokens) {
return new js_pre_pp($tokens[1]);
}
function __lambda_112 ($tokens) {
return new js_pre_mm($tokens[1]);
}
function __lambda_113 ($tokens) {
return new js_u_plus($tokens[1]);
}
function __lambda_114 ($tokens) {
return new js_u_minus($tokens[1]);
}
function __lambda_115 ($tokens) {
return new js_bit_not($tokens[1]);
}
function __lambda_116 ($tokens) {
return new js_not($tokens[1]);
}
function __lambda_117 ($tokens) {
return new js_multiply($tokens[0],$tokens[2]);
}
function __lambda_118 ($tokens) {
return new js_divide($tokens[0],$tokens[2]);
}
function __lambda_119 ($tokens) {
return new js_modulo($tokens[0],$tokens[2]);
}
function __lambda_120 ($tokens) {
return new js_plus($tokens[0],$tokens[2]);
}
function __lambda_121 ($tokens) {
return new js_minus($tokens[0],$tokens[2]);
}
function __lambda_122 ($tokens) {
return new js_lsh($tokens[0],$tokens[2]);
}
function __lambda_123 ($tokens) {
return new js_rsh($tokens[0],$tokens[2]);
}
function __lambda_124 ($tokens) {
return new js_ursh($tokens[0],$tokens[2]);
}
function __lambda_125 ($tokens) {
return 	$tokens[0];
}
function __lambda_126 ($tokens) {
return new js_lt($tokens[0],$tokens[2]);
}
function __lambda_127 ($tokens) {
return new js_gt($tokens[0],$tokens[2]);
}
function __lambda_128 ($tokens) {
return new js_lte($tokens[0],$tokens[2]);
}
function __lambda_129 ($tokens) {
return new js_gte($tokens[0],$tokens[2]);
}
function __lambda_130 ($tokens) {
return new js_instanceof($tokens[0],$tokens[2]);
}
function __lambda_131 ($tokens) {
return new js_in($tokens[0],$tokens[2]);
}
function __lambda_132 ($tokens) {
return new js_equal($tokens[0],$tokens[2]);
}
function __lambda_133 ($tokens) {
return new js_not_equal($tokens[0],$tokens[2]);
}
function __lambda_134 ($tokens) {
return new js_strict_equal($tokens[0],$tokens[2]);
}
function __lambda_135 ($tokens) {
return new js_strict_not_equal($tokens[0],$tokens[2]);
}
function __lambda_136 ($tokens) {
return new js_bit_and($tokens[0],$tokens[2]);
}
function __lambda_137 ($tokens) {
return new js_bit_xor($tokens[0],$tokens[2]);
}
function __lambda_138 ($tokens) {
return new js_bit_or($tokens[0],$tokens[2]);
}
function __lambda_139 ($tokens) {
return new js_and($tokens[0],$tokens[2]);
}
function __lambda_140 ($tokens) {
return new js_or($tokens[0],$tokens[2]);
}
function __lambda_141 ($tokens) {
return new js_ternary($tokens[0],$tokens[2],$tokens[4]);
}
function __lambda_142 ($tokens) {
return new js_assign($tokens[0],$tokens[2]);
}
function __lambda_143 ($tokens) {
return new js_compound_assign($tokens[0],$tokens[2],$tokens[1]);
}
function __lambda_144 ($tokens) {
return new js_comma($tokens[0],$tokens[2]);
}
$lexp = array (
  'INITIAL' => 
  array (
    0 => 
    array (
      0 => '((?s)/\\*.*?\\*/)',
      1 => 'mlcomment',
      2 => 1,
      3 => '',
    ),
    1 => 
    array (
      0 => '((?)//[^\\x0A\\x0D]*)',
      1 => 'slcomment',
      2 => 1,
      3 => '',
    ),
    2 => 
    array (
      0 => '((?)[\\x0A\\x0D])',
      1 => 'newline',
      2 => 1,
      3 => '',
    ),
    3 => 
    array (
      0 => '((?)\\s+)',
      1 => 'whitespace',
      2 => 1,
      3 => '',
    ),
    4 => 
    array (
      0 => '((?)\\?\\>)',
      1 => 'T_SCRIPT_END',
      2 => 0,
      3 => '__lambda_21',
    ),
    5 => 
    array (
      0 => '((?)\\bfunction\\b)',
      1 => 'T_FUNCTION',
      2 => 0,
      3 => '',
    ),
    6 => 
    array (
      0 => '((?)\\bvar\\b)',
      1 => 'T_VAR',
      2 => 0,
      3 => '',
    ),
    7 => 
    array (
      0 => '((?)\\bdo\\b)',
      1 => 'T_DO',
      2 => 0,
      3 => '',
    ),
    8 => 
    array (
      0 => '((?)\\bwhile\\b)',
      1 => 'T_WHILE',
      2 => 0,
      3 => '',
    ),
    9 => 
    array (
      0 => '((?)\\bfor\\b)',
      1 => 'T_FOR',
      2 => 0,
      3 => '',
    ),
    10 => 
    array (
      0 => '((?)\\bin\\b)',
      1 => 'T_IN',
      2 => 0,
      3 => '',
    ),
    11 => 
    array (
      0 => '((?)\\bwith\\b)',
      1 => 'T_WITH',
      2 => 0,
      3 => '',
    ),
    12 => 
    array (
      0 => '((?)\\bswitch\\b)',
      1 => 'T_SWITCH',
      2 => 0,
      3 => '',
    ),
    13 => 
    array (
      0 => '((?)\\bcase\\b)',
      1 => 'T_CASE',
      2 => 0,
      3 => '',
    ),
    14 => 
    array (
      0 => '((?)\\bdefault\\b)',
      1 => 'T_DEFAULT',
      2 => 0,
      3 => '',
    ),
    15 => 
    array (
      0 => '((?)\\bthrow\\b)',
      1 => 'T_THROW',
      2 => 0,
      3 => '',
    ),
    16 => 
    array (
      0 => '((?)\\btry\\b)',
      1 => 'T_TRY',
      2 => 0,
      3 => '',
    ),
    17 => 
    array (
      0 => '((?)\\bcatch\\b)',
      1 => 'T_CATCH',
      2 => 0,
      3 => '',
    ),
    18 => 
    array (
      0 => '((?)\\bfinally\\b)',
      1 => 'T_FINALLY',
      2 => 0,
      3 => '',
    ),
    19 => 
    array (
      0 => '((?)\\bcontinue\\b)',
      1 => 'T_CONTINUE',
      2 => 0,
      3 => '',
    ),
    20 => 
    array (
      0 => '((?)\\bbreak\\b)',
      1 => 'T_BREAK',
      2 => 0,
      3 => '',
    ),
    21 => 
    array (
      0 => '((?)\\breturn\\b)',
      1 => 'T_RETURN',
      2 => 0,
      3 => '',
    ),
    22 => 
    array (
      0 => '((?)\\bnew\\b)',
      1 => 'T_NEW',
      2 => 0,
      3 => '',
    ),
    23 => 
    array (
      0 => '((?)\\bdelete\\b)',
      1 => 'T_DELETE',
      2 => 0,
      3 => '',
    ),
    24 => 
    array (
      0 => '((?)\\bvoid\\b)',
      1 => 'T_VOID',
      2 => 0,
      3 => '',
    ),
    25 => 
    array (
      0 => '((?)\\btypeof\\b)',
      1 => 'T_TYPEOF',
      2 => 0,
      3 => '',
    ),
    26 => 
    array (
      0 => '((?)\\binstanceof\\b)',
      1 => 'T_INSTANCEOF',
      2 => 0,
      3 => '',
    ),
    27 => 
    array (
      0 => '((?)\\bnull\\b)',
      1 => 'T_NULL',
      2 => 0,
      3 => '',
    ),
    28 => 
    array (
      0 => '((?)\\btrue\\b)',
      1 => 'T_TRUE',
      2 => 0,
      3 => '',
    ),
    29 => 
    array (
      0 => '((?)\\bfalse\\b)',
      1 => 'T_FALSE',
      2 => 0,
      3 => '',
    ),
    30 => 
    array (
      0 => '((?)\\bif\\b)',
      1 => 'T_IF',
      2 => 0,
      3 => '',
    ),
    31 => 
    array (
      0 => '((?)\\bthen\\b)',
      1 => 'T_THEN',
      2 => 0,
      3 => '',
    ),
    32 => 
    array (
      0 => '((?)\\belse\\b)',
      1 => 'T_ELSE',
      2 => 0,
      3 => '',
    ),
    33 => 
    array (
      0 => '((?)\\bthis\\b)',
      1 => 'T_THIS',
      2 => 0,
      3 => '',
    ),
    34 => 
    array (
      0 => '((?)\\()',
      1 => 'T_LEFTPARENS',
      2 => 0,
      3 => '',
    ),
    35 => 
    array (
      0 => '((?)\\))',
      1 => 'T_RIGHTPARENS',
      2 => 0,
      3 => '',
    ),
    36 => 
    array (
      0 => '((?)\\{)',
      1 => 'T_LEFTBRACE',
      2 => 0,
      3 => '',
    ),
    37 => 
    array (
      0 => '((?)\\})',
      1 => 'T_RIGHTBRACE',
      2 => 0,
      3 => '',
    ),
    38 => 
    array (
      0 => '((?)\\[)',
      1 => 'T_LEFTBRACKET',
      2 => 0,
      3 => '',
    ),
    39 => 
    array (
      0 => '((?)\\])',
      1 => 'T_RIGHTBRACKET',
      2 => 0,
      3 => '',
    ),
    40 => 
    array (
      0 => '((?)\\.)',
      1 => 'T_DOT',
      2 => 0,
      3 => '',
    ),
    41 => 
    array (
      0 => '((?),)',
      1 => 'T_COMMA',
      2 => 0,
      3 => '',
    ),
    42 => 
    array (
      0 => '((?);)',
      1 => 'T_SEMICOLON',
      2 => 0,
      3 => '',
    ),
    43 => 
    array (
      0 => '((?):)',
      1 => 'T_COLON',
      2 => 0,
      3 => '',
    ),
    44 => 
    array (
      0 => '((?)(?:[*/%+&^|-]|>>>?|<<)=)',
      1 => 'T_ASSIGN',
      2 => 0,
      3 => '',
    ),
    45 => 
    array (
      0 => '((?)===)',
      1 => 'T_EQEQEQ',
      2 => 0,
      3 => '',
    ),
    46 => 
    array (
      0 => '((?)==)',
      1 => 'T_EQEQ',
      2 => 0,
      3 => '',
    ),
    47 => 
    array (
      0 => '((?)=)',
      1 => 'T_EQUAL',
      2 => 0,
      3 => '',
    ),
    48 => 
    array (
      0 => '((?)\\+\\+)',
      1 => 'T_PLUSPLUS',
      2 => 0,
      3 => '',
    ),
    49 => 
    array (
      0 => '((?)\\+)',
      1 => 'T_PLUS',
      2 => 0,
      3 => '',
    ),
    50 => 
    array (
      0 => '((?)--)',
      1 => 'T_MINUSMINUS',
      2 => 0,
      3 => '',
    ),
    51 => 
    array (
      0 => '((?)-)',
      1 => 'T_MINUS',
      2 => 0,
      3 => '',
    ),
    52 => 
    array (
      0 => '((?)[~])',
      1 => 'T_TILDE',
      2 => 0,
      3 => '',
    ),
    53 => 
    array (
      0 => '((?)!==)',
      1 => 'T_BANGEQEQ',
      2 => 0,
      3 => '',
    ),
    54 => 
    array (
      0 => '((?)!=)',
      1 => 'T_BANGEQ',
      2 => 0,
      3 => '',
    ),
    55 => 
    array (
      0 => '((?)[!])',
      1 => 'T_BANG',
      2 => 0,
      3 => '',
    ),
    56 => 
    array (
      0 => '((?)[*])',
      1 => 'T_STAR',
      2 => 0,
      3 => '',
    ),
    57 => 
    array (
      0 => '((?)[/])',
      1 => 'T_SLASH',
      2 => 0,
      3 => '',
    ),
    58 => 
    array (
      0 => '((?)[%])',
      1 => 'T_PERCENT',
      2 => 0,
      3 => '',
    ),
    59 => 
    array (
      0 => '((?)>>>)',
      1 => 'T_GTGTGT',
      2 => 0,
      3 => '',
    ),
    60 => 
    array (
      0 => '((?)<<)',
      1 => 'T_LTLT',
      2 => 0,
      3 => '',
    ),
    61 => 
    array (
      0 => '((?)>>)',
      1 => 'T_GTGT',
      2 => 0,
      3 => '',
    ),
    62 => 
    array (
      0 => '((?)<=)',
      1 => 'T_LTEQ',
      2 => 0,
      3 => '',
    ),
    63 => 
    array (
      0 => '((?)>=)',
      1 => 'T_GTEQ',
      2 => 0,
      3 => '',
    ),
    64 => 
    array (
      0 => '((?)<)',
      1 => 'T_LT',
      2 => 0,
      3 => '',
    ),
    65 => 
    array (
      0 => '((?)>)',
      1 => 'T_GT',
      2 => 0,
      3 => '',
    ),
    66 => 
    array (
      0 => '((?)[\\^])',
      1 => 'T_HAT',
      2 => 0,
      3 => '',
    ),
    67 => 
    array (
      0 => '((?)[&][&])',
      1 => 'T_AMPAMP',
      2 => 0,
      3 => '',
    ),
    68 => 
    array (
      0 => '((?)[&])',
      1 => 'T_AMP',
      2 => 0,
      3 => '',
    ),
    69 => 
    array (
      0 => '((?)[|][|])',
      1 => 'T_PIPEPIPE',
      2 => 0,
      3 => '',
    ),
    70 => 
    array (
      0 => '((?)[|])',
      1 => 'T_PIPE',
      2 => 0,
      3 => '',
    ),
    71 => 
    array (
      0 => '((?)[?])',
      1 => 'T_QUESTMARK',
      2 => 0,
      3 => '',
    ),
    72 => 
    array (
      0 => '((?)[\\$_a-zA-Z](?:\\w|\\$|_)*:)',
      1 => 'T_LABEL',
      2 => 0,
      3 => '',
    ),
    73 => 
    array (
      0 => '((?)[\\$_a-zA-Z](?:\\w|\\$|_)*)',
      1 => 'T_WORD',
      2 => 0,
      3 => '',
    ),
    74 => 
    array (
      0 => '((?)[0][xX][0-9a-zA-Z]+)',
      1 => 'T_HEXA',
      2 => 0,
      3 => '__lambda_22',
    ),
    75 => 
    array (
      0 => '((?)(?:(?:[0]|[1-9]\\d*)\\.\\d*|\\.\\d+|(?:[0]|[1-9]\\d*))(?:[eE][-+]?\\d+)?)',
      1 => 'T_DECIMAL',
      2 => 0,
      3 => '__lambda_23',
    ),
    76 => 
    array (
      0 => '((?)\'(?:[^\'\\\\]|\\\\.)*\'|"(?:[^"\\\\]|\\\\.)*")',
      1 => 'T_STRING',
      2 => 0,
      3 => '',
    ),
  ),
  'text' => 
  array (
    0 => 
    array (
      0 => '((?)\\<\\?(?:js)?)',
      1 => 'T_SCRIPT_BEGIN',
      2 => 0,
      3 => '__lambda_24',
    ),
    1 => 
    array (
      0 => '((?)\\<\\?=)',
      1 => 'T_SCRIPT_BEGIN_ECHO',
      2 => 0,
      3 => '__lambda_24',
    ),
    2 => 
    array (
      0 => '((?s)(?:[^<]|<[^?])*)',
      1 => 'T_TEXT',
      2 => 0,
      3 => '',
    ),
  ),
);
$dpa = array (
  'start' => 
  array (
    'Program' => 's165',
    'Source' => 's183',
    'FunctionDeclaration' => 's223',
    'FunctionExpression' => 's302',
    'FormalParameterList' => 's337',
    'Identifier' => 's346',
    'Statement' => 's380',
    'TextStatement' => 's430',
    'Block' => 's455',
    'StatementList' => 's470',
    'VariableStatement' => 's484',
    'VariableDeclarationList' => 's500',
    'VariableDeclaration' => 's513',
    'Initialiser' => 's524',
    'EmptyStatement' => 's531',
    'ExpressionStatement' => 's541',
    'IfStatement' => 's574',
    'IterationStatement' => 's688',
    'ContinueStatement' => 's736',
    'BreakStatement' => 's750',
    'ReturnStatement' => 's764',
    'WithStatement' => 's782',
    'SwitchStatement' => 's802',
    'CaseBlock' => 's858',
    'CaseClauses' => 's880',
    'CaseClause' => 's896',
    'DefaultClause' => 's911',
    'LabelledStatement' => 's923',
    'ThrowStatement' => 's936',
    'TryStatement' => 's968',
    'Catch' => 's988',
    'Finally' => 's1002',
    'PrimaryExpression' => 's1025',
    'Literal' => 's1044',
    'BooleanLiteral' => 's1055',
    'NumericLiteral' => 's1064',
    'StringLiteral' => 's1071',
    'ArrayLiteral' => 's1083',
    'ArrayElements' => 's1099',
    'ArrayElement' => 's1110',
    'ObjectLiteral' => 's1128',
    'PropertyNameAndValueList' => 's1171',
    'PropertyName' => 's1192',
    'MemberExpression' => 's1232',
    'Arguments' => 's1260',
    'ArgumentList' => 's1277',
    'LeftHandSideExpression' => 's1310',
    'PostfixExpression' => 's1335',
    'UnaryExpression' => 's1397',
    'MultiplicativeExpression' => 's1445',
    'AdditiveExpression' => 's1474',
    'ShiftExpression' => 's1509',
    'RelationalExpression' => 's1570',
    'EqualityExpression' => 's1621',
    'BitwiseANDExpression' => 's1644',
    'BitwiseXORExpression' => 's1661',
    'BitwiseORExpression' => 's1678',
    'LogicalANDExpression' => 's1695',
    'LogicalORExpression' => 's1712',
    'ConditionalExpression' => 's1733',
    'AssignmentExpression' => 's1759',
    'Expression' => 's1777',
    'PrimaryExpression2' => 's1800',
    'MemberExpression2' => 's1842',
    'LeftHandSideExpression2' => 's1881',
    'PostfixExpression2' => 's1906',
    'UnaryExpression2' => 's1968',
    'MultiplicativeExpression2' => 's2016',
    'AdditiveExpression2' => 's2045',
    'ShiftExpression2' => 's2080',
    'RelationalExpression2' => 's2141',
    'EqualityExpression2' => 's2192',
    'BitwiseANDExpression2' => 's2215',
    'BitwiseXORExpression2' => 's2232',
    'BitwiseORExpression2' => 's2249',
    'LogicalANDExpression2' => 's2266',
    'LogicalORExpression2' => 's2283',
    'ConditionalExpression2' => 's2304',
    'AssignmentExpression2' => 's2330',
    'Expression2' => 's2348',
    'RelationalExpressionNoIn' => 's2397',
    'EqualityExpressionNoIn' => 's2446',
    'BitwiseANDExpressionNoIn' => 's2469',
    'BitwiseXORExpressionNoIn' => 's2486',
    'BitwiseORExpressionNoIn' => 's2503',
    'LogicalANDExpressionNoIn' => 's2520',
    'LogicalORExpressionNoIn' => 's2537',
    'ConditionalExpressionNoIn' => 's2558',
    'AssignmentExpressionNoIn' => 's2584',
    'ExpressionNoIn' => 's2602',
    'VariableDeclarationListNoIn' => 's2619',
    'VariableDeclarationNoIn' => 's2632',
    'InitialiserNoIn' => 's2643',
  ),
  'delta' => 
  array (
    's165' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'Source',
        2 => 's166',
      ),
    ),
    's166' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 16,
      ),
    ),
    's183' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 17,
      ),
      'T_FUNCTION' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_VAR' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_IF' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_DO' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_WHILE' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_FOR' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_BREAK' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_RETURN' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_WITH' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_LABEL' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_SWITCH' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_THROW' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_TRY' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_DELETE' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_VOID' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_TILDE' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_BANG' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_NEW' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_THIS' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_WORD' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_NULL' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_TRUE' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_FALSE' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_HEXA' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
      'T_STRING' => 
      array (
        0 => 'fold',
        1 => 17,
        2 => 's184',
      ),
    ),
    's184' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's185',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'FunctionDeclaration',
        2 => 's186',
      ),
    ),
    's185' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 18,
      ),
      'T_FUNCTION' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_VAR' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_IF' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_DO' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_WHILE' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_FOR' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_BREAK' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_RETURN' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_WITH' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_LABEL' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_SWITCH' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_THROW' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_TRY' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_DELETE' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_VOID' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_TILDE' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_BANG' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_NEW' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_THIS' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_WORD' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_NULL' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_TRUE' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_FALSE' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_HEXA' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
      'T_STRING' => 
      array (
        0 => 'fold',
        1 => 18,
        2 => 's184',
      ),
    ),
    's186' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 19,
      ),
      'T_FUNCTION' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_VAR' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_IF' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_DO' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_WHILE' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_FOR' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_BREAK' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_RETURN' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_WITH' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_LABEL' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_SWITCH' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_THROW' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_TRY' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_DELETE' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_VOID' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_TILDE' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_BANG' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_NEW' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_THIS' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_WORD' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_NULL' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_TRUE' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_FALSE' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_HEXA' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
      'T_STRING' => 
      array (
        0 => 'fold',
        1 => 19,
        2 => 's184',
      ),
    ),
    's223' => 
    array (
      'T_FUNCTION' => 
      array (
        0 => 'go',
        1 => 's224',
      ),
    ),
    's224' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's225',
      ),
    ),
    's225' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's226',
      ),
    ),
    's226' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's227',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'FormalParameterList',
        2 => 's228',
      ),
    ),
    's227' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's229',
      ),
    ),
    's228' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's230',
      ),
    ),
    's229' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'Source',
        2 => 's231',
      ),
    ),
    's230' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's232',
      ),
    ),
    's231' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's233',
      ),
    ),
    's232' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'Source',
        2 => 's234',
      ),
    ),
    's233' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 20,
      ),
    ),
    's234' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's235',
      ),
    ),
    's235' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 21,
      ),
    ),
    's302' => 
    array (
      'T_FUNCTION' => 
      array (
        0 => 'go',
        1 => 's303',
      ),
    ),
    's303' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's304',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's305',
      ),
    ),
    's304' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's306',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'FormalParameterList',
        2 => 's307',
      ),
    ),
    's305' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's308',
      ),
    ),
    's306' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's309',
      ),
    ),
    's307' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's310',
      ),
    ),
    's308' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's311',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'FormalParameterList',
        2 => 's312',
      ),
    ),
    's309' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'Source',
        2 => 's313',
      ),
    ),
    's310' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's314',
      ),
    ),
    's311' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's315',
      ),
    ),
    's312' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's316',
      ),
    ),
    's313' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's317',
      ),
    ),
    's314' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'Source',
        2 => 's318',
      ),
    ),
    's315' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'Source',
        2 => 's319',
      ),
    ),
    's316' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's320',
      ),
    ),
    's317' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 22,
      ),
    ),
    's318' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's321',
      ),
    ),
    's319' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's322',
      ),
    ),
    's320' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'Source',
        2 => 's323',
      ),
    ),
    's321' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 24,
      ),
    ),
    's322' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 23,
      ),
    ),
    's323' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's324',
      ),
    ),
    's324' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 25,
      ),
    ),
    's337' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's338',
      ),
    ),
    's338' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 26,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 26,
        2 => 's339',
      ),
    ),
    's339' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's340',
      ),
    ),
    's340' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's341',
      ),
    ),
    's341' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 27,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 27,
        2 => 's339',
      ),
    ),
    's346' => 
    array (
      'T_WORD' => 
      array (
        0 => 'go',
        1 => 's347',
      ),
    ),
    's347' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 28,
      ),
    ),
    's380' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Block',
        2 => 's381',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'VariableStatement',
        2 => 's382',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'EmptyStatement',
        2 => 's383',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's384',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'IfStatement',
        2 => 's385',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'IterationStatement',
        2 => 's386',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'IterationStatement',
        2 => 's386',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'IterationStatement',
        2 => 's386',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'ContinueStatement',
        2 => 's387',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'BreakStatement',
        2 => 's388',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'ReturnStatement',
        2 => 's389',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'WithStatement',
        2 => 's390',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'LabelledStatement',
        2 => 's391',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'SwitchStatement',
        2 => 's392',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'ThrowStatement',
        2 => 's393',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'TryStatement',
        2 => 's394',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'TextStatement',
        2 => 's395',
      ),
    ),
    's381' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 29,
      ),
    ),
    's382' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 30,
      ),
    ),
    's383' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 31,
      ),
    ),
    's384' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 32,
      ),
    ),
    's385' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 33,
      ),
    ),
    's386' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 34,
      ),
    ),
    's387' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 35,
      ),
    ),
    's388' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 36,
      ),
    ),
    's389' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 37,
      ),
    ),
    's390' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 38,
      ),
    ),
    's391' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 39,
      ),
    ),
    's392' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 40,
      ),
    ),
    's393' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 41,
      ),
    ),
    's394' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 42,
      ),
    ),
    's395' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 43,
      ),
    ),
    's430' => 
    array (
      'T_SCRIPT_END' => 
      array (
        0 => 'go',
        1 => 's431',
      ),
    ),
    's431' => 
    array (
      'T_SCRIPT_BEGIN' => 
      array (
        0 => 'go',
        1 => 's432',
      ),
      'T_SCRIPT_BEGIN_ECHO' => 
      array (
        0 => 'go',
        1 => 's433',
      ),
      'T_TEXT' => 
      array (
        0 => 'go',
        1 => 's434',
      ),
    ),
    's432' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 44,
      ),
    ),
    's433' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's435',
      ),
    ),
    's434' => 
    array (
      'T_SCRIPT_BEGIN' => 
      array (
        0 => 'go',
        1 => 's436',
      ),
      'T_SCRIPT_BEGIN_ECHO' => 
      array (
        0 => 'go',
        1 => 's437',
      ),
    ),
    's435' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 45,
      ),
    ),
    's436' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 46,
      ),
    ),
    's437' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ExpressionStatement',
        2 => 's438',
      ),
    ),
    's438' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 47,
      ),
    ),
    's455' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's456',
      ),
    ),
    's456' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's457',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's458',
      ),
    ),
    's457' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 48,
      ),
    ),
    's458' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's459',
      ),
    ),
    's459' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 49,
      ),
    ),
    's470' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's471',
      ),
    ),
    's471' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 50,
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_VAR' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_IF' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_DO' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_WHILE' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_FOR' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_BREAK' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_RETURN' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_WITH' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_LABEL' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_SWITCH' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_THROW' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_TRY' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_DELETE' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_VOID' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_TILDE' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_BANG' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_NEW' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_THIS' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_WORD' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_NULL' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_TRUE' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_FALSE' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_HEXA' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
      'T_STRING' => 
      array (
        0 => 'fold',
        1 => 50,
        2 => 's472',
      ),
    ),
    's472' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's473',
      ),
    ),
    's473' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 51,
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_VAR' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_IF' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_DO' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_WHILE' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_FOR' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_BREAK' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_RETURN' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_WITH' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_LABEL' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_SWITCH' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_THROW' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_TRY' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_DELETE' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_VOID' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_TILDE' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_BANG' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_NEW' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_THIS' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_WORD' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_NULL' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_TRUE' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_FALSE' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_HEXA' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
      'T_STRING' => 
      array (
        0 => 'fold',
        1 => 51,
        2 => 's472',
      ),
    ),
    's484' => 
    array (
      'T_VAR' => 
      array (
        0 => 'go',
        1 => 's485',
      ),
    ),
    's485' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'VariableDeclarationList',
        2 => 's486',
      ),
    ),
    's486' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's487',
      ),
    ),
    's487' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 52,
      ),
    ),
    's500' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'VariableDeclaration',
        2 => 's501',
      ),
    ),
    's501' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 53,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 53,
        2 => 's502',
      ),
    ),
    's502' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's503',
      ),
    ),
    's503' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'VariableDeclaration',
        2 => 's504',
      ),
    ),
    's504' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 54,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 54,
        2 => 's502',
      ),
    ),
    's513' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's514',
      ),
    ),
    's514' => 
    array (
      'T_EQUAL' => 
      array (
        0 => 'push',
        1 => 'Initialiser',
        2 => 's515',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 55,
      ),
    ),
    's515' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 55,
      ),
    ),
    's524' => 
    array (
      'T_EQUAL' => 
      array (
        0 => 'go',
        1 => 's525',
      ),
    ),
    's525' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's526',
      ),
    ),
    's526' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 56,
      ),
    ),
    's531' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's532',
      ),
    ),
    's532' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 57,
      ),
    ),
    's541' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression2',
        2 => 's542',
      ),
    ),
    's542' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's543',
      ),
    ),
    's543' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 58,
      ),
    ),
    's574' => 
    array (
      'T_IF' => 
      array (
        0 => 'go',
        1 => 's575',
      ),
    ),
    's575' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's576',
      ),
    ),
    's576' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's577',
      ),
    ),
    's577' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's578',
      ),
    ),
    's578' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's579',
      ),
    ),
    's579' => 
    array (
      'T_ELSE' => 
      array (
        0 => 'go',
        1 => 's580',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 60,
      ),
    ),
    's580' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's581',
      ),
    ),
    's581' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 59,
      ),
    ),
    's688' => 
    array (
      'T_DO' => 
      array (
        0 => 'go',
        1 => 's689',
      ),
      'T_WHILE' => 
      array (
        0 => 'go',
        1 => 's690',
      ),
      'T_FOR' => 
      array (
        0 => 'go',
        1 => 's691',
      ),
    ),
    's689' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's692',
      ),
    ),
    's690' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's693',
      ),
    ),
    's691' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's694',
      ),
    ),
    's692' => 
    array (
      'T_WHILE' => 
      array (
        0 => 'go',
        1 => 's695',
      ),
    ),
    's693' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's696',
      ),
    ),
    's694' => 
    array (
      'T_VAR' => 
      array (
        0 => 'go',
        1 => 's698',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's699',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ExpressionNoIn',
        2 => 's697',
      ),
    ),
    's695' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's700',
      ),
    ),
    's696' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's701',
      ),
    ),
    's697' => 
    array (
      'T_IN' => 
      array (
        0 => 'go',
        1 => 's702',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's699',
      ),
    ),
    's698' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'VariableDeclarationListNoIn',
        2 => 's703',
      ),
    ),
    's699' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's705',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's704',
      ),
    ),
    's700' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's706',
      ),
    ),
    's701' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's707',
      ),
    ),
    's702' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's708',
      ),
    ),
    's703' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's709',
      ),
      'T_IN' => 
      array (
        0 => 'go',
        1 => 's710',
      ),
    ),
    's704' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's705',
      ),
    ),
    's705' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's712',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's711',
      ),
    ),
    's706' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's713',
      ),
    ),
    's707' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 62,
      ),
    ),
    's708' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's714',
      ),
    ),
    's709' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's716',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's715',
      ),
    ),
    's710' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's717',
      ),
    ),
    's711' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's712',
      ),
    ),
    's712' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's718',
      ),
    ),
    's713' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's719',
      ),
    ),
    's714' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's720',
      ),
    ),
    's715' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's716',
      ),
    ),
    's716' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's722',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's721',
      ),
    ),
    's717' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's723',
      ),
    ),
    's718' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 64,
      ),
    ),
    's719' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 61,
      ),
    ),
    's720' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 63,
      ),
    ),
    's721' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's722',
      ),
    ),
    's722' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's724',
      ),
    ),
    's723' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's725',
      ),
    ),
    's724' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 65,
      ),
    ),
    's725' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 66,
      ),
    ),
    's736' => 
    array (
      'T_CONTINUE' => 
      array (
        0 => 'go',
        1 => 's737',
      ),
    ),
    's737' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's739',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's738',
      ),
    ),
    's738' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's739',
      ),
    ),
    's739' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 67,
      ),
    ),
    's750' => 
    array (
      'T_BREAK' => 
      array (
        0 => 'go',
        1 => 's751',
      ),
    ),
    's751' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's753',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's752',
      ),
    ),
    's752' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's753',
      ),
    ),
    's753' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 68,
      ),
    ),
    's764' => 
    array (
      'T_RETURN' => 
      array (
        0 => 'go',
        1 => 's765',
      ),
    ),
    's765' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's767',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's766',
      ),
    ),
    's766' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's767',
      ),
    ),
    's767' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 69,
      ),
    ),
    's782' => 
    array (
      'T_WITH' => 
      array (
        0 => 'go',
        1 => 's783',
      ),
    ),
    's783' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's784',
      ),
    ),
    's784' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's785',
      ),
    ),
    's785' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's786',
      ),
    ),
    's786' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's787',
      ),
    ),
    's787' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 70,
      ),
    ),
    's802' => 
    array (
      'T_SWITCH' => 
      array (
        0 => 'go',
        1 => 's803',
      ),
    ),
    's803' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's804',
      ),
    ),
    's804' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's805',
      ),
    ),
    's805' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's806',
      ),
    ),
    's806' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'CaseBlock',
        2 => 's807',
      ),
    ),
    's807' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 71,
      ),
    ),
    's858' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's859',
      ),
    ),
    's859' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's862',
      ),
      'T_CASE' => 
      array (
        0 => 'push',
        1 => 'CaseClauses',
        2 => 's860',
      ),
      'T_DEFAULT' => 
      array (
        0 => 'push',
        1 => 'DefaultClause',
        2 => 's861',
      ),
    ),
    's860' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's862',
      ),
      'T_DEFAULT' => 
      array (
        0 => 'push',
        1 => 'DefaultClause',
        2 => 's863',
      ),
    ),
    's861' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's864',
      ),
      'T_CASE' => 
      array (
        0 => 'push',
        1 => 'CaseClauses',
        2 => 's865',
      ),
    ),
    's862' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 72,
      ),
    ),
    's863' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's866',
      ),
      'T_CASE' => 
      array (
        0 => 'push',
        1 => 'CaseClauses',
        2 => 's867',
      ),
    ),
    's864' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 73,
      ),
    ),
    's865' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's868',
      ),
    ),
    's866' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 75,
      ),
    ),
    's867' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's869',
      ),
    ),
    's868' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 74,
      ),
    ),
    's869' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 76,
      ),
    ),
    's880' => 
    array (
      'T_CASE' => 
      array (
        0 => 'push',
        1 => 'CaseClause',
        2 => 's881',
      ),
    ),
    's881' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 77,
      ),
      'T_CASE' => 
      array (
        0 => 'fold',
        1 => 77,
        2 => 's882',
      ),
    ),
    's882' => 
    array (
      'T_CASE' => 
      array (
        0 => 'push',
        1 => 'CaseClause',
        2 => 's883',
      ),
    ),
    's883' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 78,
      ),
      'T_CASE' => 
      array (
        0 => 'fold',
        1 => 78,
        2 => 's882',
      ),
    ),
    's896' => 
    array (
      'T_CASE' => 
      array (
        0 => 'go',
        1 => 's897',
      ),
    ),
    's897' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's898',
      ),
    ),
    's898' => 
    array (
      'T_COLON' => 
      array (
        0 => 'go',
        1 => 's899',
      ),
    ),
    's899' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's900',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 79,
      ),
    ),
    's900' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 79,
      ),
    ),
    's911' => 
    array (
      'T_DEFAULT' => 
      array (
        0 => 'go',
        1 => 's912',
      ),
    ),
    's912' => 
    array (
      'T_COLON' => 
      array (
        0 => 'go',
        1 => 's913',
      ),
    ),
    's913' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'StatementList',
        2 => 's914',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 80,
      ),
    ),
    's914' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 80,
      ),
    ),
    's923' => 
    array (
      'T_LABEL' => 
      array (
        0 => 'go',
        1 => 's924',
      ),
    ),
    's924' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_VAR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_SEMICOLON' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_IF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_DO' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_WHILE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_FOR' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_CONTINUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_BREAK' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_RETURN' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_WITH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_SWITCH' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_THROW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_TRY' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_SCRIPT_END' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Statement',
        2 => 's925',
      ),
    ),
    's925' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 81,
      ),
    ),
    's936' => 
    array (
      'T_THROW' => 
      array (
        0 => 'go',
        1 => 's937',
      ),
    ),
    's937' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's938',
      ),
    ),
    's938' => 
    array (
      'T_SEMICOLON' => 
      array (
        0 => 'go',
        1 => 's939',
      ),
    ),
    's939' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 82,
      ),
    ),
    's968' => 
    array (
      'T_TRY' => 
      array (
        0 => 'go',
        1 => 's969',
      ),
    ),
    's969' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Block',
        2 => 's970',
      ),
    ),
    's970' => 
    array (
      'T_CATCH' => 
      array (
        0 => 'push',
        1 => 'Catch',
        2 => 's971',
      ),
      'T_FINALLY' => 
      array (
        0 => 'push',
        1 => 'Finally',
        2 => 's972',
      ),
    ),
    's971' => 
    array (
      'T_FINALLY' => 
      array (
        0 => 'push',
        1 => 'Finally',
        2 => 's973',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 83,
      ),
    ),
    's972' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 84,
      ),
    ),
    's973' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 85,
      ),
    ),
    's988' => 
    array (
      'T_CATCH' => 
      array (
        0 => 'go',
        1 => 's989',
      ),
    ),
    's989' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's990',
      ),
    ),
    's990' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's991',
      ),
    ),
    's991' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's992',
      ),
    ),
    's992' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Block',
        2 => 's993',
      ),
    ),
    's993' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 86,
      ),
    ),
    's1002' => 
    array (
      'T_FINALLY' => 
      array (
        0 => 'go',
        1 => 's1003',
      ),
    ),
    's1003' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Block',
        2 => 's1004',
      ),
    ),
    's1004' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 87,
      ),
    ),
    's1025' => 
    array (
      'T_THIS' => 
      array (
        0 => 'go',
        1 => 's1026',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's1031',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's1027',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1028',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1028',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1028',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1028',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1028',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1028',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ArrayLiteral',
        2 => 's1029',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ObjectLiteral',
        2 => 's1030',
      ),
    ),
    's1026' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 88,
      ),
    ),
    's1027' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 89,
      ),
    ),
    's1028' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 90,
      ),
    ),
    's1029' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 91,
      ),
    ),
    's1030' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 92,
      ),
    ),
    's1031' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1032',
      ),
    ),
    's1032' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's1033',
      ),
    ),
    's1033' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 93,
      ),
    ),
    's1044' => 
    array (
      'T_NULL' => 
      array (
        0 => 'go',
        1 => 's1045',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BooleanLiteral',
        2 => 's1046',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BooleanLiteral',
        2 => 's1046',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'NumericLiteral',
        2 => 's1047',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'NumericLiteral',
        2 => 's1047',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'StringLiteral',
        2 => 's1048',
      ),
    ),
    's1045' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 94,
      ),
    ),
    's1046' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 95,
      ),
    ),
    's1047' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 96,
      ),
    ),
    's1048' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 97,
      ),
    ),
    's1055' => 
    array (
      'T_TRUE' => 
      array (
        0 => 'go',
        1 => 's1056',
      ),
      'T_FALSE' => 
      array (
        0 => 'go',
        1 => 's1057',
      ),
    ),
    's1056' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 98,
      ),
    ),
    's1057' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 99,
      ),
    ),
    's1064' => 
    array (
      'T_DECIMAL' => 
      array (
        0 => 'go',
        1 => 's1065',
      ),
      'T_HEXA' => 
      array (
        0 => 'go',
        1 => 's1066',
      ),
    ),
    's1065' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 100,
      ),
    ),
    's1066' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 101,
      ),
    ),
    's1071' => 
    array (
      'T_STRING' => 
      array (
        0 => 'go',
        1 => 's1072',
      ),
    ),
    's1072' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 102,
      ),
    ),
    's1083' => 
    array (
      'T_LEFTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1084',
      ),
    ),
    's1084' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'ArrayElements',
        2 => 's1085',
      ),
    ),
    's1085' => 
    array (
      'T_RIGHTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1086',
      ),
    ),
    's1086' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 103,
      ),
    ),
    's1099' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'ArrayElement',
        2 => 's1100',
      ),
    ),
    's1100' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 104,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 104,
        2 => 's1101',
      ),
    ),
    's1101' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's1102',
      ),
    ),
    's1102' => 
    array (
      '[default]' => 
      array (
        0 => 'push',
        1 => 'ArrayElement',
        2 => 's1103',
      ),
    ),
    's1103' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 105,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 105,
        2 => 's1101',
      ),
    ),
    's1110' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1111',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 106,
      ),
    ),
    's1111' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 107,
      ),
    ),
    's1128' => 
    array (
      'T_LEFTBRACE' => 
      array (
        0 => 'go',
        1 => 's1129',
      ),
    ),
    's1129' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's1130',
      ),
      'T_LABEL' => 
      array (
        0 => 'push',
        1 => 'PropertyNameAndValueList',
        2 => 's1131',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'PropertyNameAndValueList',
        2 => 's1131',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'PropertyNameAndValueList',
        2 => 's1131',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'PropertyNameAndValueList',
        2 => 's1131',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'PropertyNameAndValueList',
        2 => 's1131',
      ),
    ),
    's1130' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 108,
      ),
    ),
    's1131' => 
    array (
      'T_RIGHTBRACE' => 
      array (
        0 => 'go',
        1 => 's1132',
      ),
    ),
    's1132' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 109,
      ),
    ),
    's1171' => 
    array (
      'T_LABEL' => 
      array (
        0 => 'go',
        1 => 's1173',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'PropertyName',
        2 => 's1172',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'PropertyName',
        2 => 's1172',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'PropertyName',
        2 => 's1172',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'PropertyName',
        2 => 's1172',
      ),
    ),
    's1172' => 
    array (
      'T_COLON' => 
      array (
        0 => 'go',
        1 => 's1175',
      ),
    ),
    's1173' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1176',
      ),
    ),
    's1174' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's1177',
      ),
    ),
    's1175' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1178',
      ),
    ),
    's1176' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 111,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 111,
        2 => 's1174',
      ),
    ),
    's1177' => 
    array (
      'T_LABEL' => 
      array (
        0 => 'go',
        1 => 's1180',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'PropertyName',
        2 => 's1179',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'PropertyName',
        2 => 's1179',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'PropertyName',
        2 => 's1179',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'PropertyName',
        2 => 's1179',
      ),
    ),
    's1178' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 110,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 110,
        2 => 's1174',
      ),
    ),
    's1179' => 
    array (
      'T_COLON' => 
      array (
        0 => 'go',
        1 => 's1181',
      ),
    ),
    's1180' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1182',
      ),
    ),
    's1181' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1183',
      ),
    ),
    's1182' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 113,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 113,
        2 => 's1174',
      ),
    ),
    's1183' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 112,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 112,
        2 => 's1174',
      ),
    ),
    's1192' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's1193',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'StringLiteral',
        2 => 's1194',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'NumericLiteral',
        2 => 's1195',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'NumericLiteral',
        2 => 's1195',
      ),
    ),
    's1193' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 114,
      ),
    ),
    's1194' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 115,
      ),
    ),
    's1195' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 116,
      ),
    ),
    's1232' => 
    array (
      'T_NEW' => 
      array (
        0 => 'go',
        1 => 's1236',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression',
        2 => 's1233',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'FunctionExpression',
        2 => 's1234',
      ),
    ),
    's1233' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 117,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 117,
        2 => 's1235',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 117,
        2 => 's1235',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 117,
        2 => 's1235',
      ),
    ),
    's1234' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 118,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 118,
        2 => 's1235',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 118,
        2 => 's1235',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 118,
        2 => 's1235',
      ),
    ),
    's1235' => 
    array (
      'T_LEFTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1237',
      ),
      'T_DOT' => 
      array (
        0 => 'go',
        1 => 's1238',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Arguments',
        2 => 's1239',
      ),
    ),
    's1236' => 
    array (
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1240',
      ),
    ),
    's1237' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1241',
      ),
    ),
    's1238' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's1242',
      ),
    ),
    's1239' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 122,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 122,
        2 => 's1235',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 122,
        2 => 's1235',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 122,
        2 => 's1235',
      ),
    ),
    's1240' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 121,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 121,
        2 => 's1235',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 121,
        2 => 's1235',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 121,
        2 => 's1235',
      ),
    ),
    's1241' => 
    array (
      'T_RIGHTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1243',
      ),
    ),
    's1242' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 120,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 120,
        2 => 's1235',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 120,
        2 => 's1235',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 120,
        2 => 's1235',
      ),
    ),
    's1243' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 119,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 119,
        2 => 's1235',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 119,
        2 => 's1235',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 119,
        2 => 's1235',
      ),
    ),
    's1260' => 
    array (
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's1261',
      ),
    ),
    's1261' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's1262',
      ),
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ArgumentList',
        2 => 's1263',
      ),
    ),
    's1262' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 123,
      ),
    ),
    's1263' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's1264',
      ),
    ),
    's1264' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 124,
      ),
    ),
    's1277' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1278',
      ),
    ),
    's1278' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 125,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 125,
        2 => 's1279',
      ),
    ),
    's1279' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's1280',
      ),
    ),
    's1280' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1281',
      ),
    ),
    's1281' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 126,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 126,
        2 => 's1279',
      ),
    ),
    's1310' => 
    array (
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MemberExpression',
        2 => 's1311',
      ),
    ),
    's1311' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 127,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 127,
        2 => 's1312',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 127,
        2 => 's1312',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 127,
        2 => 's1312',
      ),
    ),
    's1312' => 
    array (
      'T_LEFTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1314',
      ),
      'T_DOT' => 
      array (
        0 => 'go',
        1 => 's1315',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Arguments',
        2 => 's1313',
      ),
    ),
    's1313' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 128,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 128,
        2 => 's1312',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 128,
        2 => 's1312',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 128,
        2 => 's1312',
      ),
    ),
    's1314' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1316',
      ),
    ),
    's1315' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's1317',
      ),
    ),
    's1316' => 
    array (
      'T_RIGHTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1318',
      ),
    ),
    's1317' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 130,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 130,
        2 => 's1312',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 130,
        2 => 's1312',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 130,
        2 => 's1312',
      ),
    ),
    's1318' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 129,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 129,
        2 => 's1312',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 129,
        2 => 's1312',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 129,
        2 => 's1312',
      ),
    ),
    's1335' => 
    array (
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression',
        2 => 's1336',
      ),
    ),
    's1336' => 
    array (
      'T_PLUSPLUS' => 
      array (
        0 => 'go',
        1 => 's1337',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'go',
        1 => 's1338',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 131,
      ),
    ),
    's1337' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 132,
      ),
    ),
    's1338' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 133,
      ),
    ),
    's1397' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'go',
        1 => 's1399',
      ),
      'T_VOID' => 
      array (
        0 => 'go',
        1 => 's1400',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'go',
        1 => 's1401',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'go',
        1 => 's1402',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'go',
        1 => 's1403',
      ),
      'T_PLUS' => 
      array (
        0 => 'go',
        1 => 's1404',
      ),
      'T_MINUS' => 
      array (
        0 => 'go',
        1 => 's1405',
      ),
      'T_TILDE' => 
      array (
        0 => 'go',
        1 => 's1406',
      ),
      'T_BANG' => 
      array (
        0 => 'go',
        1 => 's1407',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression',
        2 => 's1398',
      ),
    ),
    's1398' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 134,
      ),
    ),
    's1399' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1408',
      ),
    ),
    's1400' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1409',
      ),
    ),
    's1401' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1410',
      ),
    ),
    's1402' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1411',
      ),
    ),
    's1403' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1412',
      ),
    ),
    's1404' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1413',
      ),
    ),
    's1405' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1414',
      ),
    ),
    's1406' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1415',
      ),
    ),
    's1407' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1416',
      ),
    ),
    's1408' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 135,
      ),
    ),
    's1409' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 136,
      ),
    ),
    's1410' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 137,
      ),
    ),
    's1411' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 138,
      ),
    ),
    's1412' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 139,
      ),
    ),
    's1413' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 140,
      ),
    ),
    's1414' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 141,
      ),
    ),
    's1415' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 142,
      ),
    ),
    's1416' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 143,
      ),
    ),
    's1445' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1446',
      ),
    ),
    's1446' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 144,
      ),
      'T_STAR' => 
      array (
        0 => 'fold',
        1 => 144,
        2 => 's1447',
      ),
      'T_SLASH' => 
      array (
        0 => 'fold',
        1 => 144,
        2 => 's1447',
      ),
      'T_PERCENT' => 
      array (
        0 => 'fold',
        1 => 144,
        2 => 's1447',
      ),
    ),
    's1447' => 
    array (
      'T_STAR' => 
      array (
        0 => 'go',
        1 => 's1448',
      ),
      'T_SLASH' => 
      array (
        0 => 'go',
        1 => 's1449',
      ),
      'T_PERCENT' => 
      array (
        0 => 'go',
        1 => 's1450',
      ),
    ),
    's1448' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1451',
      ),
    ),
    's1449' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1452',
      ),
    ),
    's1450' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1453',
      ),
    ),
    's1451' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 145,
      ),
      'T_STAR' => 
      array (
        0 => 'fold',
        1 => 145,
        2 => 's1447',
      ),
      'T_SLASH' => 
      array (
        0 => 'fold',
        1 => 145,
        2 => 's1447',
      ),
      'T_PERCENT' => 
      array (
        0 => 'fold',
        1 => 145,
        2 => 's1447',
      ),
    ),
    's1452' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 146,
      ),
      'T_STAR' => 
      array (
        0 => 'fold',
        1 => 146,
        2 => 's1447',
      ),
      'T_SLASH' => 
      array (
        0 => 'fold',
        1 => 146,
        2 => 's1447',
      ),
      'T_PERCENT' => 
      array (
        0 => 'fold',
        1 => 146,
        2 => 's1447',
      ),
    ),
    's1453' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 147,
      ),
      'T_STAR' => 
      array (
        0 => 'fold',
        1 => 147,
        2 => 's1447',
      ),
      'T_SLASH' => 
      array (
        0 => 'fold',
        1 => 147,
        2 => 's1447',
      ),
      'T_PERCENT' => 
      array (
        0 => 'fold',
        1 => 147,
        2 => 's1447',
      ),
    ),
    's1474' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1475',
      ),
    ),
    's1475' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 148,
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 148,
        2 => 's1476',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 148,
        2 => 's1476',
      ),
    ),
    's1476' => 
    array (
      'T_PLUS' => 
      array (
        0 => 'go',
        1 => 's1477',
      ),
      'T_MINUS' => 
      array (
        0 => 'go',
        1 => 's1478',
      ),
    ),
    's1477' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1479',
      ),
    ),
    's1478' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's1480',
      ),
    ),
    's1479' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 149,
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 149,
        2 => 's1476',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 149,
        2 => 's1476',
      ),
    ),
    's1480' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 150,
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 150,
        2 => 's1476',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 150,
        2 => 's1476',
      ),
    ),
    's1509' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1510',
      ),
    ),
    's1510' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 151,
      ),
      'T_LTLT' => 
      array (
        0 => 'fold',
        1 => 151,
        2 => 's1511',
      ),
      'T_GTGT' => 
      array (
        0 => 'fold',
        1 => 151,
        2 => 's1511',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'fold',
        1 => 151,
        2 => 's1511',
      ),
    ),
    's1511' => 
    array (
      'T_LTLT' => 
      array (
        0 => 'go',
        1 => 's1512',
      ),
      'T_GTGT' => 
      array (
        0 => 'go',
        1 => 's1513',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'go',
        1 => 's1514',
      ),
    ),
    's1512' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1515',
      ),
    ),
    's1513' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1516',
      ),
    ),
    's1514' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's1517',
      ),
    ),
    's1515' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 152,
      ),
      'T_LTLT' => 
      array (
        0 => 'fold',
        1 => 152,
        2 => 's1511',
      ),
      'T_GTGT' => 
      array (
        0 => 'fold',
        1 => 152,
        2 => 's1511',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'fold',
        1 => 152,
        2 => 's1511',
      ),
    ),
    's1516' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 153,
      ),
      'T_LTLT' => 
      array (
        0 => 'fold',
        1 => 153,
        2 => 's1511',
      ),
      'T_GTGT' => 
      array (
        0 => 'fold',
        1 => 153,
        2 => 's1511',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'fold',
        1 => 153,
        2 => 's1511',
      ),
    ),
    's1517' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 154,
      ),
      'T_LTLT' => 
      array (
        0 => 'fold',
        1 => 154,
        2 => 's1511',
      ),
      'T_GTGT' => 
      array (
        0 => 'fold',
        1 => 154,
        2 => 's1511',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'fold',
        1 => 154,
        2 => 's1511',
      ),
    ),
    's1570' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1571',
      ),
    ),
    's1571' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 155,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 155,
        2 => 's1572',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 155,
        2 => 's1572',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 155,
        2 => 's1572',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 155,
        2 => 's1572',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 155,
        2 => 's1572',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 155,
        2 => 's1572',
      ),
    ),
    's1572' => 
    array (
      'T_LT' => 
      array (
        0 => 'go',
        1 => 's1573',
      ),
      'T_GT' => 
      array (
        0 => 'go',
        1 => 's1574',
      ),
      'T_LTEQ' => 
      array (
        0 => 'go',
        1 => 's1575',
      ),
      'T_GTEQ' => 
      array (
        0 => 'go',
        1 => 's1576',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'go',
        1 => 's1577',
      ),
      'T_IN' => 
      array (
        0 => 'go',
        1 => 's1578',
      ),
    ),
    's1573' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1579',
      ),
    ),
    's1574' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1580',
      ),
    ),
    's1575' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1581',
      ),
    ),
    's1576' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1582',
      ),
    ),
    's1577' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1583',
      ),
    ),
    's1578' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's1584',
      ),
    ),
    's1579' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 156,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 156,
        2 => 's1572',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 156,
        2 => 's1572',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 156,
        2 => 's1572',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 156,
        2 => 's1572',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 156,
        2 => 's1572',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 156,
        2 => 's1572',
      ),
    ),
    's1580' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 157,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 157,
        2 => 's1572',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 157,
        2 => 's1572',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 157,
        2 => 's1572',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 157,
        2 => 's1572',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 157,
        2 => 's1572',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 157,
        2 => 's1572',
      ),
    ),
    's1581' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 158,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 158,
        2 => 's1572',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 158,
        2 => 's1572',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 158,
        2 => 's1572',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 158,
        2 => 's1572',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 158,
        2 => 's1572',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 158,
        2 => 's1572',
      ),
    ),
    's1582' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 159,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 159,
        2 => 's1572',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 159,
        2 => 's1572',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 159,
        2 => 's1572',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 159,
        2 => 's1572',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 159,
        2 => 's1572',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 159,
        2 => 's1572',
      ),
    ),
    's1583' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 160,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 160,
        2 => 's1572',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 160,
        2 => 's1572',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 160,
        2 => 's1572',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 160,
        2 => 's1572',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 160,
        2 => 's1572',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 160,
        2 => 's1572',
      ),
    ),
    's1584' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 161,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 161,
        2 => 's1572',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 161,
        2 => 's1572',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 161,
        2 => 's1572',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 161,
        2 => 's1572',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 161,
        2 => 's1572',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 161,
        2 => 's1572',
      ),
    ),
    's1621' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1622',
      ),
    ),
    's1622' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 162,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 162,
        2 => 's1623',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 162,
        2 => 's1623',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 162,
        2 => 's1623',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 162,
        2 => 's1623',
      ),
    ),
    's1623' => 
    array (
      'T_EQEQ' => 
      array (
        0 => 'go',
        1 => 's1624',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'go',
        1 => 's1625',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'go',
        1 => 's1626',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'go',
        1 => 's1627',
      ),
    ),
    's1624' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1628',
      ),
    ),
    's1625' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1629',
      ),
    ),
    's1626' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1630',
      ),
    ),
    's1627' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's1631',
      ),
    ),
    's1628' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 163,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 163,
        2 => 's1623',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 163,
        2 => 's1623',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 163,
        2 => 's1623',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 163,
        2 => 's1623',
      ),
    ),
    's1629' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 164,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 164,
        2 => 's1623',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 164,
        2 => 's1623',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 164,
        2 => 's1623',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 164,
        2 => 's1623',
      ),
    ),
    's1630' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 165,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 165,
        2 => 's1623',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 165,
        2 => 's1623',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 165,
        2 => 's1623',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 165,
        2 => 's1623',
      ),
    ),
    's1631' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 166,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 166,
        2 => 's1623',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 166,
        2 => 's1623',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 166,
        2 => 's1623',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 166,
        2 => 's1623',
      ),
    ),
    's1644' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1645',
      ),
    ),
    's1645' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 167,
      ),
      'T_AMP' => 
      array (
        0 => 'fold',
        1 => 167,
        2 => 's1646',
      ),
    ),
    's1646' => 
    array (
      'T_AMP' => 
      array (
        0 => 'go',
        1 => 's1647',
      ),
    ),
    's1647' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's1648',
      ),
    ),
    's1648' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 168,
      ),
      'T_AMP' => 
      array (
        0 => 'fold',
        1 => 168,
        2 => 's1646',
      ),
    ),
    's1661' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1662',
      ),
    ),
    's1662' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 169,
      ),
      'T_HAT' => 
      array (
        0 => 'fold',
        1 => 169,
        2 => 's1663',
      ),
    ),
    's1663' => 
    array (
      'T_HAT' => 
      array (
        0 => 'go',
        1 => 's1664',
      ),
    ),
    's1664' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's1665',
      ),
    ),
    's1665' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 170,
      ),
      'T_HAT' => 
      array (
        0 => 'fold',
        1 => 170,
        2 => 's1663',
      ),
    ),
    's1678' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1679',
      ),
    ),
    's1679' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 171,
      ),
      'T_PIPE' => 
      array (
        0 => 'fold',
        1 => 171,
        2 => 's1680',
      ),
    ),
    's1680' => 
    array (
      'T_PIPE' => 
      array (
        0 => 'go',
        1 => 's1681',
      ),
    ),
    's1681' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's1682',
      ),
    ),
    's1682' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 172,
      ),
      'T_PIPE' => 
      array (
        0 => 'fold',
        1 => 172,
        2 => 's1680',
      ),
    ),
    's1695' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1696',
      ),
    ),
    's1696' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 173,
      ),
      'T_AMPAMP' => 
      array (
        0 => 'fold',
        1 => 173,
        2 => 's1697',
      ),
    ),
    's1697' => 
    array (
      'T_AMPAMP' => 
      array (
        0 => 'go',
        1 => 's1698',
      ),
    ),
    's1698' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's1699',
      ),
    ),
    's1699' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 174,
      ),
      'T_AMPAMP' => 
      array (
        0 => 'fold',
        1 => 174,
        2 => 's1697',
      ),
    ),
    's1712' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1713',
      ),
    ),
    's1713' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 175,
      ),
      'T_PIPEPIPE' => 
      array (
        0 => 'fold',
        1 => 175,
        2 => 's1714',
      ),
    ),
    's1714' => 
    array (
      'T_PIPEPIPE' => 
      array (
        0 => 'go',
        1 => 's1715',
      ),
    ),
    's1715' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's1716',
      ),
    ),
    's1716' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 176,
      ),
      'T_PIPEPIPE' => 
      array (
        0 => 'fold',
        1 => 176,
        2 => 's1714',
      ),
    ),
    's1733' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression',
        2 => 's1734',
      ),
    ),
    's1734' => 
    array (
      'T_QUESTMARK' => 
      array (
        0 => 'go',
        1 => 's1735',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 177,
      ),
    ),
    's1735' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1736',
      ),
    ),
    's1736' => 
    array (
      'T_COLON' => 
      array (
        0 => 'go',
        1 => 's1737',
      ),
    ),
    's1737' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1738',
      ),
    ),
    's1738' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 178,
      ),
    ),
    's1759' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression',
        2 => 's1760',
      ),
    ),
    's1760' => 
    array (
      'T_EQUAL' => 
      array (
        0 => 'go',
        1 => 's1761',
      ),
      'T_ASSIGN' => 
      array (
        0 => 'go',
        1 => 's1762',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 179,
      ),
    ),
    's1761' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1763',
      ),
    ),
    's1762' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1764',
      ),
    ),
    's1763' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 180,
      ),
    ),
    's1764' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 181,
      ),
    ),
    's1777' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1778',
      ),
    ),
    's1778' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 182,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 182,
        2 => 's1779',
      ),
    ),
    's1779' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's1780',
      ),
    ),
    's1780' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's1781',
      ),
    ),
    's1781' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 183,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 183,
        2 => 's1779',
      ),
    ),
    's1800' => 
    array (
      'T_THIS' => 
      array (
        0 => 'go',
        1 => 's1801',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'go',
        1 => 's1805',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's1802',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1803',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1803',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1803',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1803',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1803',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Literal',
        2 => 's1803',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ArrayLiteral',
        2 => 's1804',
      ),
    ),
    's1801' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 184,
      ),
    ),
    's1802' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 185,
      ),
    ),
    's1803' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 186,
      ),
    ),
    's1804' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 187,
      ),
    ),
    's1805' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1806',
      ),
    ),
    's1806' => 
    array (
      'T_RIGHTPARENS' => 
      array (
        0 => 'go',
        1 => 's1807',
      ),
    ),
    's1807' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 188,
      ),
    ),
    's1842' => 
    array (
      'T_NEW' => 
      array (
        0 => 'go',
        1 => 's1845',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'PrimaryExpression2',
        2 => 's1843',
      ),
    ),
    's1843' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 189,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 189,
        2 => 's1844',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 189,
        2 => 's1844',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 189,
        2 => 's1844',
      ),
    ),
    's1844' => 
    array (
      'T_LEFTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1846',
      ),
      'T_DOT' => 
      array (
        0 => 'go',
        1 => 's1847',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Arguments',
        2 => 's1848',
      ),
    ),
    's1845' => 
    array (
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1849',
      ),
    ),
    's1846' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1850',
      ),
    ),
    's1847' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's1851',
      ),
    ),
    's1848' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 193,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 193,
        2 => 's1844',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 193,
        2 => 's1844',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 193,
        2 => 's1844',
      ),
    ),
    's1849' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 192,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 192,
        2 => 's1844',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 192,
        2 => 's1844',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 192,
        2 => 's1844',
      ),
    ),
    's1850' => 
    array (
      'T_RIGHTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1852',
      ),
    ),
    's1851' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 191,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 191,
        2 => 's1844',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 191,
        2 => 's1844',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 191,
        2 => 's1844',
      ),
    ),
    's1852' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 190,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 190,
        2 => 's1844',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 190,
        2 => 's1844',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 190,
        2 => 's1844',
      ),
    ),
    's1881' => 
    array (
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MemberExpression2',
        2 => 's1882',
      ),
    ),
    's1882' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 194,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 194,
        2 => 's1883',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 194,
        2 => 's1883',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 194,
        2 => 's1883',
      ),
    ),
    's1883' => 
    array (
      'T_LEFTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1885',
      ),
      'T_DOT' => 
      array (
        0 => 'go',
        1 => 's1886',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Arguments',
        2 => 's1884',
      ),
    ),
    's1884' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 195,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 195,
        2 => 's1883',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 195,
        2 => 's1883',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 195,
        2 => 's1883',
      ),
    ),
    's1885' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'Expression',
        2 => 's1887',
      ),
    ),
    's1886' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's1888',
      ),
    ),
    's1887' => 
    array (
      'T_RIGHTBRACKET' => 
      array (
        0 => 'go',
        1 => 's1889',
      ),
    ),
    's1888' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 197,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 197,
        2 => 's1883',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 197,
        2 => 's1883',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 197,
        2 => 's1883',
      ),
    ),
    's1889' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 196,
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'fold',
        1 => 196,
        2 => 's1883',
      ),
      'T_DOT' => 
      array (
        0 => 'fold',
        1 => 196,
        2 => 's1883',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'fold',
        1 => 196,
        2 => 's1883',
      ),
    ),
    's1906' => 
    array (
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LeftHandSideExpression2',
        2 => 's1907',
      ),
    ),
    's1907' => 
    array (
      'T_PLUSPLUS' => 
      array (
        0 => 'go',
        1 => 's1908',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'go',
        1 => 's1909',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 198,
      ),
    ),
    's1908' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 199,
      ),
    ),
    's1909' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 200,
      ),
    ),
    's1968' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'go',
        1 => 's1970',
      ),
      'T_VOID' => 
      array (
        0 => 'go',
        1 => 's1971',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'go',
        1 => 's1972',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'go',
        1 => 's1973',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'go',
        1 => 's1974',
      ),
      'T_PLUS' => 
      array (
        0 => 'go',
        1 => 's1975',
      ),
      'T_MINUS' => 
      array (
        0 => 'go',
        1 => 's1976',
      ),
      'T_TILDE' => 
      array (
        0 => 'go',
        1 => 's1977',
      ),
      'T_BANG' => 
      array (
        0 => 'go',
        1 => 's1978',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'PostfixExpression2',
        2 => 's1969',
      ),
    ),
    's1969' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 201,
      ),
    ),
    's1970' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1979',
      ),
    ),
    's1971' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1980',
      ),
    ),
    's1972' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1981',
      ),
    ),
    's1973' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1982',
      ),
    ),
    's1974' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1983',
      ),
    ),
    's1975' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1984',
      ),
    ),
    's1976' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1985',
      ),
    ),
    's1977' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1986',
      ),
    ),
    's1978' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's1987',
      ),
    ),
    's1979' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 202,
      ),
    ),
    's1980' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 203,
      ),
    ),
    's1981' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 204,
      ),
    ),
    's1982' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 205,
      ),
    ),
    's1983' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 206,
      ),
    ),
    's1984' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 207,
      ),
    ),
    's1985' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 208,
      ),
    ),
    's1986' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 209,
      ),
    ),
    's1987' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 210,
      ),
    ),
    's2016' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression2',
        2 => 's2017',
      ),
    ),
    's2017' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 211,
      ),
      'T_STAR' => 
      array (
        0 => 'fold',
        1 => 211,
        2 => 's2018',
      ),
      'T_SLASH' => 
      array (
        0 => 'fold',
        1 => 211,
        2 => 's2018',
      ),
      'T_PERCENT' => 
      array (
        0 => 'fold',
        1 => 211,
        2 => 's2018',
      ),
    ),
    's2018' => 
    array (
      'T_STAR' => 
      array (
        0 => 'go',
        1 => 's2019',
      ),
      'T_SLASH' => 
      array (
        0 => 'go',
        1 => 's2020',
      ),
      'T_PERCENT' => 
      array (
        0 => 'go',
        1 => 's2021',
      ),
    ),
    's2019' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2022',
      ),
    ),
    's2020' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2023',
      ),
    ),
    's2021' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'UnaryExpression',
        2 => 's2024',
      ),
    ),
    's2022' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 212,
      ),
      'T_STAR' => 
      array (
        0 => 'fold',
        1 => 212,
        2 => 's2018',
      ),
      'T_SLASH' => 
      array (
        0 => 'fold',
        1 => 212,
        2 => 's2018',
      ),
      'T_PERCENT' => 
      array (
        0 => 'fold',
        1 => 212,
        2 => 's2018',
      ),
    ),
    's2023' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 213,
      ),
      'T_STAR' => 
      array (
        0 => 'fold',
        1 => 213,
        2 => 's2018',
      ),
      'T_SLASH' => 
      array (
        0 => 'fold',
        1 => 213,
        2 => 's2018',
      ),
      'T_PERCENT' => 
      array (
        0 => 'fold',
        1 => 213,
        2 => 's2018',
      ),
    ),
    's2024' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 214,
      ),
      'T_STAR' => 
      array (
        0 => 'fold',
        1 => 214,
        2 => 's2018',
      ),
      'T_SLASH' => 
      array (
        0 => 'fold',
        1 => 214,
        2 => 's2018',
      ),
      'T_PERCENT' => 
      array (
        0 => 'fold',
        1 => 214,
        2 => 's2018',
      ),
    ),
    's2045' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression2',
        2 => 's2046',
      ),
    ),
    's2046' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 215,
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 215,
        2 => 's2047',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 215,
        2 => 's2047',
      ),
    ),
    's2047' => 
    array (
      'T_PLUS' => 
      array (
        0 => 'go',
        1 => 's2048',
      ),
      'T_MINUS' => 
      array (
        0 => 'go',
        1 => 's2049',
      ),
    ),
    's2048' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2050',
      ),
    ),
    's2049' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'MultiplicativeExpression',
        2 => 's2051',
      ),
    ),
    's2050' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 216,
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 216,
        2 => 's2047',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 216,
        2 => 's2047',
      ),
    ),
    's2051' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 217,
      ),
      'T_PLUS' => 
      array (
        0 => 'fold',
        1 => 217,
        2 => 's2047',
      ),
      'T_MINUS' => 
      array (
        0 => 'fold',
        1 => 217,
        2 => 's2047',
      ),
    ),
    's2080' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression2',
        2 => 's2081',
      ),
    ),
    's2081' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 218,
      ),
      'T_LTLT' => 
      array (
        0 => 'fold',
        1 => 218,
        2 => 's2082',
      ),
      'T_GTGT' => 
      array (
        0 => 'fold',
        1 => 218,
        2 => 's2082',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'fold',
        1 => 218,
        2 => 's2082',
      ),
    ),
    's2082' => 
    array (
      'T_LTLT' => 
      array (
        0 => 'go',
        1 => 's2083',
      ),
      'T_GTGT' => 
      array (
        0 => 'go',
        1 => 's2084',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'go',
        1 => 's2085',
      ),
    ),
    's2083' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2086',
      ),
    ),
    's2084' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2087',
      ),
    ),
    's2085' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AdditiveExpression',
        2 => 's2088',
      ),
    ),
    's2086' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 219,
      ),
      'T_LTLT' => 
      array (
        0 => 'fold',
        1 => 219,
        2 => 's2082',
      ),
      'T_GTGT' => 
      array (
        0 => 'fold',
        1 => 219,
        2 => 's2082',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'fold',
        1 => 219,
        2 => 's2082',
      ),
    ),
    's2087' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 220,
      ),
      'T_LTLT' => 
      array (
        0 => 'fold',
        1 => 220,
        2 => 's2082',
      ),
      'T_GTGT' => 
      array (
        0 => 'fold',
        1 => 220,
        2 => 's2082',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'fold',
        1 => 220,
        2 => 's2082',
      ),
    ),
    's2088' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 221,
      ),
      'T_LTLT' => 
      array (
        0 => 'fold',
        1 => 221,
        2 => 's2082',
      ),
      'T_GTGT' => 
      array (
        0 => 'fold',
        1 => 221,
        2 => 's2082',
      ),
      'T_GTGTGT' => 
      array (
        0 => 'fold',
        1 => 221,
        2 => 's2082',
      ),
    ),
    's2141' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression2',
        2 => 's2142',
      ),
    ),
    's2142' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 222,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 222,
        2 => 's2143',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 222,
        2 => 's2143',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 222,
        2 => 's2143',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 222,
        2 => 's2143',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 222,
        2 => 's2143',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 222,
        2 => 's2143',
      ),
    ),
    's2143' => 
    array (
      'T_LT' => 
      array (
        0 => 'go',
        1 => 's2144',
      ),
      'T_GT' => 
      array (
        0 => 'go',
        1 => 's2145',
      ),
      'T_LTEQ' => 
      array (
        0 => 'go',
        1 => 's2146',
      ),
      'T_GTEQ' => 
      array (
        0 => 'go',
        1 => 's2147',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'go',
        1 => 's2148',
      ),
      'T_IN' => 
      array (
        0 => 'go',
        1 => 's2149',
      ),
    ),
    's2144' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2150',
      ),
    ),
    's2145' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2151',
      ),
    ),
    's2146' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2152',
      ),
    ),
    's2147' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2153',
      ),
    ),
    's2148' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2154',
      ),
    ),
    's2149' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2155',
      ),
    ),
    's2150' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 223,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 223,
        2 => 's2143',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 223,
        2 => 's2143',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 223,
        2 => 's2143',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 223,
        2 => 's2143',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 223,
        2 => 's2143',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 223,
        2 => 's2143',
      ),
    ),
    's2151' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 224,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 224,
        2 => 's2143',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 224,
        2 => 's2143',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 224,
        2 => 's2143',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 224,
        2 => 's2143',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 224,
        2 => 's2143',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 224,
        2 => 's2143',
      ),
    ),
    's2152' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 225,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 225,
        2 => 's2143',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 225,
        2 => 's2143',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 225,
        2 => 's2143',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 225,
        2 => 's2143',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 225,
        2 => 's2143',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 225,
        2 => 's2143',
      ),
    ),
    's2153' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 226,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 226,
        2 => 's2143',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 226,
        2 => 's2143',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 226,
        2 => 's2143',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 226,
        2 => 's2143',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 226,
        2 => 's2143',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 226,
        2 => 's2143',
      ),
    ),
    's2154' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 227,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 227,
        2 => 's2143',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 227,
        2 => 's2143',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 227,
        2 => 's2143',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 227,
        2 => 's2143',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 227,
        2 => 's2143',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 227,
        2 => 's2143',
      ),
    ),
    's2155' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 228,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 228,
        2 => 's2143',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 228,
        2 => 's2143',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 228,
        2 => 's2143',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 228,
        2 => 's2143',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 228,
        2 => 's2143',
      ),
      'T_IN' => 
      array (
        0 => 'fold',
        1 => 228,
        2 => 's2143',
      ),
    ),
    's2192' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression2',
        2 => 's2193',
      ),
    ),
    's2193' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 229,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 229,
        2 => 's2194',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 229,
        2 => 's2194',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 229,
        2 => 's2194',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 229,
        2 => 's2194',
      ),
    ),
    's2194' => 
    array (
      'T_EQEQ' => 
      array (
        0 => 'go',
        1 => 's2195',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'go',
        1 => 's2196',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'go',
        1 => 's2197',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'go',
        1 => 's2198',
      ),
    ),
    's2195' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2199',
      ),
    ),
    's2196' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2200',
      ),
    ),
    's2197' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2201',
      ),
    ),
    's2198' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpression',
        2 => 's2202',
      ),
    ),
    's2199' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 230,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 230,
        2 => 's2194',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 230,
        2 => 's2194',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 230,
        2 => 's2194',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 230,
        2 => 's2194',
      ),
    ),
    's2200' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 231,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 231,
        2 => 's2194',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 231,
        2 => 's2194',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 231,
        2 => 's2194',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 231,
        2 => 's2194',
      ),
    ),
    's2201' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 232,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 232,
        2 => 's2194',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 232,
        2 => 's2194',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 232,
        2 => 's2194',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 232,
        2 => 's2194',
      ),
    ),
    's2202' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 233,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 233,
        2 => 's2194',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 233,
        2 => 's2194',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 233,
        2 => 's2194',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 233,
        2 => 's2194',
      ),
    ),
    's2215' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression2',
        2 => 's2216',
      ),
    ),
    's2216' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 234,
      ),
      'T_AMP' => 
      array (
        0 => 'fold',
        1 => 234,
        2 => 's2217',
      ),
    ),
    's2217' => 
    array (
      'T_AMP' => 
      array (
        0 => 'go',
        1 => 's2218',
      ),
    ),
    's2218' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'EqualityExpression',
        2 => 's2219',
      ),
    ),
    's2219' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 235,
      ),
      'T_AMP' => 
      array (
        0 => 'fold',
        1 => 235,
        2 => 's2217',
      ),
    ),
    's2232' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression2',
        2 => 's2233',
      ),
    ),
    's2233' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 236,
      ),
      'T_HAT' => 
      array (
        0 => 'fold',
        1 => 236,
        2 => 's2234',
      ),
    ),
    's2234' => 
    array (
      'T_HAT' => 
      array (
        0 => 'go',
        1 => 's2235',
      ),
    ),
    's2235' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpression',
        2 => 's2236',
      ),
    ),
    's2236' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 237,
      ),
      'T_HAT' => 
      array (
        0 => 'fold',
        1 => 237,
        2 => 's2234',
      ),
    ),
    's2249' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression2',
        2 => 's2250',
      ),
    ),
    's2250' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 238,
      ),
      'T_PIPE' => 
      array (
        0 => 'fold',
        1 => 238,
        2 => 's2251',
      ),
    ),
    's2251' => 
    array (
      'T_PIPE' => 
      array (
        0 => 'go',
        1 => 's2252',
      ),
    ),
    's2252' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpression',
        2 => 's2253',
      ),
    ),
    's2253' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 239,
      ),
      'T_PIPE' => 
      array (
        0 => 'fold',
        1 => 239,
        2 => 's2251',
      ),
    ),
    's2266' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression2',
        2 => 's2267',
      ),
    ),
    's2267' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 240,
      ),
      'T_AMPAMP' => 
      array (
        0 => 'fold',
        1 => 240,
        2 => 's2268',
      ),
    ),
    's2268' => 
    array (
      'T_AMPAMP' => 
      array (
        0 => 'go',
        1 => 's2269',
      ),
    ),
    's2269' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpression',
        2 => 's2270',
      ),
    ),
    's2270' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 241,
      ),
      'T_AMPAMP' => 
      array (
        0 => 'fold',
        1 => 241,
        2 => 's2268',
      ),
    ),
    's2283' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression2',
        2 => 's2284',
      ),
    ),
    's2284' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 242,
      ),
      'T_PIPEPIPE' => 
      array (
        0 => 'fold',
        1 => 242,
        2 => 's2285',
      ),
    ),
    's2285' => 
    array (
      'T_PIPEPIPE' => 
      array (
        0 => 'go',
        1 => 's2286',
      ),
    ),
    's2286' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpression',
        2 => 's2287',
      ),
    ),
    's2287' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 243,
      ),
      'T_PIPEPIPE' => 
      array (
        0 => 'fold',
        1 => 243,
        2 => 's2285',
      ),
    ),
    's2304' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpression2',
        2 => 's2305',
      ),
    ),
    's2305' => 
    array (
      'T_QUESTMARK' => 
      array (
        0 => 'go',
        1 => 's2306',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 244,
      ),
    ),
    's2306' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2307',
      ),
    ),
    's2307' => 
    array (
      'T_COLON' => 
      array (
        0 => 'go',
        1 => 's2308',
      ),
    ),
    's2308' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2309',
      ),
    ),
    's2309' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 245,
      ),
    ),
    's2330' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpression2',
        2 => 's2331',
      ),
    ),
    's2331' => 
    array (
      'T_EQUAL' => 
      array (
        0 => 'go',
        1 => 's2332',
      ),
      'T_ASSIGN' => 
      array (
        0 => 'go',
        1 => 's2333',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 246,
      ),
    ),
    's2332' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2334',
      ),
    ),
    's2333' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2335',
      ),
    ),
    's2334' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 247,
      ),
    ),
    's2335' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 248,
      ),
    ),
    's2348' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression2',
        2 => 's2349',
      ),
    ),
    's2349' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 249,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 249,
        2 => 's2350',
      ),
    ),
    's2350' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's2351',
      ),
    ),
    's2351' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpression',
        2 => 's2352',
      ),
    ),
    's2352' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 250,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 250,
        2 => 's2350',
      ),
    ),
    's2397' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2398',
      ),
    ),
    's2398' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 251,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 251,
        2 => 's2399',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 251,
        2 => 's2399',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 251,
        2 => 's2399',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 251,
        2 => 's2399',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 251,
        2 => 's2399',
      ),
    ),
    's2399' => 
    array (
      'T_LT' => 
      array (
        0 => 'go',
        1 => 's2400',
      ),
      'T_GT' => 
      array (
        0 => 'go',
        1 => 's2401',
      ),
      'T_LTEQ' => 
      array (
        0 => 'go',
        1 => 's2402',
      ),
      'T_GTEQ' => 
      array (
        0 => 'go',
        1 => 's2403',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'go',
        1 => 's2404',
      ),
    ),
    's2400' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2405',
      ),
    ),
    's2401' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2406',
      ),
    ),
    's2402' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2407',
      ),
    ),
    's2403' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2408',
      ),
    ),
    's2404' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ShiftExpression',
        2 => 's2409',
      ),
    ),
    's2405' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 252,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 252,
        2 => 's2399',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 252,
        2 => 's2399',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 252,
        2 => 's2399',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 252,
        2 => 's2399',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 252,
        2 => 's2399',
      ),
    ),
    's2406' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 253,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 253,
        2 => 's2399',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 253,
        2 => 's2399',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 253,
        2 => 's2399',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 253,
        2 => 's2399',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 253,
        2 => 's2399',
      ),
    ),
    's2407' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 254,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 254,
        2 => 's2399',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 254,
        2 => 's2399',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 254,
        2 => 's2399',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 254,
        2 => 's2399',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 254,
        2 => 's2399',
      ),
    ),
    's2408' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 255,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 255,
        2 => 's2399',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 255,
        2 => 's2399',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 255,
        2 => 's2399',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 255,
        2 => 's2399',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 255,
        2 => 's2399',
      ),
    ),
    's2409' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 256,
      ),
      'T_LT' => 
      array (
        0 => 'fold',
        1 => 256,
        2 => 's2399',
      ),
      'T_GT' => 
      array (
        0 => 'fold',
        1 => 256,
        2 => 's2399',
      ),
      'T_LTEQ' => 
      array (
        0 => 'fold',
        1 => 256,
        2 => 's2399',
      ),
      'T_GTEQ' => 
      array (
        0 => 'fold',
        1 => 256,
        2 => 's2399',
      ),
      'T_INSTANCEOF' => 
      array (
        0 => 'fold',
        1 => 256,
        2 => 's2399',
      ),
    ),
    's2446' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2447',
      ),
    ),
    's2447' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 257,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 257,
        2 => 's2448',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 257,
        2 => 's2448',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 257,
        2 => 's2448',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 257,
        2 => 's2448',
      ),
    ),
    's2448' => 
    array (
      'T_EQEQ' => 
      array (
        0 => 'go',
        1 => 's2449',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'go',
        1 => 's2450',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'go',
        1 => 's2451',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'go',
        1 => 's2452',
      ),
    ),
    's2449' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2453',
      ),
    ),
    's2450' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2454',
      ),
    ),
    's2451' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2455',
      ),
    ),
    's2452' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'RelationalExpressionNoIn',
        2 => 's2456',
      ),
    ),
    's2453' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 258,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 258,
        2 => 's2448',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 258,
        2 => 's2448',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 258,
        2 => 's2448',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 258,
        2 => 's2448',
      ),
    ),
    's2454' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 259,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 259,
        2 => 's2448',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 259,
        2 => 's2448',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 259,
        2 => 's2448',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 259,
        2 => 's2448',
      ),
    ),
    's2455' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 260,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 260,
        2 => 's2448',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 260,
        2 => 's2448',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 260,
        2 => 's2448',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 260,
        2 => 's2448',
      ),
    ),
    's2456' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 261,
      ),
      'T_EQEQ' => 
      array (
        0 => 'fold',
        1 => 261,
        2 => 's2448',
      ),
      'T_BANGEQ' => 
      array (
        0 => 'fold',
        1 => 261,
        2 => 's2448',
      ),
      'T_EQEQEQ' => 
      array (
        0 => 'fold',
        1 => 261,
        2 => 's2448',
      ),
      'T_BANGEQEQ' => 
      array (
        0 => 'fold',
        1 => 261,
        2 => 's2448',
      ),
    ),
    's2469' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2470',
      ),
    ),
    's2470' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 262,
      ),
      'T_AMP' => 
      array (
        0 => 'fold',
        1 => 262,
        2 => 's2471',
      ),
    ),
    's2471' => 
    array (
      'T_AMP' => 
      array (
        0 => 'go',
        1 => 's2472',
      ),
    ),
    's2472' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'EqualityExpressionNoIn',
        2 => 's2473',
      ),
    ),
    's2473' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 263,
      ),
      'T_AMP' => 
      array (
        0 => 'fold',
        1 => 263,
        2 => 's2471',
      ),
    ),
    's2486' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2487',
      ),
    ),
    's2487' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 264,
      ),
      'T_HAT' => 
      array (
        0 => 'fold',
        1 => 264,
        2 => 's2488',
      ),
    ),
    's2488' => 
    array (
      'T_HAT' => 
      array (
        0 => 'go',
        1 => 's2489',
      ),
    ),
    's2489' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseANDExpressionNoIn',
        2 => 's2490',
      ),
    ),
    's2490' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 265,
      ),
      'T_HAT' => 
      array (
        0 => 'fold',
        1 => 265,
        2 => 's2488',
      ),
    ),
    's2503' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2504',
      ),
    ),
    's2504' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 266,
      ),
      'T_PIPE' => 
      array (
        0 => 'fold',
        1 => 266,
        2 => 's2505',
      ),
    ),
    's2505' => 
    array (
      'T_PIPE' => 
      array (
        0 => 'go',
        1 => 's2506',
      ),
    ),
    's2506' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseXORExpressionNoIn',
        2 => 's2507',
      ),
    ),
    's2507' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 267,
      ),
      'T_PIPE' => 
      array (
        0 => 'fold',
        1 => 267,
        2 => 's2505',
      ),
    ),
    's2520' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2521',
      ),
    ),
    's2521' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 268,
      ),
      'T_AMPAMP' => 
      array (
        0 => 'fold',
        1 => 268,
        2 => 's2522',
      ),
    ),
    's2522' => 
    array (
      'T_AMPAMP' => 
      array (
        0 => 'go',
        1 => 's2523',
      ),
    ),
    's2523' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'BitwiseORExpressionNoIn',
        2 => 's2524',
      ),
    ),
    's2524' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 269,
      ),
      'T_AMPAMP' => 
      array (
        0 => 'fold',
        1 => 269,
        2 => 's2522',
      ),
    ),
    's2537' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2538',
      ),
    ),
    's2538' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 270,
      ),
      'T_PIPEPIPE' => 
      array (
        0 => 'fold',
        1 => 270,
        2 => 's2539',
      ),
    ),
    's2539' => 
    array (
      'T_PIPEPIPE' => 
      array (
        0 => 'go',
        1 => 's2540',
      ),
    ),
    's2540' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalANDExpressionNoIn',
        2 => 's2541',
      ),
    ),
    's2541' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 271,
      ),
      'T_PIPEPIPE' => 
      array (
        0 => 'fold',
        1 => 271,
        2 => 's2539',
      ),
    ),
    's2558' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'LogicalORExpressionNoIn',
        2 => 's2559',
      ),
    ),
    's2559' => 
    array (
      'T_QUESTMARK' => 
      array (
        0 => 'go',
        1 => 's2560',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 272,
      ),
    ),
    's2560' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2561',
      ),
    ),
    's2561' => 
    array (
      'T_COLON' => 
      array (
        0 => 'go',
        1 => 's2562',
      ),
    ),
    's2562' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2563',
      ),
    ),
    's2563' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 273,
      ),
    ),
    's2584' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'ConditionalExpressionNoIn',
        2 => 's2585',
      ),
    ),
    's2585' => 
    array (
      'T_EQUAL' => 
      array (
        0 => 'go',
        1 => 's2586',
      ),
      'T_ASSIGN' => 
      array (
        0 => 'go',
        1 => 's2587',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 274,
      ),
    ),
    's2586' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2588',
      ),
    ),
    's2587' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2589',
      ),
    ),
    's2588' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 275,
      ),
    ),
    's2589' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 276,
      ),
    ),
    's2602' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2603',
      ),
    ),
    's2603' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 277,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 277,
        2 => 's2604',
      ),
    ),
    's2604' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's2605',
      ),
    ),
    's2605' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2606',
      ),
    ),
    's2606' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 278,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 278,
        2 => 's2604',
      ),
    ),
    's2619' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'VariableDeclarationNoIn',
        2 => 's2620',
      ),
    ),
    's2620' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 279,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 279,
        2 => 's2621',
      ),
    ),
    's2621' => 
    array (
      'T_COMMA' => 
      array (
        0 => 'go',
        1 => 's2622',
      ),
    ),
    's2622' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'VariableDeclarationNoIn',
        2 => 's2623',
      ),
    ),
    's2623' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 280,
      ),
      'T_COMMA' => 
      array (
        0 => 'fold',
        1 => 280,
        2 => 's2621',
      ),
    ),
    's2632' => 
    array (
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'Identifier',
        2 => 's2633',
      ),
    ),
    's2633' => 
    array (
      'T_EQUAL' => 
      array (
        0 => 'push',
        1 => 'InitialiserNoIn',
        2 => 's2634',
      ),
      '[default]' => 
      array (
        0 => 'do',
        1 => 281,
      ),
    ),
    's2634' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 281,
      ),
    ),
    's2643' => 
    array (
      'T_EQUAL' => 
      array (
        0 => 'go',
        1 => 's2644',
      ),
    ),
    's2644' => 
    array (
      'T_DELETE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_VOID' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_TYPEOF' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_PLUSPLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_MINUSMINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_PLUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_MINUS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_TILDE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_BANG' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_NEW' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_THIS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_LEFTPARENS' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_FUNCTION' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_WORD' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_NULL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_LEFTBRACKET' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_LEFTBRACE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_TRUE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_FALSE' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_DECIMAL' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_HEXA' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
      'T_STRING' => 
      array (
        0 => 'push',
        1 => 'AssignmentExpressionNoIn',
        2 => 's2645',
      ),
    ),
    's2645' => 
    array (
      '[default]' => 
      array (
        0 => 'do',
        1 => 282,
      ),
    ),
  ),
  'action' => 
  array (
    16 => '__lambda_25',
    17 => '__lambda_26',
    18 => '__lambda_27',
    19 => '__lambda_28',
    20 => '__lambda_29',
    21 => '__lambda_30',
    22 => '__lambda_31',
    23 => '__lambda_32',
    24 => '__lambda_33',
    25 => '__lambda_34',
    26 => '__lambda_35',
    27 => '__lambda_36',
    28 => '__lambda_37',
    29 => '__lambda_37',
    30 => '__lambda_37',
    31 => '__lambda_37',
    32 => '__lambda_37',
    33 => '__lambda_37',
    34 => '__lambda_37',
    35 => '__lambda_37',
    36 => '__lambda_37',
    37 => '__lambda_37',
    38 => '__lambda_37',
    39 => '__lambda_37',
    40 => '__lambda_37',
    41 => '__lambda_37',
    42 => '__lambda_37',
    43 => '__lambda_37',
    44 => '__lambda_38',
    45 => '__lambda_39',
    46 => '__lambda_40',
    47 => '__lambda_41',
    48 => '__lambda_42',
    49 => '__lambda_43',
    50 => '__lambda_44',
    51 => '__lambda_45',
    52 => '__lambda_46',
    53 => '__lambda_47',
    54 => '__lambda_36',
    55 => '__lambda_48',
    56 => '__lambda_49',
    57 => '__lambda_50',
    58 => '__lambda_51',
    59 => '__lambda_52',
    60 => '__lambda_53',
    61 => '__lambda_54',
    62 => '__lambda_55',
    63 => '__lambda_56',
    64 => '__lambda_57',
    65 => '__lambda_58',
    66 => '__lambda_59',
    67 => '__lambda_60',
    68 => '__lambda_61',
    69 => '__lambda_62',
    70 => '__lambda_63',
    71 => '__lambda_64',
    72 => '__lambda_65',
    73 => '__lambda_66',
    74 => '__lambda_67',
    75 => '__lambda_67',
    76 => '__lambda_68',
    77 => '__lambda_35',
    78 => '__lambda_69',
    79 => '__lambda_70',
    80 => '__lambda_71',
    81 => '__lambda_72',
    82 => '__lambda_73',
    83 => '__lambda_74',
    84 => '__lambda_75',
    85 => '__lambda_76',
    86 => '__lambda_77',
    87 => '__lambda_78',
    88 => '__lambda_79',
    89 => '__lambda_80',
    90 => '__lambda_81',
    91 => '__lambda_81',
    92 => '__lambda_81',
    93 => '__lambda_49',
    94 => '__lambda_82',
    95 => '__lambda_83',
    96 => '__lambda_84',
    97 => '__lambda_81',
    98 => '__lambda_85',
    99 => '__lambda_86',
    100 => '__lambda_37',
    101 => '__lambda_37',
    102 => '__lambda_87',
    103 => '__lambda_88',
    104 => '__lambda_35',
    105 => '__lambda_89',
    106 => '__lambda_90',
    107 => '__lambda_37',
    108 => '__lambda_91',
    109 => '__lambda_92',
    110 => '__lambda_93',
    111 => '__lambda_94',
    112 => '__lambda_95',
    113 => '__lambda_96',
    114 => '__lambda_97',
    115 => '__lambda_37',
    116 => '__lambda_98',
    117 => '__lambda_37',
    118 => '__lambda_37',
    119 => '__lambda_99',
    120 => '__lambda_100',
    121 => '__lambda_101',
    122 => '__lambda_102',
    123 => '__lambda_103',
    124 => '__lambda_104',
    125 => '__lambda_35',
    126 => '__lambda_105',
    127 => '__lambda_37',
    128 => '__lambda_102',
    129 => '__lambda_99',
    130 => '__lambda_100',
    131 => '__lambda_37',
    132 => '__lambda_106',
    133 => '__lambda_107',
    134 => '__lambda_37',
    135 => '__lambda_108',
    136 => '__lambda_109',
    137 => '__lambda_110',
    138 => '__lambda_111',
    139 => '__lambda_112',
    140 => '__lambda_113',
    141 => '__lambda_114',
    142 => '__lambda_115',
    143 => '__lambda_116',
    144 => '__lambda_37',
    145 => '__lambda_117',
    146 => '__lambda_118',
    147 => '__lambda_119',
    148 => '__lambda_37',
    149 => '__lambda_120',
    150 => '__lambda_121',
    151 => '__lambda_37',
    152 => '__lambda_122',
    153 => '__lambda_123',
    154 => '__lambda_124',
    155 => '__lambda_125',
    156 => '__lambda_126',
    157 => '__lambda_127',
    158 => '__lambda_128',
    159 => '__lambda_129',
    160 => '__lambda_130',
    161 => '__lambda_131',
    162 => '__lambda_37',
    163 => '__lambda_132',
    164 => '__lambda_133',
    165 => '__lambda_134',
    166 => '__lambda_135',
    167 => '__lambda_37',
    168 => '__lambda_136',
    169 => '__lambda_37',
    170 => '__lambda_137',
    171 => '__lambda_37',
    172 => '__lambda_138',
    173 => '__lambda_37',
    174 => '__lambda_139',
    175 => '__lambda_37',
    176 => '__lambda_140',
    177 => '__lambda_37',
    178 => '__lambda_141',
    179 => '__lambda_37',
    180 => '__lambda_142',
    181 => '__lambda_143',
    182 => '__lambda_37',
    183 => '__lambda_144',
    184 => '__lambda_79',
    185 => '__lambda_80',
    186 => '__lambda_81',
    187 => '__lambda_81',
    188 => '__lambda_49',
    189 => '__lambda_37',
    190 => '__lambda_99',
    191 => '__lambda_100',
    192 => '__lambda_101',
    193 => '__lambda_102',
    194 => '__lambda_37',
    195 => '__lambda_102',
    196 => '__lambda_99',
    197 => '__lambda_100',
    198 => '__lambda_37',
    199 => '__lambda_106',
    200 => '__lambda_107',
    201 => '__lambda_37',
    202 => '__lambda_108',
    203 => '__lambda_109',
    204 => '__lambda_110',
    205 => '__lambda_111',
    206 => '__lambda_112',
    207 => '__lambda_113',
    208 => '__lambda_114',
    209 => '__lambda_115',
    210 => '__lambda_116',
    211 => '__lambda_37',
    212 => '__lambda_117',
    213 => '__lambda_118',
    214 => '__lambda_119',
    215 => '__lambda_37',
    216 => '__lambda_120',
    217 => '__lambda_121',
    218 => '__lambda_37',
    219 => '__lambda_122',
    220 => '__lambda_123',
    221 => '__lambda_124',
    222 => '__lambda_125',
    223 => '__lambda_126',
    224 => '__lambda_127',
    225 => '__lambda_128',
    226 => '__lambda_129',
    227 => '__lambda_130',
    228 => '__lambda_131',
    229 => '__lambda_37',
    230 => '__lambda_132',
    231 => '__lambda_133',
    232 => '__lambda_134',
    233 => '__lambda_135',
    234 => '__lambda_37',
    235 => '__lambda_136',
    236 => '__lambda_37',
    237 => '__lambda_137',
    238 => '__lambda_37',
    239 => '__lambda_138',
    240 => '__lambda_37',
    241 => '__lambda_139',
    242 => '__lambda_37',
    243 => '__lambda_140',
    244 => '__lambda_37',
    245 => '__lambda_141',
    246 => '__lambda_37',
    247 => '__lambda_142',
    248 => '__lambda_143',
    249 => '__lambda_37',
    250 => '__lambda_144',
    251 => '__lambda_125',
    252 => '__lambda_126',
    253 => '__lambda_127',
    254 => '__lambda_128',
    255 => '__lambda_129',
    256 => '__lambda_130',
    257 => '__lambda_37',
    258 => '__lambda_132',
    259 => '__lambda_133',
    260 => '__lambda_134',
    261 => '__lambda_135',
    262 => '__lambda_37',
    263 => '__lambda_136',
    264 => '__lambda_37',
    265 => '__lambda_137',
    266 => '__lambda_37',
    267 => '__lambda_138',
    268 => '__lambda_37',
    269 => '__lambda_139',
    270 => '__lambda_37',
    271 => '__lambda_140',
    272 => '__lambda_37',
    273 => '__lambda_141',
    274 => '__lambda_37',
    275 => '__lambda_142',
    276 => '__lambda_143',
    277 => '__lambda_37',
    278 => '__lambda_144',
    279 => '__lambda_47',
    280 => '__lambda_36',
    281 => '__lambda_48',
    282 => '__lambda_49',
  ),
);
?>