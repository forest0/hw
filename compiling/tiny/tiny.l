%{
#include <stdlib.h>
#include "definition.h"
#include "tiny.yacc.h"
void yyerror(char *);
%}

%%

    /* variables */
[a-z] {
    yylval.sIndex = *yytext - 'a';
    return VARIABLE;
}

    /* integers */
0 {
    yylval.iValue = atoi(yytext);
    return INTEGER;
}
[1-9][0-9]* {
    yylval.iValue = atoi(yytext);
    return INTEGER;
}

    /* opeators */
[-()<>=+*/;{}.] {
    return *yytext;
}

">="    return GE;
"<="    return LE;
"=="    return EQ;
"!="    return NE;
"while" return WHILE;
"if"    return IF;
"else"  return ELSE;
"print" return PRINT;

    /* ignore whitespace */
[ \t\n]+ ;

    /* anything else is an error */
. {
    yyerror("invalid character");
}

%%

int yywrap(void) {
    return 1;
}
