	/* DEFINITIONS SECTION */
%{
/*
 *	Put text
 */

/*
 * Forward declare output functions
 *
 */
#include "pp_fe.h"

int last_was_tick = 0;
%}

WS [\t\n\f]+
TX [^\t\n\f\015]+
CR \015

%%
	{/* RULES SECTION */}

{TX}	{ pp_fe_plain (yytext); }
{WS}	{ pp_fe_white_space (yytext); }
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
