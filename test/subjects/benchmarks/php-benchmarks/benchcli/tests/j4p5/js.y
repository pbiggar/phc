# first shot at ecma-262 grammar file

Program: Source		{ return new js_program({0}); }

Source: EPSILON 		{ return new js_source(); }
 | Source Statement		{ {0}->addStatement({1}); return {0}; }
 | Source FunctionDeclaration	{ {0}->addFunction(new js_function_definition({1})); return {0}; }

FunctionDeclaration: T_FUNCTION Identifier T_LEFTPARENS T_RIGHTPARENS T_LEFTBRACE Source T_RIGHTBRACE { return array({1},array(),{5}); }
 | T_FUNCTION Identifier T_LEFTPARENS FormalParameterList T_RIGHTPARENS T_LEFTBRACE Source T_RIGHTBRACE { return array({1},{3},{6}); }

FunctionExpression : T_FUNCTION T_LEFTPARENS T_RIGHTPARENS T_LEFTBRACE Source T_RIGHTBRACE { return new js_function_definition(array('',array(),{4})); }
 | T_FUNCTION Identifier T_LEFTPARENS T_RIGHTPARENS T_LEFTBRACE Source T_RIGHTBRACE { return new js_function_definition(array({1},array(),{5})); }
 | T_FUNCTION T_LEFTPARENS FormalParameterList T_RIGHTPARENS T_LEFTBRACE Source T_RIGHTBRACE { return new js_function_definition(array('',{2},{5})); }
 | T_FUNCTION Identifier T_LEFTPARENS FormalParameterList T_RIGHTPARENS T_LEFTBRACE Source T_RIGHTBRACE { return new js_function_definition(array({1},{3},{6})); }

FormalParameterList: Identifier			{return array({0});}
                   | FormalParameterList T_COMMA Identifier { {0}[]={2}; return {0}; }

Identifier: T_WORD				{return {0};}

Statement: Block {return {0};}
         | VariableStatement {return {0};}
         | EmptyStatement {return {0};}
         | ExpressionStatement {return {0};}
         | IfStatement {return {0};}
         | IterationStatement {return {0};}
         | ContinueStatement {return {0};}
         | BreakStatement {return {0};}
         | ReturnStatement {return {0};}
         | WithStatement {return {0};}
         | LabelledStatement {return {0};}
         | SwitchStatement {return {0};}
         | ThrowStatement {return {0};}
         | TryStatement {return {0};}
         | TextStatement {return {0};}

TextStatement: T_SCRIPT_END T_SCRIPT_BEGIN { return new js_nop(); }
 | T_SCRIPT_END T_SCRIPT_BEGIN_ECHO ExpressionStatement { return new js_print({2}); }
 | T_SCRIPT_END T_TEXT T_SCRIPT_BEGIN { return new js_print(new js_literal_string({1},0)); }
 | T_SCRIPT_END T_TEXT T_SCRIPT_BEGIN_ECHO ExpressionStatement {
    return new js_print(js_plus(new js_literal_string({1},0), {3}));
}

Block: T_LEFTBRACE T_RIGHTBRACE  {return new js_nop();}
 | T_LEFTBRACE StatementList T_RIGHTBRACE  {return new js_block({1});}

StatementList: Statement { return array({0});}
 | StatementList Statement { {0}[]={1}; return {0};}

VariableStatement: T_VAR VariableDeclarationList T_SEMICOLON { 
  return new js_var({1});
}

VariableDeclarationList: VariableDeclaration  { return array({0}); }
                       | VariableDeclarationList T_COMMA VariableDeclaration { {0}[]={2}; return {0}; }

VariableDeclaration: Identifier Initialiser? { return @array({0},{1});}

Initialiser: T_EQUAL AssignmentExpression { return {1}; }

EmptyStatement: T_SEMICOLON { return new js_nop();}

ExpressionStatement: Expression2 T_SEMICOLON {return new js_statement({0});}

IfStatement: T_IF T_LEFTPARENS Expression T_RIGHTPARENS Statement T_ELSE Statement {
  return new js_if({2}, {4}, {6});
}
 | T_IF T_LEFTPARENS Expression T_RIGHTPARENS Statement {
  return new js_if({2}, {4});
}

# slightly modified statement, to keep our peculiar CFG happy.
IterationStatement: T_DO Statement T_WHILE T_LEFTPARENS Expression T_RIGHTPARENS T_SEMICOLON { return new js_do({4},{1}); }
  | T_WHILE T_LEFTPARENS Expression T_RIGHTPARENS Statement { return new js_while({2}, {4}); }
  | T_FOR T_LEFTPARENS ExpressionNoIn T_IN Expression T_RIGHTPARENS Statement {return new js_for_in({2}, {4}, {6});}
  | T_FOR T_LEFTPARENS ExpressionNoIn? T_SEMICOLON Expression? T_SEMICOLON Expression? T_RIGHTPARENS Statement {
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
  | T_FOR T_LEFTPARENS T_VAR VariableDeclarationListNoIn T_SEMICOLON Expression? T_SEMICOLON Expression? T_RIGHTPARENS Statement {
    $k=5;
    if ($tokens[$k]==';') { $a2=new js_nop(); $k++; }
    else { $a2=$tokens[$k]; $k+=2; }
    if ($tokens[$k]==')') { $a3=new js_nop(); $k++; }
    else { $a3=$tokens[$k]; $k+=2; }
    $a4=$tokens[$k];
    return new js_for( new js_var({3}), $a2, $a3, $a4);
}
  | T_FOR T_LEFTPARENS T_VAR VariableDeclarationListNoIn T_IN Expression T_RIGHTPARENS Statement {return new js_for_in( new js_var({3}), {5}, {7});}

# XXX no line terminators between continue and identifier
ContinueStatement: T_CONTINUE Identifier? T_SEMICOLON {return @new js_continue({1});}

# XXX no line terminators between break and identifier
BreakStatement: T_BREAK Identifier? T_SEMICOLON {return @new js_break({1});}

# XXX no line terminators between return and identifier
ReturnStatement: T_RETURN Expression? T_SEMICOLON {return @new js_return({1});}

WithStatement: T_WITH T_LEFTPARENS Expression T_RIGHTPARENS Statement {return new js_with({2},{4});}

SwitchStatement: T_SWITCH T_LEFTPARENS Expression T_RIGHTPARENS CaseBlock {
  return new js_switch({2}, {4});
}

CaseBlock : T_LEFTBRACE CaseClauses? T_RIGHTBRACE {if ({1}=='}') return array(); else return {1};}
 | T_LEFTBRACE DefaultClause T_RIGHTBRACE {
  return {1};
}
 | T_LEFTBRACE DefaultClause CaseClauses T_RIGHTBRACE {
  return array_merge({1},{2});
}
 | T_LEFTBRACE CaseClauses DefaultClause T_RIGHTBRACE {
  return array_merge({1},{2});
}
 | T_LEFTBRACE CaseClauses DefaultClause CaseClauses T_RIGHTBRACE {
  return array_merge({1},{2},{3});
}
 
CaseClauses: CaseClause {return array({0});}
 | CaseClauses CaseClause {{0}[] = {1}; return {0};}
 
CaseClause: T_CASE Expression T_COLON StatementList? {return new js_case({1},{3});}

DefaultClause: T_DEFAULT T_COLON StatementList? {return array(new js_case(0, {2}));}

# introducing the T_LABEL.. it's that, or confuse the CFGP to heck.
LabelledStatement: T_LABEL Statement {return new js_label({0}, {1});}

# XXX no line terminators between throw and expression
ThrowStatement: T_THROW Expression T_SEMICOLON {return new js_throw({1});}

TryStatement: T_TRY Block Catch {return new js_try({1},{2}, NULL);}
 | T_TRY Block Finally 		{return new js_try({1}, NULL, {2});}
 | T_TRY Block Catch Finally 	{return new js_try({1}, {2}, {3});}

Catch: T_CATCH T_LEFTPARENS Identifier T_RIGHTPARENS Block {return new js_catch({2}, {4});}

Finally: T_FINALLY Block { return {1};}

PrimaryExpression: T_THIS { return new js_this();}
 | Identifier { return new js_identifier({0});}
 | Literal { return {0}; }
 | ArrayLiteral { return {0}; }
 | ObjectLiteral { return {0}; }
 | T_LEFTPARENS Expression T_RIGHTPARENS { return {1}; }

Literal: T_NULL { return new js_literal_null(); }
 | BooleanLiteral { return new js_literal_boolean({0}); }
 | NumericLiteral { return new js_literal_number({0}); }
 | StringLiteral { return {0}; }
 
BooleanLiteral: T_TRUE {return TRUE;} | T_FALSE {return FALSE;}

NumericLiteral: T_DECIMAL {return {0};} | T_HEXA {return {0};}

StringLiteral: T_STRING {return new js_literal_string({0});}

#-- Array definition without weird Elision rules
ArrayLiteral: T_LEFTBRACKET ArrayElements T_RIGHTBRACKET {return new js_literal_array({1});}
ArrayElements: ArrayElement		{return array({0});}
 | ArrayElements T_COMMA ArrayElement	{{0}[] = {2}; return {0};}
ArrayElement: EPSILON   {return new js_literal_null();}
 | AssignmentExpression	{return {0};}

#-- Object definition, identical to the sample grammaer
ObjectLiteral: T_LEFTBRACE T_RIGHTBRACE {return new js_literal_object();}
 | T_LEFTBRACE PropertyNameAndValueList T_RIGHTBRACE {return new js_literal_object({1});}
PropertyNameAndValueList: PropertyName T_COLON AssignmentExpression {return array({0},{2});}
 | T_LABEL AssignmentExpression {$p=explode(':', {0}); return array(new js_literal_string($p[0],0),{1});}
 | PropertyNameAndValueList T_COMMA PropertyName T_COLON AssignmentExpression {{0}[]={2};{0}[]={4};return {0};}
 | PropertyNameAndValueList T_COMMA T_LABEL AssignmentExpression {$p=explode(':', {2}); {0}[]=new js_literal_string($p[0],0);{0}[]={3}; return {0};}

PropertyName: Identifier {return new js_literal_string({0},0);}
 | StringLiteral         {return {0};}
 | NumericLiteral        {return new js_literal_number({0});}

MemberExpression: PrimaryExpression {return {0};}
 | FunctionExpression {return {0};}
 | MemberExpression T_LEFTBRACKET Expression T_RIGHTBRACKET {return new js_accessor({0},{2},1);}
 | MemberExpression T_DOT Identifier {return new js_accessor({0},new js_identifier({2}),0);}
 | T_NEW MemberExpression {return new js_new({1});}
 | MemberExpression Arguments {return new js_call({0},{1});}

# only used for left hand side expr.
# can't think of a practical need for " new Object = 2" syntax..
# plus, this parser bitches at the epsilon nondeterministic-ness of it all.
#NewExpression: MemberExpression {}
# | T_NEW NewExpression {}
#
#CallExpression: MemberExpression Arguments {}
# | CallExpression Arguments {}
# | CallExpression T_LEFTBRACKET Expression T_RIGHTBRACKET {}
# | CallExpression T_DOT Identifier {}
 
Arguments: T_LEFTPARENS T_RIGHTPARENS {return array(); }
 | T_LEFTPARENS ArgumentList T_RIGHTPARENS {return (array){1};}

ArgumentList: AssignmentExpression 			{return array({0});}
 | ArgumentList T_COMMA AssignmentExpression		{{0}[]={2};return {0};}

#LeftHandSideExpression: NewExpression {} | CallExpression {}

LeftHandSideExpression: MemberExpression {return {0};}
 | LeftHandSideExpression Arguments {return new js_call({0},{1});}
 | LeftHandSideExpression T_LEFTBRACKET Expression T_RIGHTBRACKET {return new js_accessor({0},{2},1);}
 | LeftHandSideExpression T_DOT Identifier {return new js_accessor({0},new js_identifier({2}),0);}
 
PostfixExpression: LeftHandSideExpression 	{return {0};}
 | LeftHandSideExpression T_PLUSPLUS		{return new js_post_pp({0});}
 | LeftHandSideExpression T_MINUSMINUS 		{return new js_post_mm({0});}
 
UnaryExpression: PostfixExpression 	{return {0};}
 | T_DELETE UnaryExpression 		{return new js_delete({1});}
 | T_VOID UnaryExpression 		{return new js_void({1});}
 | T_TYPEOF UnaryExpression 		{return new js_typeof({1});}
 | T_PLUSPLUS UnaryExpression		{return new js_pre_pp({1});}
 | T_MINUSMINUS UnaryExpression		{return new js_pre_mm({1});}
 | T_PLUS UnaryExpression		{return new js_u_plus({1});}
 | T_MINUS UnaryExpression		{return new js_u_minus({1});}
 | T_TILDE UnaryExpression		{return new js_bit_not({1});}
 | T_BANG UnaryExpression		{return new js_not({1});}
 
MultiplicativeExpression: UnaryExpression {return {0};}
 | MultiplicativeExpression T_STAR UnaryExpression {return new js_multiply({0},{2});}
 | MultiplicativeExpression T_SLASH UnaryExpression {return new js_divide({0},{2});}
 | MultiplicativeExpression T_PERCENT UnaryExpression {return new js_modulo({0},{2});}

AdditiveExpression: MultiplicativeExpression {return {0};}
 | AdditiveExpression T_PLUS MultiplicativeExpression {return new js_plus({0},{2});}
 | AdditiveExpression T_MINUS MultiplicativeExpression {return new js_minus({0},{2});}

ShiftExpression: AdditiveExpression 		{return {0};}
 | ShiftExpression T_LTLT AdditiveExpression   	{return new js_lsh({0},{2});}
 | ShiftExpression T_GTGT AdditiveExpression   	{return new js_rsh({0},{2});}
 | ShiftExpression T_GTGTGT AdditiveExpression 	{return new js_ursh({0},{2});}

RelationalExpression: ShiftExpression {return 	{0};}
 | RelationalExpression T_LT ShiftExpression 	{return new js_lt({0},{2});}
 | RelationalExpression T_GT ShiftExpression 	{return new js_gt({0},{2});}
 | RelationalExpression T_LTEQ ShiftExpression 	{return new js_lte({0},{2});}
 | RelationalExpression T_GTEQ ShiftExpression 	{return new js_gte({0},{2});}
 | RelationalExpression T_INSTANCEOF ShiftExpression {return new js_instanceof({0},{2});}
 | RelationalExpression T_IN ShiftExpression 	{return new js_in({0},{2});}

EqualityExpression: RelationalExpression {return {0};}
 | EqualityExpression T_EQEQ RelationalExpression   {return new js_equal({0},{2});}
 | EqualityExpression T_BANGEQ RelationalExpression {return new js_not_equal({0},{2});}
 | EqualityExpression T_EQEQEQ RelationalExpression {return new js_strict_equal({0},{2});}
 | EqualityExpression T_BANGEQEQ RelationalExpression {return new js_strict_not_equal({0},{2});}

BitwiseANDExpression: EqualityExpression {return {0};}
 | BitwiseANDExpression T_AMP EqualityExpression {return new js_bit_and({0},{2});}

BitwiseXORExpression: BitwiseANDExpression {return {0};}
 | BitwiseXORExpression T_HAT BitwiseANDExpression {return new js_bit_xor({0},{2});}

BitwiseORExpression: BitwiseXORExpression {return {0};}
 | BitwiseORExpression T_PIPE BitwiseXORExpression {return new js_bit_or({0},{2});}

LogicalANDExpression: BitwiseORExpression {return {0};}
 | LogicalANDExpression T_AMPAMP BitwiseORExpression {return new js_and({0},{2});}

LogicalORExpression: LogicalANDExpression {return {0};}
 | LogicalORExpression T_PIPEPIPE LogicalANDExpression {return new js_or({0},{2});}

ConditionalExpression: LogicalORExpression {return {0};}
 | LogicalORExpression T_QUESTMARK AssignmentExpression T_COLON AssignmentExpression {return new js_ternary({0},{2},{4});}

AssignmentExpression: ConditionalExpression {return {0};}
 | ConditionalExpression T_EQUAL AssignmentExpression {return new js_assign({0},{2});}
 | ConditionalExpression T_ASSIGN AssignmentExpression {return new js_compound_assign({0},{2},{1});}

Expression: AssignmentExpression {return {0};}
 | Expression T_COMMA AssignmentExpression {return new js_comma({0},{2});}

#-- Expression2 stuff, to solve the "{" and "function" ambiguity in an expression-statement

PrimaryExpression2: T_THIS { return new js_this();}
 | Identifier { return new js_identifier({0});}
 | Literal { return {0}; }
 | ArrayLiteral { return {0}; }
 | T_LEFTPARENS Expression T_RIGHTPARENS { return {1}; }

MemberExpression2: PrimaryExpression2 {return {0};}
 | MemberExpression2 T_LEFTBRACKET Expression T_RIGHTBRACKET {return new js_accessor({0},{2},1);}
 | MemberExpression2 T_DOT Identifier {return new js_accessor({0},new js_identifier({2}),0);}
 | T_NEW MemberExpression2 {return new js_new({1});}
 | MemberExpression2 Arguments {return new js_call({0},{1});}
 
LeftHandSideExpression2: MemberExpression2 {return {0};}
 | LeftHandSideExpression2 Arguments {return new js_call({0},{1});}
 | LeftHandSideExpression2 T_LEFTBRACKET Expression T_RIGHTBRACKET {return new js_accessor({0},{2},1);}
 | LeftHandSideExpression2 T_DOT Identifier {return new js_accessor({0},new js_identifier({2}),0);}
 
PostfixExpression2: LeftHandSideExpression2 	{return {0};}
 | LeftHandSideExpression2 T_PLUSPLUS		{return new js_post_pp({0});}
 | LeftHandSideExpression2 T_MINUSMINUS 		{return new js_post_mm({0});}
 
UnaryExpression2: PostfixExpression2 	{return {0};}
 | T_DELETE UnaryExpression 		{return new js_delete({1});}
 | T_VOID UnaryExpression 		{return new js_void({1});}
 | T_TYPEOF UnaryExpression 		{return new js_typeof({1});}
 | T_PLUSPLUS UnaryExpression		{return new js_pre_pp({1});}
 | T_MINUSMINUS UnaryExpression		{return new js_pre_mm({1});}
 | T_PLUS UnaryExpression		{return new js_u_plus({1});}
 | T_MINUS UnaryExpression		{return new js_u_minus({1});}
 | T_TILDE UnaryExpression		{return new js_bit_not({1});}
 | T_BANG UnaryExpression		{return new js_not({1});}
 
MultiplicativeExpression2: UnaryExpression2 {return {0};}
 | MultiplicativeExpression2 T_STAR UnaryExpression {return new js_multiply({0},{2});}
 | MultiplicativeExpression2 T_SLASH UnaryExpression {return new js_divide({0},{2});}
 | MultiplicativeExpression2 T_PERCENT UnaryExpression {return new js_modulo({0},{2});}

AdditiveExpression2: MultiplicativeExpression2 {return {0};}
 | AdditiveExpression2 T_PLUS MultiplicativeExpression {return new js_plus({0},{2});}
 | AdditiveExpression2 T_MINUS MultiplicativeExpression {return new js_minus({0},{2});}

ShiftExpression2: AdditiveExpression2 		{return {0};}
 | ShiftExpression2 T_LTLT AdditiveExpression   	{return new js_lsh({0},{2});}
 | ShiftExpression2 T_GTGT AdditiveExpression   	{return new js_rsh({0},{2});}
 | ShiftExpression2 T_GTGTGT AdditiveExpression 	{return new js_ursh({0},{2});}

RelationalExpression2: ShiftExpression2 {return 	{0};}
 | RelationalExpression2 T_LT ShiftExpression 	{return new js_lt({0},{2});}
 | RelationalExpression2 T_GT ShiftExpression 	{return new js_gt({0},{2});}
 | RelationalExpression2 T_LTEQ ShiftExpression 	{return new js_lte({0},{2});}
 | RelationalExpression2 T_GTEQ ShiftExpression 	{return new js_gte({0},{2});}
 | RelationalExpression2 T_INSTANCEOF ShiftExpression {return new js_instanceof({0},{2});}
 | RelationalExpression2 T_IN ShiftExpression 	{return new js_in({0},{2});}

EqualityExpression2: RelationalExpression2 {return {0};}
 | EqualityExpression2 T_EQEQ RelationalExpression   {return new js_equal({0},{2});}
 | EqualityExpression2 T_BANGEQ RelationalExpression {return new js_not_equal({0},{2});}
 | EqualityExpression2 T_EQEQEQ RelationalExpression {return new js_strict_equal({0},{2});}
 | EqualityExpression2 T_BANGEQEQ RelationalExpression {return new js_strict_not_equal({0},{2});}

BitwiseANDExpression2: EqualityExpression2 {return {0};}
 | BitwiseANDExpression2 T_AMP EqualityExpression {return new js_bit_and({0},{2});}

BitwiseXORExpression2: BitwiseANDExpression2 {return {0};}
 | BitwiseXORExpression2 T_HAT BitwiseANDExpression {return new js_bit_xor({0},{2});}

BitwiseORExpression2: BitwiseXORExpression2 {return {0};}
 | BitwiseORExpression2 T_PIPE BitwiseXORExpression {return new js_bit_or({0},{2});}

LogicalANDExpression2: BitwiseORExpression2 {return {0};}
 | LogicalANDExpression2 T_AMPAMP BitwiseORExpression {return new js_and({0},{2});}

LogicalORExpression2: LogicalANDExpression2 {return {0};}
 | LogicalORExpression2 T_PIPEPIPE LogicalANDExpression {return new js_or({0},{2});}

ConditionalExpression2: LogicalORExpression2 {return {0};}
 | LogicalORExpression2 T_QUESTMARK AssignmentExpression T_COLON AssignmentExpression {return new js_ternary({0},{2},{4});}

AssignmentExpression2: ConditionalExpression2 {return {0};}
 | ConditionalExpression2 T_EQUAL AssignmentExpression {return new js_assign({0},{2});}
 | ConditionalExpression2 T_ASSIGN AssignmentExpression {return new js_compound_assign({0},{2},{1});}

Expression2: AssignmentExpression2 {return {0};}
 | Expression2 T_COMMA AssignmentExpression {return new js_comma({0},{2});}

#-- The NoIn stuff, to have for(;;) and for(a in b) work nicely together.
 
RelationalExpressionNoIn: ShiftExpression {return 	{0};}
 | RelationalExpressionNoIn T_LT ShiftExpression 	{return new js_lt({0},{2});}
 | RelationalExpressionNoIn T_GT ShiftExpression 	{return new js_gt({0},{2});}
 | RelationalExpressionNoIn T_LTEQ ShiftExpression 	{return new js_lte({0},{2});}
 | RelationalExpressionNoIn T_GTEQ ShiftExpression 	{return new js_gte({0},{2});}
 | RelationalExpressionNoIn T_INSTANCEOF ShiftExpression {return new js_instanceof({0},{2});}

EqualityExpressionNoIn: RelationalExpressionNoIn {return {0};}
 | EqualityExpressionNoIn T_EQEQ RelationalExpressionNoIn   {return new js_equal({0},{2});}
 | EqualityExpressionNoIn T_BANGEQ RelationalExpressionNoIn {return new js_not_equal({0},{2});}
 | EqualityExpressionNoIn T_EQEQEQ RelationalExpressionNoIn {return new js_strict_equal({0},{2});}
 | EqualityExpressionNoIn T_BANGEQEQ RelationalExpressionNoIn {return new js_strict_not_equal({0},{2});}

BitwiseANDExpressionNoIn: EqualityExpressionNoIn {return {0};}
 | BitwiseANDExpressionNoIn T_AMP EqualityExpressionNoIn {return new js_bit_and({0},{2});}

BitwiseXORExpressionNoIn: BitwiseANDExpressionNoIn {return {0};}
 | BitwiseXORExpressionNoIn T_HAT BitwiseANDExpressionNoIn {return new js_bit_xor({0},{2});}

BitwiseORExpressionNoIn: BitwiseXORExpressionNoIn {return {0};}
 | BitwiseORExpressionNoIn T_PIPE BitwiseXORExpressionNoIn {return new js_bit_or({0},{2});}

LogicalANDExpressionNoIn: BitwiseORExpressionNoIn {return {0};}
 | LogicalANDExpressionNoIn T_AMPAMP BitwiseORExpressionNoIn {return new js_and({0},{2});}

LogicalORExpressionNoIn: LogicalANDExpressionNoIn {return {0};}
 | LogicalORExpressionNoIn T_PIPEPIPE LogicalANDExpressionNoIn {return new js_or({0},{2});}

ConditionalExpressionNoIn: LogicalORExpressionNoIn {return {0};}
 | LogicalORExpressionNoIn T_QUESTMARK AssignmentExpressionNoIn T_COLON AssignmentExpressionNoIn {return new js_ternary({0},{2},{4});}

AssignmentExpressionNoIn: ConditionalExpressionNoIn {return {0};}
 | ConditionalExpressionNoIn T_EQUAL AssignmentExpressionNoIn {return new js_assign({0},{2});}
 | ConditionalExpressionNoIn T_ASSIGN AssignmentExpressionNoIn {return new js_compound_assign({0},{2},{1});}

ExpressionNoIn: AssignmentExpressionNoIn {return {0};}
 | ExpressionNoIn T_COMMA AssignmentExpressionNoIn {return new js_comma({0},{2});}

VariableDeclarationListNoIn: VariableDeclarationNoIn { return array({0}); }
                       | VariableDeclarationListNoIn T_COMMA VariableDeclarationNoIn { {0}[]={2}; return {0}; }

VariableDeclarationNoIn: Identifier InitialiserNoIn? { return @array({0},{1});}

InitialiserNoIn: T_EQUAL AssignmentExpressionNoIn { return {1}; }