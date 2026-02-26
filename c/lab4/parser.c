#include "lexer.c"

// data structures needed for the interpreter
int lineno = 0;   // if this is equal to 0 then we should execute immediately
char* lines[10];  // preallocate enough room for 10 lines
int linenos[10];  
int symboltable[26];
char symboldefined[26];
void line();
void statement();
void expr_list();
void var_list();
void expression();
void term();
void factor();
void relop();

/******************************************************/
/* main driver */
int main()
{
  /* Open the input data file and process its contents */
  if ((in_fp = fopen("front.in", "r")) == NULL) {
    printf("ERROR - cannot open front.in \n");
    printf("%d",(int)('A'-'A'));
  } 
  else
  {
    getChar();
    do
    {
      lex();
      line();
    } while (nextToken != EOF);
  }
}

// lex() MUST be called before this function
void line() {
    if (nextToken == NUMBER) {
        lineno = atoi(lexeme);
        // take whatever is left in the rest of the line and store it for processing later!

        // consume the token by looking at the line number
        // and storing the statement that follows in the right place in our stored program
        // BUT NOT FOR THIS ASSIGNMENT
        // Call lex() to get the next token
        lex();
    }
    statement(); // note that statement MUST have an extra call to lex()
    if (nextToken != CR && nextToken != EOF) {
        printf("Expecting CR, but found: %d instead!\n", nextToken);
    } 

}

// lex() MUST have already been called before here
void statement() {
    switch(nextToken) {
        case PRINT:
            lex();
            expr_list();
            // unconditionally printf("\n");
            break;

        case IF:
            lex();
            expression(); // all expressions have an extra call to lex() because of term()
            relop(); // this always ends with an extra call to lex()
            expression();
            if (nextToken != THEN) {
                printf("error! expecting then found something else");
            }
            lex();
            statement();
            // we never need an extra call to lex() here 
            // because statement() ALWAYS has an extra call to lex()
            break;

        case GOTO:
            lex();
            expression();
            // no extra call to lex to look for the carriage return
            break;

        // keep going with more cases INPUT DOES NOT NEED THE EXTRA CALL TO LEX ... NEITHER DO THE ONES THAT ARE JUST KEYWORDS
        case INPUT:
            lex();
            var_list();
            break;

        case LET:
            lex();
            if (nextToken != VAR) {
                printf("Expecting IDENT but found: %d\n", nextToken);
                exit(1);
            }
            lex();
            if (nextToken != EQUALS_OP) {
                printf("Expecting EQ but found: %d\n", nextToken);
                exit(1);
            }
            lex();
            expression();

            // no extra call to lex() here because expression() will have already called lex() for us when it was looking for +, -, *, or /
            break;
        
        case GOSUB:
            lex();
            expression();

            // NO extra call to lex to look for the carriage return b/c expression() has an extra call to lex()
            break;
            
        case RETURN:
        case CLEAR:
        case LIST:
        case RUN:
        case END:
             lex(); // this IS the extra call to lex() since nothing comes after these keywords
             break;
    }
}

// makes an extra call to lex() to look for the comma
// lex has ALREADY been called before expr_list
void expr_list() {
    if (nextToken == STRING) {
        // extra call to lex() to look for the comma or carriage return after the string
        lex();
        // do nothing else for this assignment
        // but in the next assignment you will need to print something!
    } else {
        expression();
        // expression ends with an extra call to lex() so we are already looking for the comma or carriage return by the time we get back here
    }
    while (nextToken == COMMA) {
        lex(); // move past the comma (i.e., consume the comma by looking for the next token after the comma)
        // next assignment: printf("\t");
        if (nextToken == STRING) {
            // extra call to lex() to look for the comma or carriage return after the string
            lex();
            // do nothing else for this assignment
            // but in the next assignment you will need to print something
        } else {
            expression();
            // no extra call to lex() here because expression() will have already called lex() for us when it was looking for +, -, *, or /
        }
        // there are only two valid tokens AT THIS SPOT
        if (nextToken != COMMA && nextToken != CR) {
            printf("Expecting COMMA or CR but found: %d\n", nextToken);
            exit(1);
        }
    }
}

void var_list() {
    if (nextToken != VAR) {
        printf("Expecting VAR but found: %d\n", nextToken);
    }
    else {
        lex();
        // do nothing else for this assignment
        // but in the next assignment you will need to print something
    }
    while (nextToken == COMMA) {
        lex();
        if (nextToken != VAR) {
            printf("Expecting VAR but found: %d\n", nextToken);
        }
        else {
            lex();
            // do nothing else for this assignment
            // but in the next assignment you will need to print something
        }
    }
}

void expression() {
    if(nextToken == ADD_OP || nextToken == SUB_OP) {
        lex(); // move past the leading + or - if it was there otherwise, the current nextToken is part of the term so no need to call lex()
    }
    term();
    // no need to call lex() here because term() will have already called lex() for us when it was looking for * or /
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex(); // move past the + or -
        term();
        // remember, term() will have already called lex() for us when it was looking for * or / so no need to call it again here
    }
    // no need for extra call to lex() here because the while loop will have already called lex() for us when it was looking for + or -
}

void term() {
    // you gotta do something here ... should be very similar to expression() but looking for * and / instead of + and -
    // note that term() will end up having an extra call to lex() at the end just like expression() does
    factor();
    lex(); // look for mult op or div op
    while (nextToken == MULT_OP || nextToken == DIV_OP) {
        lex();
        factor();
        lex();
    }
}

void factor() {
    // look back at the grammar for all the possibilities for a factor ... you need if else if to handle identifiers, numbers, and parenthesized expressions
    // you should make very sure NOT to have an extra call to lex() here (finally!) because expression() and term() are the ones that need the extra calls to lex() to look for +, -, *, or /
    if (nextToken == VAR || nextToken == NUMBER) {
        // dont do anything for this assignment
    }
    else if (nextToken == LEFT_PAREN) {
        lex();
        expression();
        if(nextToken != RIGHT_PAREN) {
            printf("Found %d but expecting RIGHT PAREN\n", nextToken);
        }
    }
}

// this always has an extra call to lex()
void relop() {
    if (nextToken == LT_OP) {
        lex();
        if (nextToken == RT_OP || nextToken == EQUALS_OP) {
            lex();
        }
    }
    else if (nextToken == RT_OP) {
        lex();
        if (nextToken == LT_OP || nextToken == EQUALS_OP) {
            lex();
        }
    }
    else if (nextToken == EQUALS_OP) {
        lex();
    }
    else {
        printf("Expecting some valid REL_OP but found: %d\n", nextToken);
        exit(1);
    }
}