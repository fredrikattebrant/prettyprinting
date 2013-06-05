	/* DEFINITIONS SECTION */
%{
/*
 *	Scan Ada syntax
 */

/*
 * Forward declare output functions
 *
 */
#include "pp_fe.h"
#include "pp_ada.h"

int last_was_tick = 0;
int last_was_pragma = 0;
int formfeed_after_next_lf = 0;
%}

WORD [a-zA-Z](_?[a-zA-Z0-9])*
WS [ \t\014\015]+
QSTR \"[^\"\n\014\015]*[\"]
COMMENT --[^\n\014\015]*
TICK '
LF \n
CR \015

%%
	{/* RULES SECTION */}

{WORD}	{ if (is_ada_reserved_word (yytext) && !last_was_tick) {
		/* "last_was_tick" says that for instance "range" *
		 * should not be bold when used as an attribute   */
		pp_fe_bold (yytext);
		last_was_pragma = is_pragma (yytext);
	  } else if (last_was_pragma && is_page (yytext)) {
	  	formfeed_after_next_lf = 1;
	  	last_was_pragma = 0;
	  	pp_fe_plain (yytext);
	  } else {
	  	pp_fe_plain (yytext);
	  	last_was_pragma = 0;
	  }
	  last_was_tick = 0;
	}

{COMMENT}		{ pp_fe_italic (yytext); }
{TICK}			{ last_was_tick = 1; pp_fe_plain (yytext); }
{WS}			{ pp_fe_white_space (yytext); }
{LF}			{ if (formfeed_after_next_lf) {
				pp_fe_white_space ("\n\f");
				formfeed_after_next_lf = 0;
			  } else {
			  	pp_fe_white_space ("\n");
			  }
			}
{QSTR}|.		{ last_was_tick = 0; pp_fe_plain (yytext); }

{CR}	{ ; }

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
