/* some utility functions */

#ifndef UTILS_H
#define UTILS_H

#include "globals.h"

void printToken(TokenType token, const char *tokenString);

void printTree(struct TreeNode *tree);

struct TreeNode * newStmtNode(StmtKind kind);

struct TreeNode * newExpNode(ExpKind kind);

/* allocate and make a new copy of str */
char * copyString (const char *str);

void token2String(TokenType token,
        const char *tokenString, char **result);

#endif /* ifndef UTILS_H */
