%{
#include <stdlib.h>
void yyerror(char *);
#include "calculator.yacc.h"
%}

%%

    /* variables */
[a-z] {
    yylval = *yytext - 'a';
    return VARIABLE;
}

    /* integers */
[0-9]+ {
    yylval = atoi(yytext);
    return INTEGER;
}

    /* opeators */
[-+()=/*\n] {
    return *yytext;
}

    /* ignore whitespace */
[ \t] ;

    /* anything else is an error */
. {
    yyerror("invalid character");
}

%%

int yywrap(void) {
    return 1;
}
