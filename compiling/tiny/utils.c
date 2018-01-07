/* utility functions implementation */

#include "globals.h"
#include "utils.h"

/* should only be used for debug purpose */
void token2String(TokenType token,
        const char *tokenString, char **result) {

    char buffer[128];
    switch (token) {
        case IF:
            *result = copyString("IF");
        case THEN:
            *result = copyString("THEN");
        case ELSE:
            *result = copyString("ELSE");
        case END:
            *result = copyString("END");
        case REPEAT:
            *result = copyString("REPEAT");
        case UNTIL:
            *result = copyString("UNTIL");
        case READ:
            *result = copyString("READ");
        case WRITE:
            *result = copyString("WRITE");
            break;
        case ASSIGN:
            *result = copyString(":=");
            break;
        case LT:
            *result = copyString("<");
            break;
        case EQ:
            *result = copyString("=");
            break;
        case LPAREN:
            *result = copyString("(");
            break;
        case RPAREN:
            *result = copyString(")");
            break;
        case SEMI:
            *result = copyString(";");
            break;
        case PLUS:
            *result = copyString("+");
            break;
        case MINUS:
            *result = copyString("-");
            break;
        case TIMES:
            *result = copyString("*");
            break;
        case DIVIDE:
            *result = copyString("/");
            break;
        case ENDFILE:
            *result = copyString("EOF");
            break;
        case NUM:
            sprintf(buffer, "NUM(%s)", tokenString);
            *result = copyString(buffer);
            break;
        case ID:
            sprintf(buffer, "ID(%s)", tokenString);
            *result = copyString(buffer);
            break;
        case ERROR:
            *result = copyString(tokenString);
            break;
        default: // should never appear
            sprintf(buffer, "unknown token: %d\n", token);
            *result = copyString(buffer);
            break;
    }
}

void printToken(TokenType token, const char *tokenString) {
    switch (token) {
        case IF:
        case THEN:
        case ELSE:
        case END:
        case REPEAT:
        case UNTIL:
        case READ:
        case WRITE:
            fprintf(listing, "KEYWORD(%s)\n", tokenString);
            break;
        case ASSIGN:
            fprintf(listing, ":=\n");
            break;
        case LT:
            fprintf(listing, "<\n");
            break;
        case EQ:
            fprintf(listing, "=\n");
            break;
        case LPAREN:
            fprintf(listing, "(\n");
            break;
        case RPAREN:
            fprintf(listing, ")\n");
            break;
        case SEMI:
            fprintf(listing, ";\n");
            break;
        case PLUS:
            fprintf(listing, "+\n");
            break;
        case MINUS:
            fprintf(listing, "-\n");
            break;
        case TIMES:
            fprintf(listing, "*\n");
            break;
        case DIVIDE:
            fprintf(listing, "/\n");
            break;
        case ENDFILE:
            fprintf(listing, "EOF\n");
            break;
        case NUM:
            fprintf(listing, "NUM(%s)\n", tokenString);
            break;
        case ID:
            fprintf(listing, "ID(%s)\n", tokenString);
            break;
        case ERROR:
            fprintf(listing, "%s\n", tokenString);
            break;
        default: // should never appear
            fprintf(listing, "unknown token: %d\n", token);
            break;
    }
}

static int indentNumber = 0;

#define STEP_SIZE 4

#define INDENT indentNumber+=STEP_SIZE
#define UNINDENT indentNumber-=STEP_SIZE

/* indent by printing spaces */
static void printSpaces(void) {
    int i;
    for (i = 0; i < indentNumber; ++i) {
        fprintf(listing, " ");
    }
}

void printTree(struct TreeNode *tree) {
    int i;
    char *str;
    INDENT;
    while (tree) {
        printSpaces();
        if (tree->nodeKind == StmtK) {
            switch (tree->kind.stmt) {
                case IfK:
                    fprintf(listing, "IF\n");
                    break;
                case RepeatK:
                    fprintf(listing, "REPEAT\n");
                    break;
                case AssignK:
                    fprintf(listing, "ASSIGN(%s)\n", tree->attr.name);
                    break;
                case ReadK:
                    fprintf(listing, "READ(%s)\n", tree->attr.name);
                    break;
                case WriteK:
                    fprintf(listing, "WRITE\n");
                    break;
                default:
                    fprintf(listing, "unknown StmtNode kind\n");
                    break;
            }
        } else if (tree->nodeKind == ExpK) {
            switch (tree->kind.exp) {
                case OpK:
                    token2String(tree->attr.op, "\0", &str);
                    fprintf(listing, "OP(%s)\n", str);
                    break;
                case ConstK:
                    fprintf(listing, "CONST(%d)\n", tree->attr.val);
                    break;
                case IdK:
                    fprintf(listing, "ID(%s)\n", tree->attr.name);
                    break;
                default:
                    fprintf(listing, "unknown ExpNode kind\n");
                    break;
            }
        } else {
            fprintf(listing, "unknown node kind\n");
        }

        for (i = 0; i < MAX_CHILDREN; ++i) {
            printTree(tree->child[i]);
        }
        tree = tree->sibling;
    }
    UNINDENT;
}

struct TreeNode * newStmtNode(StmtKind kind) {
    struct TreeNode * t = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    int i;
    if (!t) {
        fprintf(stderr, "out of memory error at line %d\n", lineNumber);
    } else {
        for (i = 0; i < MAX_CHILDREN; ++i) {
            t->child[i] = NULL;
        }
        t->sibling = NULL;
        t->nodeKind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineNumber;
    }
    return t;
}

struct TreeNode * newExpNode(ExpKind kind) {
    struct TreeNode * t = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    int i;
    if (!t) {
        fprintf(stderr, "out of memory error at line %d\n", lineNumber);
    } else {
        for (i = 0; i < MAX_CHILDREN; ++i) {
            t->child[i] = NULL;
        }
        t->sibling = NULL;
        t->nodeKind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineNumber;
    }
    return t;
}

char * copyString(const char *str) {
    int strLength;
    char * newStr;

    if (!str) {
        return NULL;
    }

    strLength = strlen(str) + 1;
    newStr = malloc(strLength);
    if (!newStr) {
        fprintf(stderr, "out of memory error at line %d\n", lineNumber);
    } else {
        strcpy(newStr, str);
    }
    
    return newStr;
}

