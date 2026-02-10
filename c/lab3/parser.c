#include "lexer.c"

// data structures needed for the interpreter
int lineno = 0;   // if this is equal to 0 then we should execute immediately
char* lines[10];  // preallocate enough room for 10 lines
int linenos[10];  

void line();
void statement();
void expr_list();
void expression();
void term();
void factor();
void relop();

/******************************************************/
/* main driver */
int main()
{
  /* Open the input data file and process its contents */
  if ((in_fp = fopen("front.in", "r")) == NULL)
    printf("ERROR - cannot open front.in \n");
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
            expression(); 
            lex();
            relop();
            lex();
            expression();
            lex();
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

            break;

        case LET:
            lex();
            if (nextToken != IDENT) {
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
        // do nothing for this assignment
        // but in the next assignment you will need to print something!
    } else {
        expression();
    }
    lex(); // extra call to look for the comma
    while (nextToken == COMMA) {
        // next assignment: printf("\t");
        if (nextToken == STRING) {
            // extra call to lex() to look for the comma or carriage return after the string
            lex();
            // do nothing for this assignment
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

void expression() {
    term();
    lex(); // see if we have a + or - coming up
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();
        lex(); // see if we have another + or - coming up   
    }
    // no need for extra call to lex() here because the while loop will have already called lex() for us when it was looking for + or -
}

void term() {
    // you gotta do something here ... should be very similar to expression() but looking for * and / instead of + and -
}

void factor() {
    // look back at the grammar for all the possibilities for a factor ... you need if else if to handle identifiers, numbers, and parenthesized expressions
}

void relop() {

}