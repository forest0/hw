/**********************************************************************
*   main program for TINY compiler
*   
*   currently contains a scanner(lexical analysis)
*      and a parser(generate syntax tree)
*      
*   reference: 
*       Compiler Construction Principles and Practice
*           by Kenneth C.Louden
**********************************************************************/


#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE

/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE TRUE

#include "utils.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#include "viz.h"
#endif

/* global variables */
int lineNumber = 0;
FILE * source;
FILE * listing;

/**************** tracing flags **********************/

int echoSource = FALSE;

int traceScan  = TRUE;

int traceParse = TRUE;
int generateDotFile = TRUE;
int showGraphViz = TRUE;

/**************** end of tracing flags ***************/

int stopWhenError = TRUE;


int main(int argc, char *argv[]) {
    struct TreeNode *syntaxTree;
    char sourceFileName[64];
    if (argc != 2) {
        fprintf(stderr, "usage: %s <source_file_name>\n", argv[0]);
        exit(1);
    }

    strcpy(sourceFileName, argv[1]);
    if (strchr(sourceFileName, '.') == NULL) {
        strcat(sourceFileName, ".tny");
    }

    source = fopen(sourceFileName, "r");
    if (!source) {
        perror("failed to open source file: ");
        exit(1);
    }

    listing = stdout;
    fprintf(listing, "\n******* TINY compilation: %s *******\n\n", sourceFileName);

#if NO_PARSE
    while (getNextToken() != ENDFILE);
#else
    syntaxTree = parse();

    if (traceParse) {
        fprintf(listing, "\nsyntax tree:\n");
        printTree(syntaxTree);

    }

    if (generateDotFile && showGraphViz) {
        showGraphVizTree(syntaxTree);
    }
#endif

    if (fclose(source) != 0) {
        perror("failed to close source file: ");
    }

    return 0;
}
