#include "viz.h"
#include "utils.h"
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>

/* some data to help show graphical syntaxTree */
static FILE * dotFile = NULL;
static const char * dotFileName = "syntaxTree.dot";
static const char * picFileName = "syntaxTree.svg";

static int globalNodeNumber = 0;

/* some helper functions to show grapihcal syntax tree */
static void dot2pic();
static void showPicWithEOG();

static void pushToDotFile(const char *text);
static void newDotNode(int parentNodeNumber,
        const char *label);
static void newDotEdge(int num1, int num2);

static void dotFileInit();
static void dotFileFinish();

static void traverseTree(struct TreeNode *node, int parentNodeNumber);

static void traverseTree(struct TreeNode *node, int parentNodeNumber) {
    int i;
    const char *s = NULL;
    char label[64];
    char *str;


    while (node) {
        s = label;
        if (node->nodeKind == StmtK) {
            switch (node->kind.stmt) {
                case IfK:
                    /* fprintf(listing, "IF\n"); */
                    s = "IF";
                    break;
                case RepeatK:
                    /* fprintf(listing, "REPEAT\n"); */
                    s = "REPEAT";
                    break;
                case AssignK:
                    /* fprintf(listing, "ASSIGN(%s)\n", node->attr.name); */
                    sprintf(label, "ASSIGN(%s)", node->attr.name);
                    break;
                case ReadK:
                    /* fprintf(listing, "READ(%s)\n", node->attr.name); */
                    sprintf(label, "READ(%s)", node->attr.name);
                    break;
                case WriteK:
                    /* fprintf(listing, "WRITE\n"); */
                    s = "WRITE";
                    break;
                default:
                    /* fprintf(stderr, "unknown StmtNode kind\n"); */
                    strcpy(label, "unknown StmtNode kind"); // this should never appear
                    break;
            }
        } else if (node->nodeKind == ExpK) {
            switch (node->kind.exp) {
                case OpK:
                    /* fprintf(listing, "Op "); */
                    /* printToken(node->attr.op, "\0"); */
                    token2String(node->attr.op, "\0", &str);
                    sprintf(label, "OP(%s)", str);
                    break;
                case ConstK:
                    /* fprintf(listing, "Const(%d)\n", node->attr.val); */
                    sprintf(label, "CONST(%d)", node->attr.val);
                    break;
                case IdK:
                    /* fprintf(listing, "Id(%s)\n", node->attr.name); */
                    sprintf(label, "ID(%s)", node->attr.name);
                    break;
                default:
                    /* fprintf(stderr, "unknown ExpNode kind\n"); */
                    strcpy(label, "unknown ExpNode kind"); // this should never appear
                    break;
            }
        } else {
            /* fprintf(stderr, "unknown node kind\n"); */
            strcpy(label, "unknown node kind"); // this should never appear
        }
        newDotNode(parentNodeNumber, s);

        int currentNumber = globalNodeNumber - 1;
        for (i = 0; i < MAX_CHILDREN; ++i) {
            traverseTree(node->child[i], currentNumber);
        }
        node = node->sibling;
    }
}

/* entry for show graphical syntax tree */
void showGraphVizTree(struct TreeNode *tree) {
    dotFileInit();

    globalNodeNumber = 1;
    traverseTree(tree, globalNodeNumber-1);

    dotFileFinish();
    dot2pic();
    showPicWithEOG();
}

static void dotFileInit() {
    const char * DOT_FILE_HEAD = "graph g {\n"
        "\tnode [shape=plaintext];\n"
        "\tn0 [label=\"stmt-sequence\"]\n";
    dotFile = fopen(dotFileName, "w");
    if (!dotFile) {
        perror("failed to open dot file: ");
        exit(1);
    }

    /* dot file header */
    pushToDotFile(DOT_FILE_HEAD);
}

static void dotFileFinish() {
    const char * DOT_FILE_TAIL = "\n}";

    pushToDotFile(DOT_FILE_TAIL);

    if (dotFile) {
        if (fclose(dotFile) != 0) {
            perror("failed to close dot file: ");
        } else {
            dotFile = NULL;
        }
    }
}

static void pushToDotFile(const char *text) {
    if (!generateDotFile) {
        return;
    }
    assert(dotFile);
    fprintf(dotFile, "%s", text);
}

static void showPicWithEOG() {
    pid_t eogPid = fork();
    if (eogPid == 0) {
        char * exec_str[] = {"eog", picFileName, NULL};
        const char *cmd = "/usr/bin/eog";
        if (execv(cmd, exec_str) < 0) {
            perror("error on exec eog: ");
            exit(1);
        }
    } else if (eogPid < 0) {
        perror("error on fork: ");
        exit(1);
    }
}

static void dot2pic() {
    pid_t pid = fork();
    if (pid == 0) {
        char * exec_str[] = {"dot", "-T", "svg","-o", 
            picFileName, dotFileName, NULL};
        const char * cmd = "/usr/bin/dot";
        if (execv(cmd, exec_str) < 0) {
            perror("error on exec dot: ");
            exit(1);
        }
    } else if (pid < 0) {
        perror("error on fork: ");
        exit(1);
    }
}

static void newDotNode(int parentNodeNumber, const char *label) {
    char buffer[64];

    if (parentNodeNumber < -1) {
        return;
    }

    sprintf(buffer, "\nn%d [label=\"%s\"];\n", globalNodeNumber++, label);
    pushToDotFile(buffer);

    newDotEdge(parentNodeNumber, globalNodeNumber-1);
}

static void newDotEdge(int num1, int num2) {
    char buffer[64];
    if (num1 < 0 || num2 < 0) {
        fprintf(stderr, "%s\n", "attempt to build invalid edge");
        return;
    }

    sprintf(buffer, "\tn%d -- n%d;\n", num1, num2);
    pushToDotFile(buffer);
}
