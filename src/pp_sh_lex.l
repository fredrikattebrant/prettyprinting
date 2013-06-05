%{
	/* DEFINITIONS SECTION */
/*
 *	Scan sh syntax
 */

/*
 * Forward declare output functions
 *
 * Reserved words may occur with a quoted string. However, comments
 * may not.
 */
#include "pp_fe.h"
#include "pp_sh.h"

#define PLAIN  pp_fe_plain(yytext)
#define BOLD   pp_fe_bold(yytext)
#define ITALIC pp_fe_italic(yytext)
#define WSPACE pp_fe_white_space(yytext)


int	in_quotes = 0;
char	quote;

void check_quotes (char *);

%}

%s COMMENT STANDARD

D	([0-9]+)
WORD	[a-zA-Z](_?[a-zA-Z0-9])*
WS	[\t\n\014\015 ]+
OTHER	[^\"\'\`\t\n\014\015]

QT	\" | \' | \`
CR \015

%%


\#	{ if (!in_quotes) {
			BEGIN COMMENT;
			ITALIC;
		  } else {
		  	PLAIN;
		  }
		}
<COMMENT>[^\n\t\f\015]*	{ ITALIC; }
<COMMENT>[\t]*			{ WSPACE; }
<COMMENT>[\n,\f\015]*	{ WSPACE; BEGIN STANDARD;}


<STANDARD>{WS}		{ WSPACE; }
<STANDARD>{D}		{ PLAIN; }
<STANDARD>{WORD}	{ if (is_sh_reserved_word (yytext)) {
				BOLD;
			   } else {
	  			PLAIN;
			   }
			}

<STANDARD>{OTHER}	{ PLAIN; }
<STANDARD>\"|\'|\`	{ check_quotes (yytext); PLAIN; }
<STANDARD>.		{ PLAIN; }

{CR}			{ ; }

%%

	/* USER'S SUBROUTINES SECTION */

void check_quotes (delim)
	char	*delim;
{
	if (in_quotes) {
		if (*delim == quote) {
			in_quotes = 0;
		}
	} else {
		quote = *delim;
		in_quotes = 1;
	}
}

int yywrap ()
{
	return (pp_yywrap());
}

main (argc, argv)
	int  argc;
	char **argv;
{
	BEGIN STANDARD;
	pp_main (argc, argv);
}
