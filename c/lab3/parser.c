#include "lexer.c"

// data structures needed for the interpreter
int lineno = 0;   // if this is equal to 0 then we should execute immediately
char* lines[10];  // preallocate enough room for 10 lines
int linenos[10];  

void line();
void statement();
void expr_list();
void expression();
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

            // extra call to lex to look for the carriage return
            lex();
            break;

        // keep going with more cases INPUT DOES NOT NEED THE EXTRA CALL TO LEX ... NEITHER DO THE ONES THAT ARE JUST KEYWORDS
        case INPUT:
            lex();

            break;

        case LET:
            lex();

            // extra call to lex to look for the carriage return
            lex();
            break;
        
        case GOSUB:
            lex();
            expression();

            // extra call to lex to look for the carriage return
            lex();
            break;
            
        // case RETURN:
        // case CLEAR:
        // case LIST:
        // case RUN:
        // case END:
        //     lex(); // this IS the extra call to lex() since nothing comes after these keywords
        //     you probably need another call to lex() right here!!!!
        //     break;
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
            // do nothing for this assignment
            // but in the next assignment you will need to print something
        } else {
            expression();
        }
        lex(); // extra call to look for the comma
        // there are only two valid tokens AT THIS SPOT
        if (nextToken != COMMA && nextToken != CR) {
            printf("Expecting COMMA or CR but found: %d\n", nextToken);
            exit(1);
        }
    }
}

void expression() {
    lex(); // you gotta do more than this!
}

void relop() {

}