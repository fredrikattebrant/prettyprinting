	/* DEFINITIONS SECTION */
%{
/*
 *	Scan Visual Basic syntax
 */

/*
 * Forward declare output functions
 *
 */
#include "pp_fe.h"
#include "pp_vb.h"

int last_was_sharp = 0;
%}

WORD [a-zA-Z](_?[a-zA-Z0-9])*
WS [ \t\014\n\015]+
QSTR \"[^\"\n\014\015]*[\"]
SHARP "#"
COMMENT \'[^\n\015]*
REM	REM\ [^\n\015]*
CR \015

%%
	{/* RULES SECTION */}

{COMMENT}	{ pp_fe_italic (yytext); }
{REM}		{ pp_fe_italic (yytext); }

{WORD}	{ if (is_vb_reserved_word (yytext) || (last_was_sharp)) {
				pp_fe_bold (yytext);
	  	  } else {
	  			pp_fe_plain (yytext);
	  	  }
		  last_was_sharp = 0;
		}

{SHARP}			{ last_was_sharp = 1; pp_fe_plain (yytext); }
{WS}			{ pp_fe_white_space (yytext); }
{QSTR}|.		{ last_was_sharp = 0; pp_fe_plain (yytext); }
{CR}			{ ; }

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
