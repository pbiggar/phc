%x text
%%

/\*.*?\*/	/s	mlcomment	ignore
//[^\x0A\x0D]*		slcomment	ignore
[\x0A\x0D]		newline		ignore
\s+			whitespace	ignore

\?\>			T_SCRIPT_END {$state='text';}
\bfunction\b		T_FUNCTION
\bvar\b			T_VAR
\bdo\b			T_DO
\bwhile\b		T_WHILE
\bfor\b			T_FOR
\bin\b			T_IN
\bwith\b		T_WITH
\bswitch\b		T_SWITCH
\bcase\b		T_CASE
\bdefault\b		T_DEFAULT
\bthrow\b		T_THROW
\btry\b			T_TRY
\bcatch\b		T_CATCH
\bfinally\b		T_FINALLY
\bcontinue\b		T_CONTINUE
\bbreak\b		T_BREAK
\breturn\b		T_RETURN
\bnew\b			T_NEW
\bdelete\b		T_DELETE
\bvoid\b		T_VOID
\btypeof\b		T_TYPEOF
\binstanceof\b		T_INSTANCEOF
\bnull\b		T_NULL
\btrue\b		T_TRUE
\bfalse\b		T_FALSE
\bif\b			T_IF
\bthen\b		T_THEN
\belse\b		T_ELSE
\bthis\b		T_THIS
\(			T_LEFTPARENS
\)			T_RIGHTPARENS
\{			T_LEFTBRACE
\}			T_RIGHTBRACE
\[			T_LEFTBRACKET
\]			T_RIGHTBRACKET
\.			T_DOT
,			T_COMMA
;			T_SEMICOLON
:			T_COLON
(?:[*/%+&^|-]|>>>?|<<)=	T_ASSIGN
===			T_EQEQEQ
==			T_EQEQ
=			T_EQUAL
\+\+			T_PLUSPLUS
\+			T_PLUS
--			T_MINUSMINUS
-			T_MINUS
[~]			T_TILDE
!==			T_BANGEQEQ
!=			T_BANGEQ
[!]			T_BANG
[*]			T_STAR
[/]			T_SLASH
[%]			T_PERCENT
>>>			T_GTGTGT
<<			T_LTLT
>>			T_GTGT
<=			T_LTEQ
>=			T_GTEQ
<			T_LT
>			T_GT
[\^]			T_HAT
[&][&]			T_AMPAMP
[&]			T_AMP
[|][|]			T_PIPEPIPE
[|]			T_PIPE
[?]			T_QUESTMARK
[\$_a-zA-Z](?:\w|\$|_)*:	T_LABEL
[\$_a-zA-Z](?:\w|\$|_)*	T_WORD

[0][xX][0-9a-zA-Z]+	T_HEXA { $text = hexdec($text); }
(?:(?:[0]|[1-9]\d*)\.\d*|\.\d+|(?:[0]|[1-9]\d*))(?:[eE][-+]?\d+)?	T_DECIMAL { $text = $text-0; }
'(?:[^'\\]|\\.)*'|"(?:[^"\\]|\\.)*"	T_STRING

#-- (?i:/[^/]*/[a-z]*)	regexp

<text>{
\<\?(?:js)?		T_SCRIPT_BEGIN {$state='INITIAL';}
\<\?=			T_SCRIPT_BEGIN_ECHO {$state='INITIAL';}
(?:[^<]|<[^?])*		/s	T_TEXT
}
