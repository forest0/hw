/* scanner implementation for TINY compiler */

#include "scan.h"
#include "utils.h"

/* states in scanner DFA */
typedef enum {
    START,
    INASSIGN,
    INCOMMENT,
    INNUM,
    INID,
    DONE
} StateType;

/* lexeme of identifier or reserved word */
char tokenString[MAX_TOKEN_LENGTH+1];

/* the length of input buffer for source code line */
#define BUFFER_LENGTH 256

static char lineBuffer[BUFFER_LENGTH];  // hold the current line
static int linePosition = 0;            // current position in lineBuffer
static int bufferSize = 0;              // current size of buffer string
static int EOF_flag = FALSE;

/* getNextChar fetches the next character
 * from lineBuffer, reading in a new line if lineBuffer is exhausted */
static int getNextChar(void) {
    if (!(linePosition < bufferSize)) {
        ++lineNumber;
        if (fgets(lineBuffer, BUFFER_LENGTH-1, source)) {
            if (echoSource) {
                fprintf(listing, "%4d: %s", lineNumber, lineBuffer);;
            }
            bufferSize = strlen(lineBuffer);
            linePosition = 0;
            return lineBuffer[linePosition++];
        } else {
            EOF_flag = TRUE;
            return EOF;
        }
    } else {
        return lineBuffer[linePosition++];
    }
}

/* backtracks one character in lineBuffer */
static void ungetNextChar(void) {
    if (!EOF_flag) {
        --linePosition;
    }
}

/* lookup table of reserved words */
static struct {
    char *str;
    TokenType token;
} reservedWords[MAX_RESERVED] = {
    {"if"     , IF},
    {"then"   , THEN},
    {"else"   , ELSE},
    {"end"    , END},
    {"repeat" , REPEAT},
    {"until"  , UNTIL},
    {"read"   , READ},
    {"write"  , WRITE}
};

/* lookup an identifier to see if it is a serverd word */
static TokenType reservedLookup(char *s) {
    int i;
    for (i = 0; i < MAX_RESERVED; ++i) {
        if (!strcmp(s, reservedWords[i].str)) {
            return reservedWords[i].token;
        }
    }
    return ID;
}

/* primary function of the scanner
 * getNextToken returns the next token in source file */
TokenType getNextToken(void) {
    /* index for storing into tokenString */
    int tokenStringIndex = 0;
    /* holds current token to be renturned */
    TokenType currentToken;
    /* current state, which always begins at START */
    StateType state = START;
    /* flag to indicate current character needs to be saved to tokenString */
    int needToSave = TRUE;

    while (state != DONE) {
        int c = getNextChar();
        needToSave = TRUE;
        switch (state) {
            case START:
                if (isdigit(c)) {
                    state = INNUM;
                } else if (isalpha(c)) {
                    state = INID;
                } else if (c == ':') {
                    state = INASSIGN;
                } else if ((c == ' ') || (c == '\t') || (c == '\n')) {
                    needToSave = FALSE;
                } else if ( c == '{' ) {
                    needToSave = FALSE;
                    state = INCOMMENT;
                } else {
                    state = DONE;
                    switch (c) {
                        case EOF:
                            needToSave = FALSE;
                            currentToken = ENDFILE;
                            break;
                        case '=':
                            currentToken = EQ;
                            break;
                        case '<':
                            currentToken = LT;
                            break;
                        case '+':
                            currentToken = PLUS;
                            break;
                        case '-':
                            currentToken = MINUS;
                            break;
                        case '*':
                            currentToken = TIMES;
                            break;
                        case '/':
                            currentToken = DIVIDE;
                            break;
                        case '(':
                            currentToken = LPAREN;
                            break;
                        case ')':
                            currentToken = RPAREN;
                            break;
                        case ';':
                            currentToken = SEMI;
                            break;
                        default:
                            currentToken = ERROR;
                            break;
                    }
                }
                break;
            case INCOMMENT:
                needToSave = FALSE;
                if (c == EOF) {
                    state = DONE;
                    currentToken = ENDFILE;
                } else if (c == '}') {
                    state = START;
                }
                break;
            case INASSIGN:
                state = DONE;
                if (c == '=') {
                    currentToken = ASSIGN;
                } else {
                    /* backup in the input */
                    ungetNextChar();
                    needToSave = FALSE;
                    currentToken = ERROR;
                }
                break;
            case INNUM:
                if (!isdigit(c)) {
                    /* backup in the input */
                    ungetNextChar();
                    needToSave = FALSE;
                    state = DONE;
                    currentToken = NUM;
                }
                break;
            case INID:
                if (!isalpha(c)) {
                    /* backup in the input */
                    ungetNextChar();
                    needToSave = FALSE;
                    state = DONE;
                    currentToken = ID;
                }
                break;
            case DONE:
            default: // should never happen
                fprintf(listing, "scanner bug: state = %d\n", state);
                state = DONE;
                currentToken = ERROR;
                break;
        }
        if ((needToSave) && (tokenStringIndex <= MAX_TOKEN_LENGTH)) {
            tokenString[tokenStringIndex++] = (char) c;
        } 
        if (state == DONE) {
            tokenString[tokenStringIndex] = '\0';
            if (currentToken == ID) {
                currentToken = reservedLookup(tokenString);
            }
        }
    }
    if (traceScan) {
        /* fprintf(listing, "\t%d: ", lineNumber); */
        printToken(currentToken, tokenString);
    }
    return currentToken;
}
