#include "lexer.c"

void line();
void statement();

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
        // consume the token by looking at the line number
        // and storing the statement that follows in the right place in our stored program
        // BUT NOT FOR THIS ASSIGNMENT
        // Call lex() to get the next token
        lex();
    }
    statement(); // note that statement MUST have an extra call to lex()
    if (nextToken != CR) {
        printf("Expecting CR, but found: %d instead!\n", nextToken);
    } 

}

void statement() {
    switch(nextToken) {
        case PRINT:
            lex();
            expr_list();
            break;
        case IF:
            lex();

            // extra call to lex to look for the carriage return
            lex();
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
            
        case RETURN:
        case CLEAR:
        case LIST:
        case RUN:
        case END:
            lex(); // this IS the extra call to lex() since nothing comes after these keywords

            break;
    }
}