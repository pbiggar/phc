%%
% Authors:
%   Isil Dillig    <isil@stanford.edu>
%   Thomas Dillig  <tdillig@stanford.edu>
%
% Copyright (c) 2006,
%   The Board of Trustees of The Leland Stanford Junior University
% All rights reserved.
%
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:
% 
% 1. Redistributions of source code must retain the above copyright notice,
% this list of conditions and the following disclaimer.
% 
% 2. Redistributions in binary form must reproduce the above copyright notice,
% this list of conditions and the following disclaimer in the documentation
% and/or other materials provided with the distribution.
% 
% 3. The names of the contributors may not be used to endorse or promote
% products derived from this software without specific prior written
% permission.
% 
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
% AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
% IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
% ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
% LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
% CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
% SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
% INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
% CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
% ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
% POSSIBILITY OF SUCH DAMAGE.
%%

#bool_g(true, T), +null_sum("__ctype_b_loc")->side_effect_edge(root{glob{"__ctype_b_char_ptr"}} ,root{glob{"__ctype_b_array"}} ,T ).
#bool_g(true, T), +null_sum("__ctype_tolower_loc")->side_effect_edge(root{glob{"__ctype_tolower_ptr"}} ,root{glob{"__ctype_tolower_array"}} ,T ).
#bool_g(true, T), +null_sum("__ctype_toupper_loc")->side_effect_edge(root{glob{"__ctype_toupper_ptr"}} ,root{glob{"__ctype_toupper_array"}} ,T ).
#bool_g(true, T), +null_sum("__inner_strtox")->side_effect_edge(drf{root{arg{1}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("__inner_strtox")->deref_edge([deref_location{"__inner_strtox",30,"stdlib.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("__inner_strtox")->deref_edge([deref_location{"__inner_strtox",29,"stdlib.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("__inner_use_string")->deref_edge([deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fgets")->null_edge(drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("fgets")->deref_edge([deref_location{"fgets",39,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fread")->deref_edge([deref_location{"fread",72,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fwrite")->deref_edge([deref_location{"fwrite",102,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("gets")->deref_edge([deref_location{"gets",115,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memccpy")->side_effect_edge(drf{root{arg{0}}} ,drf{drf{root{arg{1}}}} ,T ).
#bool_g(true, T), +null_sum("memccpy")->deref_edge([deref_location{"memccpy",16,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memccpy")->deref_edge([deref_location{"memccpy",16,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memchr")->deref_edge([deref_location{"memchr",25,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memcmp")->deref_edge([deref_location{"memcmp",33,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memcmp")->deref_edge([deref_location{"memcmp",32,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memcpy")->side_effect_edge(drf{root{arg{0}}} ,drf{drf{root{arg{1}}}} ,T ).
#bool_g(true, T), +null_sum("memcpy")->deref_edge([deref_location{"memcpy",39,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memcpy")->deref_edge([deref_location{"memcpy",39,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memset")->deref_edge([deref_location{"memset",50,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcat")->null_edge(drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strcat")->deref_edge([deref_location{"strcat",58,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcat")->deref_edge([deref_location{"strcat",57,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strchr")->deref_edge([deref_location{"strchr",65,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcmp")->deref_edge([deref_location{"strcmp",74,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcmp")->deref_edge([deref_location{"strcmp",73,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcpy")->null_edge(drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strcpy")->deref_edge([deref_location{"strcpy",87,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcpy")->deref_edge([deref_location{"strcpy",87,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcspn")->deref_edge([deref_location{"strcspn",95,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcspn")->deref_edge([deref_location{"strcspn",96,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strdup")->deref_edge([deref_location{"strdup",106,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strerror_r")->deref_edge([deref_location{"strerror_r",122,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strlen")->deref_edge([deref_location{"strlen",130,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strncat")->null_edge(drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strncat")->deref_edge([deref_location{"strncat",136,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strncat")->deref_edge([deref_location{"strncat",137,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strncpy")->side_effect_edge(drf{root{arg{0}}} ,drf{root{temp{"ciltmp","uninit_char"}}} ,T ).
#bool_g(true, T), +null_sum("strncpy")->deref_edge([deref_location{"strncpy",151,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strncpy")->deref_edge([deref_location{"strncpy",152,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtok_r")->side_effect_edge(drf{root{arg{2}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtok_r")->deref_edge([deref_location{"strtok_r",184,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtok_r")->deref_edge([deref_location{"strtok_r",183,"string.c"}] ,root{arg{2}} ,T ,T ,true ).






#bool_g(true, T), +null_sum("a64l")->deref_edge([deref_location{"__inner_use_string",47,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("atof")->deref_edge([deref_location{"__inner_use_string",56,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("atoi")->deref_edge([deref_location{"__inner_use_string",61,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("atol")->deref_edge([deref_location{"__inner_use_string",66,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("atoll")->deref_edge([deref_location{"__inner_use_string",71,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fdopen")->deref_edge([deref_location{"__inner_use_string",27,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fopen")->deref_edge([deref_location{"__inner_use_string",49,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fopen")->deref_edge([deref_location{"__inner_use_string",50,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fprintf")->deref_edge([deref_location{"__inner_use_string",56,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fputs")->deref_edge([deref_location{"__inner_use_string",64,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("freopen")->deref_edge([deref_location{"__inner_use_string",79,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("freopen")->deref_edge([deref_location{"__inner_use_string",80,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("fscanf")->deref_edge([deref_location{"__inner_use_string",86,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("getenv")->deref_edge([deref_location{"__inner_use_string",86,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memmove")->side_effect_edge(drf{root{arg{0}}} ,drf{drf{root{arg{1}}}} ,T ).
#bool_g(true, T), +null_sum("memmove")->deref_edge([deref_location{"memcpy",45,"string.c"},deref_location{"memcpy",39,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("memmove")->deref_edge([deref_location{"memcpy",45,"string.c"},deref_location{"memcpy",39,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("perror")->deref_edge([deref_location{"__inner_use_string",123,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("popen")->deref_edge([deref_location{"__inner_use_string",128,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("popen")->deref_edge([deref_location{"__inner_use_string",129,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("printf")->deref_edge([deref_location{"__inner_use_string",135,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("putenv")->deref_edge([deref_location{"__inner_use_string",119,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("puts")->deref_edge([deref_location{"__inner_use_string",146,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("remove")->deref_edge([deref_location{"__inner_use_string",152,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("rename")->deref_edge([deref_location{"__inner_use_string",158,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("rename")->deref_edge([deref_location{"__inner_use_string",159,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("scanf")->deref_edge([deref_location{"__inner_use_string",167,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("setenv")->deref_edge([deref_location{"__inner_use_string",133,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("setenv")->deref_edge([deref_location{"__inner_use_string",134,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("snprintf")->null_edge(drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("snprintf")->deref_edge([deref_location{"snprintf",187,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("snprintf")->deref_edge([deref_location{"__inner_use_string",186,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{2}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("sprintf")->deref_edge([deref_location{"sprintf",196,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("sprintf")->deref_edge([deref_location{"__inner_use_string",194,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("sscanf")->deref_edge([deref_location{"__inner_use_string",202,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("sscanf")->deref_edge([deref_location{"__inner_use_string",203,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcasecmp")->deref_edge([deref_location{"strcmp",209,"string.c"},deref_location{"strcmp",73,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcasecmp")->deref_edge([deref_location{"strcmp",209,"string.c"},deref_location{"strcmp",74,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcoll")->deref_edge([deref_location{"strcmp",81,"string.c"},deref_location{"strcmp",73,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strcoll")->deref_edge([deref_location{"strcmp",81,"string.c"},deref_location{"strcmp",74,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strncmp")->deref_edge([deref_location{"strcmp",144,"string.c"},deref_location{"strcmp",73,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strncmp")->deref_edge([deref_location{"strcmp",144,"string.c"},deref_location{"strcmp",74,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strpbrk")->deref_edge([deref_location{"strchr",160,"string.c"},deref_location{"strchr",65,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strpbrk")->deref_edge([deref_location{"strpbrk",159,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strrchr")->deref_edge([deref_location{"strchr",165,"string.c"},deref_location{"strchr",65,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strspn")->deref_edge([deref_location{"strcspn",170,"string.c"},deref_location{"strcspn",95,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strspn")->deref_edge([deref_location{"strcspn",170,"string.c"},deref_location{"strcspn",96,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtod")->side_effect_edge(drf{root{arg{1}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtod")->deref_edge([deref_location{"__inner_strtox",146,"stdlib.c"},deref_location{"__inner_strtox",29,"stdlib.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtod")->deref_edge([deref_location{"__inner_strtox",146,"stdlib.c"},deref_location{"__inner_strtox",30,"stdlib.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtof")->side_effect_edge(drf{root{arg{1}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtof")->deref_edge([deref_location{"__inner_strtox",152,"stdlib.c"},deref_location{"__inner_strtox",29,"stdlib.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtof")->deref_edge([deref_location{"__inner_strtox",152,"stdlib.c"},deref_location{"__inner_strtox",30,"stdlib.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtok")->side_effect_edge(root{glob{"__strtok_last"}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtok")->deref_edge([deref_location{"strtok_r",194,"string.c"},deref_location{"strtok_r",184,"string.c"}] ,root{arg{1}} ,T ,T ,true ).

#bool_g(true, T), +null_sum("strtol")->side_effect_edge(drf{root{arg{1}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtol")->deref_edge([deref_location{"__inner_strtox",158,"stdlib.c"},deref_location{"__inner_strtox",29,"stdlib.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtol")->deref_edge([deref_location{"__inner_strtox",158,"stdlib.c"},deref_location{"__inner_strtox",30,"stdlib.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtold")->side_effect_edge(drf{root{arg{1}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtold")->deref_edge([deref_location{"__inner_strtox",164,"stdlib.c"},deref_location{"__inner_strtox",29,"stdlib.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtold")->deref_edge([deref_location{"__inner_strtox",164,"stdlib.c"},deref_location{"__inner_strtox",30,"stdlib.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtoll")->side_effect_edge(drf{root{arg{1}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtoll")->deref_edge([deref_location{"__inner_strtox",170,"stdlib.c"},deref_location{"__inner_strtox",29,"stdlib.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtoll")->deref_edge([deref_location{"__inner_strtox",170,"stdlib.c"},deref_location{"__inner_strtox",30,"stdlib.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtoul")->side_effect_edge(drf{root{arg{1}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtoul")->deref_edge([deref_location{"__inner_strtox",176,"stdlib.c"},deref_location{"__inner_strtox",29,"stdlib.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtoul")->deref_edge([deref_location{"__inner_strtox",176,"stdlib.c"},deref_location{"__inner_strtox",30,"stdlib.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtoull")->side_effect_edge(drf{root{arg{1}}} ,drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strtoull")->deref_edge([deref_location{"__inner_strtox",182,"stdlib.c"},deref_location{"__inner_strtox",29,"stdlib.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strtoull")->deref_edge([deref_location{"__inner_strtox",182,"stdlib.c"},deref_location{"__inner_strtox",30,"stdlib.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strxfrm")->null_edge(drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("strxfrm")->side_effect_edge(drf{root{arg{0}}} ,drf{root{temp{"ciltmp","uninit_char"}}} ,T ).
#bool_g(true, T), +null_sum("strxfrm")->deref_edge([deref_location{"strxfrm",200,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strxfrm")->deref_edge([deref_location{"strlen",202,"string.c"},deref_location{"strlen",130,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strxfrm")->deref_edge([deref_location{"strncpy",199,"string.c"},deref_location{"strncpy",152,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strxfrm")->deref_edge([deref_location{"strncpy",199,"string.c"},deref_location{"strncpy",151,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("system")->deref_edge([deref_location{"__inner_use_string",188,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("unsetenv")->deref_edge([deref_location{"__inner_use_string",196,"stdlib.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vfprintf")->deref_edge([deref_location{"__inner_use_string",214,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vfscanf")->deref_edge([deref_location{"__inner_use_string",220,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vprintf")->deref_edge([deref_location{"__inner_use_string",226,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vscanf")->deref_edge([deref_location{"__inner_use_string",232,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vsnprintf")->null_edge(drf{root{arg{0}}} ,T ).
#bool_g(true, T), +null_sum("vsnprintf")->deref_edge([deref_location{"vsnprintf",239,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vsnprintf")->deref_edge([deref_location{"__inner_use_string",238,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{2}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vsprintf")->deref_edge([deref_location{"__inner_use_string",246,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vsprintf")->deref_edge([deref_location{"vsprintf",248,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vsscanf")->deref_edge([deref_location{"__inner_use_string",255,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("vsscanf")->deref_edge([deref_location{"__inner_use_string",254,"stdio.c"},deref_location{"__inner_use_string",16,"stdio.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strncasecmp")->deref_edge([deref_location{"strncmp",214,"string.c"},deref_location{"strcmp",144,"string.c"},deref_location{"strcmp",74,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strncasecmp")->deref_edge([deref_location{"strncmp",214,"string.c"},deref_location{"strcmp",144,"string.c"},deref_location{"strcmp",73,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strstr")->deref_edge([deref_location{"strpbrk",175,"string.c"},deref_location{"strpbrk",159,"string.c"}] ,root{arg{1}} ,T ,T ,true ).
#bool_g(true, T), +null_sum("strstr")->deref_edge([deref_location{"strpbrk",175,"string.c"},deref_location{"strchr",160,"string.c"},deref_location{"strchr",65,"string.c"}] ,root{arg{0}} ,T ,T ,true ).
