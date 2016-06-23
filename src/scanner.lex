%{
#include "scanner.h"
%}

%option c++

/* ------------------- definitions -------------------- */
/* newline */
NL            "\n"

/* anything but newline */
NOTNL         .

/* any of 256 source characters */
ANY           ({NOTNL}|{NL})

/* backslash */
BACKSL        "\\"

/* beginnging of line (must be start of a pattern) */
BOL           ^

/* end of line (would like EOF to qualify also, but flex doesn't allow it */
EOL           {NL}

/* letter or underscore */
LETTER        [A-Za-z_]

/* letter or underscore or digit */
ALNUM         [A-Za-z_0-9]

/* decimal digit */
DIGIT         [0-9]
HEXDIGIT      [0-9A-Fa-f]

/* sequence of decimal digits */
DIGITS        ({DIGIT}+)
/* sequence of hex digits */
HEXDIGITS     ({HEXDIGIT}+)

/* sign of a number */
SIGN          ("+"|"-")

/* integer suffix */
/* added 'LL' option for gcc/c99 long long compatibility */
ELL_SUFFIX    [lL]([lL]?)
INT_SUFFIX    ([uU]{ELL_SUFFIX}?|{ELL_SUFFIX}[uU]?)

/* floating-point suffix letter */
FLOAT_SUFFIX  [flFL]

/* normal string character: any but quote, newline, or backslash */
STRCHAR       [^\"\n\\]

/* (start of) an escape sequence */
ESCAPE        ({BACKSL}{ANY})

/* double quote */
QUOTE         [\"]

/* normal character literal character: any but single-quote, newline, or backslash */
CCCHAR        [^\'\n\\]

/* single quote */
TICK          [\']

/* space or tab */
SPTAB         [ \t]

/* preprocessor "character" -- any but escaped newline */
PPCHAR        ([^\\\n]|{BACKSL}{NOTNL})


%%


  /* operators, punctuators and keywords: tokens with one spelling */
"auto"                   *yyout << "[TYPE]";
"break"                  *yyout << YYText();
"bool"                   *yyout << "[TYPE]";
"case"                   *yyout << YYText();
"catch"                  *yyout << YYText();
"cdecl"                  *yyout << YYText();
"char"                   *yyout << "[TYPE]";
"class"                  *yyout << YYText();
"const"                  *yyout << "[KWORD]";
"const_cast"             *yyout << YYText();
"continue"               *yyout << YYText();
"default"                *yyout << YYText();
"delete"                 *yyout << YYText();
"do"                     *yyout << YYText();
"double"                 *yyout << "[TYPE]";
"dynamic_cast"           *yyout << YYText();
"else"                   *yyout << YYText();
"enum"                   *yyout << YYText();
"explicit"               *yyout << YYText();
"export"                 *yyout << YYText();
"extern"                 *yyout << YYText();
"false"                  *yyout << YYText();
"float"                  *yyout << "[TYPE]";
"for"                    *yyout << YYText();
"friend"                 *yyout << YYText();
"goto"                   *yyout << YYText();
"if"                     *yyout << YYText();
"inline"                 *yyout << YYText();
"int"                    *yyout << "[TYPE]";
"long"                   *yyout << "[TYPE]";
"mutable"                *yyout << YYText();
"namespace"              *yyout << YYText();
"new"                    *yyout << YYText();
"operator"               *yyout << YYText();
"pascal"                 *yyout << YYText();
"private"                *yyout << YYText();
"protected"              *yyout << YYText();
"public"                 *yyout << YYText();
"register"               *yyout << YYText();
"reinterpret_cast"       *yyout << YYText();
"return"                 *yyout << YYText();
"short"                  *yyout << YYText();
"signed"                 *yyout << YYText();
"sizeof"                 *yyout << YYText();
"static"                 *yyout << YYText();
"static_cast"            *yyout << YYText();
"struct"                 *yyout << YYText();
"switch"                 *yyout << YYText();
"template"               *yyout << YYText();
"this"                   *yyout << YYText();
"throw"                  *yyout << YYText();
"true"                   *yyout << YYText();
"try"                    *yyout << YYText();
"typedef"                *yyout << YYText();
"typeid"                 *yyout << YYText();
"typename"               *yyout << YYText();
"union"                  *yyout << YYText();
"unsigned"               *yyout << YYText();
"using"                  *yyout << YYText();
"virtual"                *yyout << YYText();
"void"                   *yyout << YYText();
"volatile"               *yyout << YYText();
"wchar_t"                *yyout << "[TYPE]";
"while"                  *yyout << YYText();

"std"                    *yyout << YYText();
"cin"                    *yyout << YYText();
"cout"                   *yyout << YYText();
"vector"                 *yyout << YYText();
"size_t"                 *yyout << YYText();
"map"                    *yyout << YYText();
"set"                    *yyout << YYText();
"deque"                  *yyout << YYText();
"priority_queue"         *yyout << YYText();
"queue"                  *yyout << YYText();
"list"                   *yyout << YYText();
"stack"                  *yyout << YYText();
"unordered_map"          *yyout << YYText();
"unordered_set"          *yyout << YYText();
"endl"                   *yyout << YYText();
"string"                 *yyout << YYText();



"("                      *yyout << YYText();
")"                      *yyout << YYText();
"["                      *yyout << YYText();
"]"                      *yyout << YYText();
"->"                     *yyout << YYText();
"::"                     *yyout << YYText();
"."                      *yyout << YYText();
"!"                      *yyout << YYText();
"~"                      *yyout << YYText();
"+"                      *yyout << YYText();
"-"                      *yyout << YYText();
"++"                     *yyout << YYText();
"--"                     *yyout << YYText();
"&"                      *yyout << YYText();
"*"                      *yyout << YYText();
".*"                     *yyout << YYText();
"->*"                    *yyout << YYText();
"/"                      *yyout << YYText();
"%"                      *yyout << YYText();
"<<"                     *yyout << YYText();
">>"                     *yyout << YYText();
"<"                      *yyout << YYText();
"<="                     *yyout << YYText();
">"                      *yyout << YYText();
">="                     *yyout << YYText();
"=="                     *yyout << YYText();
"!="                     *yyout << YYText();
"^"                      *yyout << YYText();
"|"                      *yyout << YYText();
"&&"                     *yyout << YYText();
"||"                     *yyout << YYText();
"?"                      *yyout << YYText();
":"                      *yyout << YYText();
"="                      *yyout << YYText();
"*="                     *yyout << YYText();
"/="                     *yyout << YYText();
"%="                     *yyout << YYText();
"+="                     *yyout << YYText();
"-="                     *yyout << YYText();
"&="                     *yyout << YYText();
"^="                     *yyout << YYText();
"|="                     *yyout << YYText();
"<<="                    *yyout << YYText();
">>="                    *yyout << YYText();
","                      *yyout << YYText();
"..."                    *yyout << YYText();
";"                      *yyout << YYText();
"{"
"}"

  /* end of line */
[\n\r]  {
  *yyout << YYText();
}

    /* integer literal; dec, oct, or hex */
[1-9][0-9]*{INT_SUFFIX}?           |
[0][0-7]*{INT_SUFFIX}?             |
[0][xX][0-9A-Fa-f]+{INT_SUFFIX}?   {
  *yyout << "[INT]";
}

  /* hex literal with nothing after the 'x' */
[0][xX] {
  *yyout << "[INT]";
}

    /* identifier: e.g. foo */
{LETTER}{ALNUM}* {
  *yyout << "[ID]";
}

  /* floating literal */
{DIGITS}"."{DIGITS}?([eE]{SIGN}?{DIGITS})?{FLOAT_SUFFIX}?   |
{DIGITS}"."?([eE]{SIGN}?{DIGITS})?{FLOAT_SUFFIX}?	    |
"."{DIGITS}([eE]{SIGN}?{DIGITS})?{FLOAT_SUFFIX}?	    {
  *yyout << "[FLT]";
}

  /* floating literal with no digits after the 'e' */
{DIGITS}"."{DIGITS}?[eE]{SIGN}?   |
{DIGITS}"."?[eE]{SIGN}?           |
"."{DIGITS}[eE]{SIGN}?            {

  /* in recovery rules like this it's best to yield the best-guess
   * token type, instead of some TOK_ERROR, so the parser can still
   * try to make sense of the input; having reported the error is
   * sufficient to ensure that later stages won't try to interpret
   * the lexical text of this token as a floating literal */
  *yyout << "[FLT]";
}

  /* string literal */
"L"?{QUOTE}({STRCHAR}|{ESCAPE})*{QUOTE} {
  *yyout << "[STR]";
}

  /* string literal missing final quote */
"L"?{QUOTE}({STRCHAR}|{ESCAPE})*{EOL}   {
    *yyout << "[STR]";
}

  /* character literal */
"L"?{TICK}({CCCHAR}|{ESCAPE})*{TICK}   {
  *yyout << "[CHAR]";
}

  /* character literal missing final tick */
"L"?{TICK}({CCCHAR}|{ESCAPE})*{EOL}    {
  *yyout << "[CHAR]";
}

  /* unterminated character literal */
"L"?{TICK}({CCCHAR}|{ESCAPE})*{BACKSL}?  {
  *yyout << "[CHAR]";
}

  /* preprocessor */
  /* technically, if this isn't at the start of a line (possibly after
   * some whitespace), it should be an error.. I'm not sure right now how
   * I want to deal with that (I originally was using '^', but that
   * interacts badly with the whitespace rule) */


  /* other preprocessing: ignore it */
  /* trailing optional baskslash to avoid backing up */
"#"{PPCHAR}*({BACKSL}{NL}{PPCHAR}*)*{BACKSL}?   {
  // ignore ?
}

  /* whitespace */
  /* 10/20/02: added '\r' to accomodate files coming from Windows; this
   * could be seen as part of the mapping from physical source file
   * characters to the basic character set (cppstd 2.1 para 1 phase 1),
   * except that it doesn't happen for chars in string/char literals... */
[ \f\v\t]+  {
    // delete whitespace
}

  /* C++ comment */
  /* we don't match the \n because that way this works at EOF */
"//"{NOTNL}*    {
  // delete comment
}

  /* C comment */
"/""*"([^*]|"*"*[^*/])*"*"+"/"     {
  // delete comment
}

  /* unterminated C comment */
"/""*"([^*]|"*"*[^*/])*"*"*        {
  // delete comment
}




  /* else */
.  {
  *yyout << YYText();
}

%%

int yyFlexLexer::yywrap(void)
{
    return 1;
}
