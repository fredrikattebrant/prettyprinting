	/* DEFINITIONS SECTION */
%{
/*
 *	Scan IDL syntax
 */

/*
 * Forward declare output functions
 *
 */
#include "pp_fe.h"
#include "pp_idl.h"

#define ITALIC	pp_fe_italic (yytext)
#define BOLD	pp_fe_bold (yytext)
#define BOLDIT	pp_fe_bolditalic (yytext)
#define WHITE	pp_fe_white_space (yytext)
#define PLAIN	pp_fe_plain (yytext)

%}

WORD [a-zA-Z0-9_]+
WS ([ \n\t\014\015])+
QSTR \"[^\"\n\014\015]*[\"]
PPCOMM \/\/[^\n\014\015]*
CR \015

	/* Extra lexer states */
%s BASE COMMENT ATTR ATTRCOMMENT

%%
      {/* RULES SECTION */}

<BASE>"/*"					{ ITALIC; BEGIN COMMENT; }
<COMMENT>[^\*\n\t\014\015]* { ITALIC; }
<COMMENT>[\n\t\014\015]+	{ WHITE; }
<COMMENT>\*					{ ITALIC; }
<COMMENT>"*/"				{ ITALIC; BEGIN BASE; }

<BASE>"["		{ BOLDIT;  BEGIN ATTR; }
<ATTR>{WORD}	{ if (is_idl_reserved_word(yytext)) {
					BOLDIT;
				  } else {
					ITALIC;
				  }
				}
<ATTR>{PPCOMM} { ITALIC; }
<ATTR>{WS}		{ WHITE; }
<ATTR>{QSTR}|[^\]]	{ ITALIC; }
<ATTR>{CR}		{ ; }
<ATTR>"]"		{ BOLDIT; BEGIN BASE; }

<ATTR>"/*"						{ ITALIC; BEGIN ATTRCOMMENT; }
<ATTRCOMMENT>[^\*\n\t\014\015]* { ITALIC; }
<ATTRCOMMENT>[\n\t\014\015]+	{ WHITE; }
<ATTRCOMMENT>\*					{ ITALIC; }
<ATTRCOMMENT>"*/"				{ ITALIC; BEGIN ATTR; }

<BASE>{PPCOMM} { ITALIC; }

<BASE>{WORD}	{ if (is_idl_reserved_word(yytext)) {
					BOLD;
				  } else {
					PLAIN;
				  }
				}

<BASE>{WS}		{ WHITE; }
<BASE>{QSTR}|.	{ PLAIN; }
<BASE>{CR}		{ ; }

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
	BEGIN BASE;
	pp_main (argc, argv);
}
