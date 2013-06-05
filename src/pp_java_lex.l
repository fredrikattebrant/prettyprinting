	/* DEFINITIONS SECTION */
%{
/*
 *	Scan Java syntax
 */

/*
 * Forward declare output functions
 *
 */
#include "pp_fe.h"
#include "pp_java.h"

int last_was_sharp = 0;
%}

WORD [a-zA-Z0-9_]+
WS ([ \n\t\014\015])+
QSTR \"[^\"\n\014\015]*[\"]
SHARP "#"
PPCOMM \/\/[^\n\014\015]*
CR \015

	/* Extra lexer states */
%s COMMENT

%%
      {/* RULES SECTION */}

   {/* "/ *" enters the comment state. The pattern [^\*\n]* catches the      */}
   {/* rest of the line, or to the next "*". We cannot go further, since we */}
   {/* have to recognize the end of a comment as "* /" (with no space..)    */}
   {/* We catch newlines separately, to minimize the risk of having too     */}
   {/* long input strings to the implementation. Lastly, we catch the       */}
   {/* "comments-end" pattern, and leave the COMMENT state.                 */}

"/*"			{ pp_fe_italic (yytext); BEGIN COMMENT; }
<COMMENT>[^\*\n\t\014\015]* { pp_fe_italic (yytext); }
<COMMENT>[\n\t\014\015]+	{ pp_fe_white_space (yytext); }
<COMMENT>\*		{ pp_fe_italic (yytext); }
<COMMENT>"*/"	  { pp_fe_italic (yytext); BEGIN 0; }

{PPCOMM} { pp_fe_italic (yytext); }

{WORD}	{ if (is_java_reserved_word(yytext) ||
	      (last_was_sharp) ) {
		pp_fe_bold (yytext);
	  } else {
	  	pp_fe_plain (yytext);
	  }
	  last_was_sharp = 0;
	}

{SHARP}		{ pp_fe_plain (yytext); last_was_sharp = 1; }
{WS}		{ pp_fe_white_space (yytext); }
{QSTR}|.	{ pp_fe_plain (yytext); last_was_sharp = 0; }
{CR}		{ ; }

%%
	/* USER'S SUBROUTINES SECTION */

int yywrap ()
{
	return (pp_yywrap());
}

main (argc, argv)
	int  argc;
	char **argv;
{
	pp_main (argc, argv);
}
