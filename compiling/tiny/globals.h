/* global types and vars for TINY compiler */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MAX_RESERVED 8

typedef enum {
    /* book-keeping tokens */
    ENDFILE, ERROR,
    /* reserved words */
    IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
    /* multicharacter tokens */
    ID, NUM,
    /* special symbols */
    ASSIGN, EQ, LT, PLUS, MINUS, TIMES, DIVIDE, LPAREN, RPAREN, SEMI
} TokenType;


extern FILE* source;    // source code text file
extern FILE* listing;   // listing output text file

extern int lineNumber;      // source line number

typedef enum {
    StmtK,
    ExpK
} NodeKind;

typedef enum {
    IfK,
    RepeatK,
    AssignK,
    ReadK,
    WriteK
} StmtKind;

typedef enum {
    OpK,
    ConstK,
    IdK
} ExpKind;

#define MAX_CHILDREN 3

/* syntax tree node */

typedef struct TreeNode {
    struct TreeNode * child[MAX_CHILDREN];
    struct TreeNode * sibling;
    int lineno;
    NodeKind nodeKind;
    union {
        StmtKind stmt;
        ExpKind exp;
    } kind;
    union {
        TokenType op;
        int val;
        char * name;
    } attr;

} treeNode;

/* flags for tracing */

/* echoSource = TRUE will echo source program
 * with line number during parsing */
extern int echoSource;

/* traceScan = TRUE will print token info */
extern int traceScan;

/* traceParse = TRUE will print the syntax tree */
extern int traceParse;

/* generateDotFile = TRUE will generate the dot file which
 *      descripe the syntax tree with Graphviz in parsing */
extern int generateDotFile;

/* stopWhenError = TRUE will stop further passes when error occurs */
extern int stopWhenError;

#endif /* ifndef GLOBALS_H */
