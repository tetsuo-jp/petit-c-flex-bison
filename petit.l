%option noyywrap

%{
#include "y.tab.h"
#include "../node.h"
#include "../program.h"
%}

SP	[ \t]+
NL	(\r\n|\r|\n)

%%

0					{ yylval.node = create_zero_node(); return ZERO; }
[A-Z]				{ yylval.node = create_var_node(yytext[0]); return VAR; }
;					{ return SEMICOLON; }
:=					{ return ASSIGN; }
suc{SP}				{ return SUC; }
for{SP}				{ return FOR; }
{SP}times{SP}do{SP}	{ return TIMES_DO; }
{SP}end				{ return END; }

{NL}				{ if (is_interactive) return NL; else line++; }
{SP}				{ ; }
.					{ /* ignored output. */; }

%%
