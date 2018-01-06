/* generateParseTree.c: Generation of the dot graph of the syntax tree */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <assert.h>

#include "definition.h"
#include "tiny.yacc.h"

/* global data */
int eogStarted = 0;
pid_t eogPid = 0;

FILE * dotFile = NULL;
char * dotFileName = "graph.dot";
char * svgFileName = "graph.svg";
int globalNodeNumber = 0;

void init();
void finish();
void eogInit();
void eogFinish();
void dotFileInit();
void dotFileFinish();
void generatePicture();
void newDotNode(int parentNodeNumber, const char *label);
void newDotEdge(int num1, int num2);
void pushToDotFile(const char *text);

/* recursive traverse the syntax tree */
void traverseNode(nodeType *p, int parentNodeNumber);


/* main entry point of the traverse of the syntax tree */
int traverseTree(nodeType *p);

/* when parse done, this function should be called */
void onExit();

/*********************************************************/

int traverseTree(nodeType *p) {
    init();

    traverseNode(p, -1);

    finish();

    return 0;
}

void traverseNode(nodeType *p, int parentNodeNumber) {
    int i;
    const char *s = NULL;     // node text
    char word[20];      // extended node text

    if (!p) {
        return;
    }

    strcpy(word, "???");    // this should never appear
    s = word;
    switch(p->type) {
        case typeCon: 
            sprintf (word, "c(%d)", p->con.value); 
            /* sprintf(buffer, "c(%d)", p->con.value); */
            /* newDotNode(parentNodeNumber, buffer); */
            break;
        case typeId:  
            sprintf (word, "id(%c)", p->id.i + 'A'); 
            /* sprintf(buffer, "id(%c)", p->id.i + 'A'); */
            /* newDotNode(parentNodeNumber, buffer); */
            break;
        case typeOpr:
            switch(p->opr.oper){
                case WHILE:     s = "while";   break;
                case IF:        s = "if";      break;
                case PRINT:     s = "print";   break;
                case ';':       s = "[;]";     break;
                case '=':       s = "[=]";     break;
                case UMINUS:    s = "[_]";     break;
                case '+':       s = "[+]";     break;
                case '-':       s = "[-]";     break;
                case '*':       s = "[*]";     break;
                case '/':       s = "[/]";     break;
                case '<':       s = "[<]";     break;
                case '>':       s = "[>]";     break;
                case GE:        s = "[>=]";    break;
                case LE:        s = "[<=]";    break;
                case NE:        s = "[!=]";    break;
                case EQ:        s = "[==]";    break;
            }
            /* newDotNode(parentNodeNumber, s); */
            break;
    }
    newDotNode(parentNodeNumber, s);

    /* node is leaf */
    if (p->type == typeCon || p->type == typeId || p->opr.nops == 0) {
        return;
    }

    /* node has children */
    int currentNumber = globalNodeNumber - 1;
    for (i = 0; i < p->opr.nops; ++i) {
        traverseNode(p->opr.op[i], currentNumber);
    }


}

void init() {
    dotFileInit();
    eogInit();
}

void finish() {
    dotFileFinish();
    generatePicture();
}

void dotFileInit() {
    const char *DOT_FILE_HEAD = "graph g {\n "
                                        "\tnode [shape=plaintext];\n";
    dotFile = fopen(dotFileName, "w");
    if (!dotFile) {
        perror("Failed to open dot file: ");
        exit(1);
    }

    /* dot file header */
    pushToDotFile(DOT_FILE_HEAD);
}

void dotFileFinish() {
    const char*DOT_FILE_TAIL = "}";

    pushToDotFile(DOT_FILE_TAIL);

    if (dotFile) {
        fclose(dotFile);
        dotFile = NULL;
    }
}

void newDotNode(int parentNodeNumber, const char *label) {
    char buffer[64];

    if (parentNodeNumber < -1) {
        return;
    }

    sprintf(buffer, "\nn%d [label=\"%s\"];\n", globalNodeNumber++, label);
    pushToDotFile(buffer);

    if (parentNodeNumber < 0) {
        return;
    }
    newDotEdge(parentNodeNumber, globalNodeNumber-1);
}

void newDotEdge(int num1, int num2) {
    char buffer[64];
    if (num1 < 0 || num2 < 0) {
        fprintf(stderr, "%s\n", "attempt to build invalid edge");
        return;
    }

    sprintf(buffer, "\tn%d -- n%d;\n", num1, num2);
    pushToDotFile(buffer);
}

void pushToDotFile(const char *text) {
    assert(dotFile);
    fprintf(dotFile, "%s", text);
}

void eogInit() {
    if (eogStarted) {
        return;
    }

    eogStarted = 1;
    eogPid = fork();
    if (eogPid == 0) {
        char * exec_str[] = {"eog", svgFileName, NULL};
        const char * cmd = "/usr/bin/eog";
        if (execv(cmd, exec_str) < 0) {
            perror("error on exec eog: ");
            exit(1);
        }
        puts("eog exit");
    } else if (eogPid < 0) {
        perror("error on fork: ");
        exit(1);
    }
}

void eogFinish() {
    assert(eogPid);
    printf("%s", "\nkilling eog...");
    if (kill(eogPid, SIGKILL) != 0) {
        perror("failed to kill eog: ");
    }
    
    puts("killed");
}

void generatePicture() {
    pid_t pid = fork();
    if (pid == 0) {
        char * exec_str[] = {"dot", "-T", "svg","-o", svgFileName, dotFileName, NULL};
        const char * cmd = "/usr/bin/dot";
        if (execv(cmd, exec_str) < 0) {
            perror("error on exec dot: ");
            exit(1);
        }
        puts("svg file generated");
    } else if (pid < 0) {
        perror("error on fork: ");
        exit(1);
    }
}

void onExit() {
    printf("%s", "parse done, cleaning...");

    eogFinish();

    printf("%s", "cleaing done\nexit\n");
}
