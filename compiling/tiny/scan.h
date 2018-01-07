/* scanner for TINY compiler */

#ifndef SCAN_H
#define SCAN_H

#include "globals.h"

#define MAX_TOKEN_LENGTH 40

/* tokenString stores the lexeme of the token */
extern char tokenString[MAX_TOKEN_LENGTH+1];

/* returns the next token in the source file */
TokenType getNextToken(void);

#endif /* ifndef SCAN_H */
