/* front.c - a lexical analyzer system for simple
             arithmetic expressions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char rest_of_line[1000]; // should be enough room (hopefully) to store all the characters in the rest of the line
char nextChar;
int lexLen;
int token; // this is never used but your book gave it to us in the code
int nextToken;
FILE *in_fp; /*, *fopen(); */
char* in_str; // "statement" we are currently processing when running a program
int stri=-1; // position within string ... -1 means read from file
/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define QUOTE 2
#define UNKNOWN 99

/* Token codes */
#define STRING 8
#define NUMBER 10
#define IDENT 11
#define VAR 12
#define REM 13
#define LT_OP 18
#define RT_OP 19
#define EQUALS_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define PRINT 30
#define IF 31
#define THEN 32
#define GOTO 33
#define GOSUB 34
#define INPUT 35
#define LET 36
#define COMMA 40
#define RETURN 41
#define END 42
#define LIST 43
#define CLEAR 44
#define RUN 45
#define CR 99


/*****************************************************/
/* lookup - a function to lookup operators and parentheses
            and return the token */
int lookup(char ch)
{
  switch (ch)
  {
  case '(':
    addChar();
    nextToken = LEFT_PAREN;
    break;

  case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    break;

  case '+':
    addChar();
    nextToken = ADD_OP;
    break;

  case '-':
    addChar();
    nextToken = SUB_OP;
    break;

  case '*':
    addChar();
    nextToken = MULT_OP;
    break;

  case '/':
    addChar();
    nextToken = DIV_OP;
    break;

  case '=':
    addChar();
    nextToken = EQUALS_OP;
    break;

  case '<':
    addChar();
    nextToken = LT_OP;
    break;

  case '>':
    addChar();
    nextToken = RT_OP;
    break;

  case ',':
    addChar();
    nextToken = COMMA;
    break;

  case '\n':
    addChar();
    nextToken = CR;
    break;

  default:
    addChar();
    printf("Unexpected symbol found: %c while working on the current lexeme: %s\n", nextChar, lexeme);
    exit(1);
    break;
  }
  return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
  if (lexLen <= 98)
  {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  }
  else
    printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
             input and determine its character class */
void getChar()
{
  if (stri>=0 && stri>=strlen(in_str)) {
    charClass = CR;
    nextChar = '\n';
    return;
  }
  int c = stri<0 ? getc(in_fp) : in_str[stri++];
  if (c == EOF)
  {
    charClass = EOF;
    nextChar = 0;
  }
  else
  {
    nextChar = (char)c;
    if (isalpha((unsigned char)nextChar))
      charClass = LETTER;
    else if (isdigit((unsigned char)nextChar))
      charClass = DIGIT;
    else if (nextChar == '"')
      charClass = QUOTE;
    else
      charClass = UNKNOWN;
  }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
                 returns a non-whitespace character */
void getNonBlank()
{
  while (isspace(nextChar)&&nextChar!='\n')
    getChar();
}

/* examines current lexeme and returns specific token or IDENT if it's not a keyword */
int keywordLookup() {
  if (strcmp(lexeme,"PRINT")==0 || strcmp(lexeme,"PR")==0)
    return PRINT;
  else if (strcmp(lexeme,"REM")==0)
    return REM;
  else if (strcmp(lexeme,"INPUT")==0)
    return INPUT;
  else if (strcmp(lexeme,"GOSUB")==0)
    return GOSUB;
  else if (strcmp(lexeme,"GOTO")==0)
    return GOTO;
  else if (strcmp(lexeme,"LET")==0)
    return LET;
  else if (strcmp(lexeme,"END")==0)
    return END;
  else if (strcmp(lexeme,"CLEAR")==0)
    return CLEAR;
  else if (strcmp(lexeme,"LIST")==0)
    return LIST;
  else if (strcmp(lexeme,"RUN")==0)
    return RUN;
  else if (strcmp(lexeme,"IF")==0)
    return IF;
  else if (strcmp(lexeme,"THEN")==0)
    return THEN;
  else if (strcmp(lexeme,"RETURN")==0)
    return RETURN;
  else if (strlen(lexeme)==1)
    return VAR;
  //else if ... finish all the keywords!
  else
    return IDENT;
  
}

void lex_endl() {
  int i;
  // read all the characters into a string but not the newline character
  getChar(); // side effect of setting nextChar and charClass and advancing the filepointer
  for (i=0; nextChar != '\n' && nextChar != EOF; i++) {
    rest_of_line[i] = nextChar;
    getChar();
  }
  rest_of_line[i] = 0; // string termination character
  
  // let's take care of the END first
  // after we consume the entire line, if this is program is valid
  // there should be a newline character at the end of the line
  // and the nextToken should be pointing at CR
  lexLen = 1;
  strcpy(lexeme,"\n");
  nextToken = CR;
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
         expressions 
   // depends on charClass and nextChar already being set by the caller
         */
int lex()
{
  lexLen = 0;
  getNonBlank();
  switch (charClass)
  {
    /* Parse identifiers */
  case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT)
    {
      addChar();
      getChar();
    }
    nextToken = keywordLookup();
    break;

    /* Parse integer literals */
  case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT)
    {
      addChar();
      getChar();
    }
    nextToken = NUMBER;
    break;

  case QUOTE:
    addChar();
    getChar();
    while (charClass != QUOTE)
    {
      addChar(); 
      getChar();
    }
    addChar();
    getChar();
    nextToken = STRING;
    break;

    /* Parentheses and operators */
  case UNKNOWN:
    lookup(nextChar);
    getChar();
    break;

    /* EOF */
  case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = 0;
    break;
  } /* End of switch */
  //printf("Next token is: %d, Next lexeme is %s\n",
  //       nextToken, lexeme);
  return nextToken;
} /* End of function lex */