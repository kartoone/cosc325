#include "lexer.c"

// this is probably the right way to do this
// but let's do use the two data structure approach instead
typedef struct {
    int lineno;
    char* line;
} Line;
Line storedProgram[10]; // group the line numbers together with the line

// data structures needed for the interpreter
int lineno = 0;    // if this is equal to 0 then we should execute immediately
char* lines[1000];   // preallocate enough room for 1000 lines if we have more lines than that, oh well.
int linenos[1000];   // map the corresponding position in "lines" to the "line #" in this data structure
int lineindex = 0;   // keeps track of how many lines we have and where the next line should be stored
int linei = 0;       // keeps track of which line index we are on while running a program
int reti = 0;        // keeps track of the index we should return to after a gosub is executed

// here's our dirty symbol table
int symboltable[26];   // position 0 = "A", position 1 = "B", etc...
int symboldefined[26]; // store a 1 in a given position if that "symbol" has been defined 

void line();
void statement();
void expr_list();
void var_list();
int expression();
int term();
int factor();
int relop();

void killIf() {
    // force the lexer to read to the end of the line
    // this is when an if statement is false so that it finishes parsing any way without executing
    while (nextChar != '\n' && nextChar != 0) {
        getChar();
    }
    nextToken = CR;
}

// hard coded swap of the positions applied to two different data structures
void swap(int j, int k) {
    // let's take care of the char* first
    char* tmpc = lines[j];
    lines[j] = lines[k];
    lines[k] = tmpc;

    // now let's take care of swapping the ints
    int tmpi = linenos[j];
    linenos[j] = linenos[k];
    linenos[k] = tmpi;
}

// insertion sort algorithm - wikipedia
// i ← 1
// while i < length(A)
//     j ← i
//     while j > 0 and A[j-1] > A[j]
//         swap A[j] and A[j-1]
//         j ← j - 1
//     end while
//     i ← i + 1
// end while
void sort() {
    int i = 1;
    while (i < lineindex) {
        int j = i;
        while (j>0 && linenos[j-1]>linenos[j]) {
            swap(j, j-1);
            j = j - 1;
        }
        i = i + 1;
    }
}

// search through linenos and return index if found
// otherwise return -1 (if not found)
// no need for curly braces, but be careful if you change this!
int search(int lineno) {
    for (int i=0; i<lineindex; i++) 
        if (linenos[i]==lineno) 
            return i;
    return -1;
}

int findLine(int lineno) {
    int hit = search(lineno);
    if (hit<0) {
        printf("Could not find line number target %d\n", lineno);
        exit(1);
    }
    return hit;
}

/******************************************************/
/* main driver */
int main()
{
    // prep the symbol table definitions
    // to indicate that no symbols have been defined yet
    for (int i=0; i<26; i++) {
        symboldefined[i] = 0;
    }


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
        int previndex = search(lineno);
        if (previndex < 0)
            linenos[lineindex] = lineno;

        // take whatever is left in the rest of the line and store it for processing later!

        // consume the token by looking at the line number
        // and storing the statement that follows in the right place in our stored program
        // BUT NOT FOR THIS ASSIGNMENT
        // Call our special lex_endl() function to extract the rest of the line out of the file
        lex_endl(); // sets a global variable named rest_of_line that we need to store in 
                    // the right place in our lines datastructure;

        // allocate memory for the new line we just read in via lex_endl()
        // and then copy the line we just read into that new memory location
        if (previndex < 0) {
            // this must be a new line, allocate space for it
            lines[lineindex] = malloc(1000);
            strcpy(lines[lineindex], rest_of_line);
            printf("Stored this line: %s at line number %d, which is index %d\n", rest_of_line, lineno, lineindex);
            lineindex++;
        } else {
            // we are overwriting an old line so just copy it over the space that was already allocated at previndex
            strcpy(lines[previndex], rest_of_line);
            printf("Overwrote old line with this line: %s at line number %d, which is index %d\n", rest_of_line, lineno, previndex);
        }
    } else {
        statement(); // note that statement MUST have an extra call to lex()
    }
    if (nextToken != CR && nextToken != EOF) {
        printf("Expecting CR, but found: %d instead!\n", nextToken);
    } 

}

// lex() MUST have already been called before here
void statement() {
    int targetlineno; // this is ONLY used for GOTO and GOSUB
    int if_a;
    int if_b;
    int op;
    switch(nextToken) {
        case REM:
            killIf();
            break;

        case PRINT:
            lex();
            expr_list();
            // unconditionally printf("\n");
            break;

        case IF:
            lex();
            if_a = expression(); // all expressions have an extra call to lex() because of term()
            op = relop(); // this always ends with an extra call to lex()
            if_b = expression();
            if (nextToken != THEN) {
                printf("error! expecting then found something else");
            }
            lex();
            switch (op) {
                case 0:
                    if (if_a < if_b) {
                        statement();
                    } else {
                        killIf();
                    }
                    break;
                case 1:
                    if (if_a > if_b) {
                        statement();
                    } else {
                        killIf();
                    }

                    break;
                 case 2:
                    if (if_a == if_b) {
                        statement();
                    } else {
                        killIf();
                    }

                    break;
                 case 3:
                    if (if_a <= if_b) {
                        statement();
                    } else {
                        killIf();
                    }

                    break;
                 case 4:
                    if (if_a >= if_b) {
                        statement();
                    } else {
                        killIf();
                    }
                    break;
                 case 5:
                    if (if_a != if_b) {
                        statement();
                    } else {
                        killIf();
                    }
                    break;
             }
            // we never need an extra call to lex() here 
            // because statement() ALWAYS has an extra call to lex()
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
            int pos = lexeme[0]-'A';
            symboldefined[pos] = 1;
            lex();
            if (nextToken != EQUALS_OP) {
                printf("Expecting EQ but found: %d\n", nextToken);
                exit(1);
            }
            lex();
            symboltable[pos] = expression();

            // no extra call to lex() here because expression() will have already called lex() for us when it was looking for +, -, *, or /
            break;
        
        case GOTO:
            lex();
            targetlineno = expression();
            // find the linei we are supposed to jump to
            // remember this is from a recursive call where
            // we are in the middle of a for loop that will execute
            // linei++ ... so we need to set it to the target index minus 1
            linei = findLine(targetlineno)-1;
            // no extra call to lex to look for the carriage return
            break;

        case GOSUB:
            lex();
            targetlineno = expression();
            reti = linei; // save the index of the line we should return to
            // remember this is from a recursive call where
            // we are in the middle of a for loop that will execute
            // linei++ ... so we need to set it to the target index minus 1
            linei = findLine(targetlineno)-1; 

            // NO extra call to lex to look for the carriage return b/c expression() has an extra call to lex()
            break;
            
        case CLEAR:
            lineindex = 0;
            lex(); // this IS the extra call to lex() since nothing comes after these keywords
            break;

        case LIST:
            sort();
            for (int i=0; i<lineindex; i++) {
              printf("%d: %s\n", linenos[i], lines[i]);
            }
            lex(); // this IS the extra call to lex() since nothing comes after these keywords
            break;

        case RETURN:
            linei = reti;
            lex();
            break;

        case RUN:
            sort();
            // BIG TO DO HERE: update the lexer to take in a String
            // instead of always reading from a file ... DO THIS BY ADDING
            // a FLAG variable to the lexer to indicate whether it 
            // should be grabbing the next token from a FILE or from a String

            // also, add a function that will set a global string to be processed
            // and simultaneously set the flag to start reading from the string

            // loop through all the lines
            // setting the read_from_str flag and the current line as the string to be read
            // use one variable both ... a char* to the line to be prcoessed
            // if that line is null, then the lexer should be reading from the file
            for (linei=0; linei<lineindex; linei++) {
                // GOTO and GOSUB will ALTER linei
                in_str = lines[linei];
                stri = 0;
                printf("Executing: %d %s\n",linenos[linei],in_str);
                getChar();
                lex();
                line();
            }

            // DON'T FORGET, we need to clear the flag after the program
            // has run and set it to continue reading from the file
            // clearing the flag might necessitate messing with those global
            // variables (nextChar, charClass, etc...)
            lex();
            break;

        case END:
            // force the for loop to stop by setting linei = to lineindex
            linei = lineindex;
            stri = -1;  // this puts us back into "file reading" mode
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
        printf("%s\t",lexeme);
        // do nothing else for this assignment
        // but in the next assignment you will need to print something!
    } else {
        printf("%d\t",expression());
        // expression ends with an extra call to lex() so we are already looking for the comma or carriage return by the time we get back here
    }
    while (nextToken == COMMA) {
        lex(); // move past the comma (i.e., consume the comma by looking for the next token after the comma)
        // next assignment: printf("\t");
        if (nextToken == STRING) {
            // extra call to lex() to look for the comma or carriage return after the string
            lex();
            printf("%s\t",lexeme);
            // do nothing else for this assignment
            // but in the next assignment you will need to print something
        } else {
            printf("%d\t",expression());
            // no extra call to lex() here because expression() will have already called lex() for us when it was looking for +, -, *, or /
        }
        // there are only two valid tokens AT THIS SPOT
        if (nextToken != COMMA && nextToken != CR) {
            printf("Expecting COMMA or CR but found: %d\n", nextToken);
            exit(1);
        }
    }
    printf("\n");
}

void var_list() {
    int varpos[26];
    int varcnt = 0;
    if (nextToken != VAR) {
        printf("Expecting VAR but found: %d\n", nextToken);
    }
    else {
        // before we call lex() again we need to grab position
        varpos[varcnt++] = lexeme[0] - 'A';        

        lex();
        // we need to use scanf to read from the console
        // and convert whatever they type in into a number
        // and then store that number into the symboltable
        // at the right spot
        // maybe create a separate function so that you 
        // can just call it twice
    }
    while (nextToken == COMMA) {
        lex();
        if (nextToken != VAR) {
            printf("Expecting VAR but found: %d\n", nextToken);
        }
        else {
            varpos[varcnt++] = lexeme[0] - 'A';        
            lex();
        }
    }

    // now we need to use scanf to read from the console
    // and convert whatever they type in into a number
    // and then store that number into the symboltable
    // varpos[] we found during parsing
    for (int i=0; i<varcnt; i++) {
        scanf("%d",&symboltable[varpos[i]]);
        symboldefined[varpos[i]] = 1;
    }
}

int expression() {
    if(nextToken == ADD_OP || nextToken == SUB_OP) {
        lex(); // move past the leading + or - if it was there otherwise, the current nextToken is part of the term so no need to call lex()
    }
    int result = term();
    // no need to call lex() here because term() will have already called lex() for us when it was looking for * or /
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex(); // move past the + or -
        if (nextToken == ADD_OP)
            result += term();
        else
            result -= term();
        // remember, term() will have already called lex() for us when it was looking for * or / so no need to call it again here
    }
    // no need for extra call to lex() here because the while loop will have already called lex() for us when it was looking for + or -
    return result;
}

int term() {
    // you gotta do something here ... should be very similar to expression() but looking for * and / instead of + and -
    // note that term() will end up having an extra call to lex() at the end just like expression() does
    int result = factor();
    lex(); // look for mult op or div op
    while (nextToken == MULT_OP || nextToken == DIV_OP) {
        if (nextToken == MULT_OP) {
            lex();
            result *= factor();
        } else {
            lex();
            result /= factor();
        }
        lex();
    }
    return result;
}

int factor() {
    // look back at the grammar for all the possibilities for a factor ... you need if else if to handle identifiers, numbers, and parenthesized expressions
    // you should make very sure NOT to have an extra call to lex() here (finally!) because expression() and term() are the ones that need the extra calls to lex() to look for +, -, *, or /
    if (nextToken == VAR) {
        // look up the value in the symbol table
        // error if not defined
        int pos = lexeme[0] - 'A';
        if (symboldefined[pos]==0) {
            printf("How? Undefined symbol %c\n", lexeme[0]);
            exit(1);
        }
        return symboltable[pos];
    }
    else if (nextToken == NUMBER) {
        return atoi(lexeme);
    } else if (nextToken == LEFT_PAREN) {
        lex();
        int result = expression();
        if(nextToken != RIGHT_PAREN) {
            printf("Found %d but expecting RIGHT PAREN\n", nextToken);
        }
        return result;
    }
    // this should NEVER happen
    printf("What? Syntax error, expecting VAR, NUMBER, or ()\n");
    exit(1);
    return -999999;
}

// this always has an extra call to lex()
// 0: <
// 1: >
// 2: ==
// 3: <=
// 4: >=
// 5: <> or ><
int relop() {
    if (nextToken == LT_OP) {
        lex();
        if (nextToken == RT_OP || nextToken == EQUALS_OP) {
            lex();
            if (nextToken == RT_OP) {
                return 5;
            } else {
                return 3;
            }
        } else {
            return 0;
        }
    }
    else if (nextToken == RT_OP) {
        lex();
        if (nextToken == LT_OP || nextToken == EQUALS_OP) {
            lex();
            if (nextToken == LT_OP)
                return 5;
            else
                return 4;
        } else {
            return 1;
        }
    }
    else if (nextToken == EQUALS_OP) {
        lex();
        return 2;
    }
    else {
        printf("Expecting some valid REL_OP but found: %d\n", nextToken);
        exit(1);
    }
    return -1; // there should be NO PATH that ever hits here
}