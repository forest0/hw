/* the parser implementation for TINY compiler */

#include "globals.h"
#include "parse.h"
#include "utils.h"
#include "scan.h"

static TokenType token;     // holds current token

/* recursive descent parseing */
static struct TreeNode * stmt_sequence(void);
static struct TreeNode * statement(void);
static struct TreeNode * if_stmt(void);
static struct TreeNode * repeat_stmt(void);
static struct TreeNode * assign_stmt(void);
static struct TreeNode * read_stmt(void);
static struct TreeNode * write_stmt(void);
static struct TreeNode * exp(void);
static struct TreeNode * simple_exp(void);
static struct TreeNode * term(void);
static struct TreeNode * factor(void);

static void syntaxError(const char *message) {
    fprintf(listing, "\n>>> Syntax error at line %d: %s",
            lineNumber, message);
    stopWhenError = TRUE;
}

static void match(TokenType expected) {
    if (token == expected) {
        token = getNextToken();
    } else {
        syntaxError("unexpected token -> ");
        printToken(token, tokenString);
    }
}

struct TreeNode * stmt_sequence(void) {
    struct TreeNode * t = statement();
    struct TreeNode * p = t;
    while ((token != ENDFILE) && (token != END) &&
            (token != ELSE) && (token != UNTIL)) {
        struct TreeNode * q;
        match(SEMI);
        q = statement();
        if (q) {
            if (!t) {
                t = p = q;
            } else {
                p->sibling = q;
                p = q;
            }
        }
    }
    return t;
}

struct TreeNode * statement(void) {
    struct TreeNode * t = NULL;
    switch (token) {
        case IF:
            t = if_stmt();
            break;
        case REPEAT:
            t = repeat_stmt();
            break;
        case ID:
            t = assign_stmt();
            break;
        case READ:
            t = read_stmt();
            break;
        case WRITE:
            t = write_stmt();
            break;
        default:
            syntaxError("unexpected token -> ");
            printToken(token, tokenString);
            token = getNextToken();
            break;
    }
    return t;
}

struct TreeNode * if_stmt(void) {
    struct TreeNode * t = newStmtNode(IfK);

    match(IF);
    if (t) {
        t->child[0] = exp();
    }

    match(THEN);
    if (t) {
        t->child[1] = stmt_sequence();
    }

    if (token == ELSE) {
        match(ELSE);
        if (t) {
            t->child[2] = stmt_sequence();
        }
    }

    match(END);

    return t;
}

struct TreeNode * repeat_stmt(void) {
    struct TreeNode * t = newStmtNode(RepeatK);

    match(REPEAT);

    if (t) {
        t->child[0] = stmt_sequence();
    }

    match(UNTIL);

    if (t) {
        t->child[1] = exp();
    }

    return t;
}

struct TreeNode * assign_stmt(void) {
    struct TreeNode * t = newStmtNode(AssignK);

    if ((t) && (token == ID)) {
        t->attr.name = copyString(tokenString);
    }

    match(ID);
    match(ASSIGN);

    if (t) {
        t->child[0] = exp();
    }

    return t;
}

struct TreeNode * read_stmt(void) {
    struct TreeNode * t = newStmtNode(ReadK);

    match(READ);

    if ((t) && (token == ID)) {
        t->attr.name = copyString(tokenString);
    }

    match(ID);

    return t;
}

struct TreeNode * write_stmt(void) {
    struct TreeNode *t = newStmtNode(WriteK);

    match(WRITE);

    if (t) {
        t->child[0] = exp();
    }

    return t;
}

struct TreeNode * exp(void) {
    struct TreeNode * t = simple_exp();
    if ((token == LT) || (token == EQ)) {
        struct TreeNode * p = newExpNode(OpK);
        if (p) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
        }

        match(token);

        if (t) {
            t->child[1] = simple_exp();
        }
    }
    return t;
}

struct TreeNode * simple_exp(void) {
    struct TreeNode * t = term();
    while ((token == PLUS) || (token == MINUS)) {
        struct TreeNode * p = newExpNode(OpK);
        if (p) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            t->child[1] = term();
        }
    }
    return t;
}

struct TreeNode * term(void) {
    struct TreeNode * t = factor();
    while ((token == TIMES) || (token == DIVIDE)) {
        struct TreeNode * p = newExpNode(OpK);
        if (p) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            p->child[1] = factor();
        }
    }
    return t;
}

struct TreeNode * factor(void) {
    struct TreeNode * t = NULL;
    switch (token) {
        case NUM:
            t = newExpNode(ConstK);
            if ((t) && (token == NUM)) {
                t->attr.val = atoi(tokenString);
            }
            match(NUM);
            break;
        case ID:
            t = newExpNode(IdK);
            if ((t) && (token == ID)) {
                t->attr.name = copyString(tokenString);
            }
            match(ID);
            break;
        case LPAREN:
            match(LPAREN);
            t = exp();
            match(RPAREN);
            break;
        default:
            syntaxError("unexpected token -> ");
            printToken(token, tokenString);
            token = getNextToken();
            break;
    }
    return t;
}

/* primary function of parser */
struct TreeNode * parse(void) {
    struct TreeNode * t;
    token = getNextToken();
    t = stmt_sequence();
    if (token != ENDFILE) {
        syntaxError("code ends before file\n");
    }
    return t;
}
