/*
 *  pp_me.c	PrettyPrinter Midend
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

#include "pp_me.h"
#include "pp_be.h"

/*  "Exported" variables  */
int	me_curr_col = 0, me_broken_lines = 0;
int	me_cols_per_row, me_tab = 8;


/*  "Private" variables  */
static	int	me_curr_row = 0;
static	int me_curr_page = 0;
static	int	me_curr_line_no = 1;
static	int	me_first_line_on_paper = 1;
static	int	me_curr_paper = 1;
static	int	me_rows_per_page, me_pages_per_paper;
static	int	me_print_line_nums = 0;
static	int	me_file_page = 1;
static	int	me_dnd_started = 0;
static	int	me_arg2_is_title = 0;
static	char	*me_title = NULL;

extern	FILE	*yyin;
static	char	**file_list;
static	int	file_count;
static	int	file_to_open;

static	char	file_name[512], file_date[10], file_time[10];

static	pp_be_format_t		me_format = Form_2P;
static	pp_be_paper_size_t	me_paper = A4;

static	struct	tm		*curr_clock;
static	struct	timeval		tval;
static	struct	timezone	tzone;
static	struct	stat		statb;

static	int	first_time = 0;


/*  INTERNAL SUBPROGRAMS  */

/*
 *  pp_me_make_title
 */
static char *pp_me_make_title (char *filename)
{
	static char buf [BUFSIZ];
	char *replacor;

	if (!me_title)
		return (filename);

	/*
	 * Idea: If there is an occurance of "%F" in "me_title", then
	 *       replace that with the filename, otherwise return the
	 *       title as is
	 */
	if (replacor = (char *)strstr (me_title, "%F")) {
		strncpy (buf, me_title, replacor - me_title);
		buf [replacor - me_title] = '\0';
		strcat (buf, filename);
		strcat (buf, replacor+2);
		return (buf);
	} else {
		return (me_title);
	}
}


/*
 *  pp_me_usage
 */
static void pp_me_usage (char *argv0)
{
	char	*prog;

	if ((prog = (char *) strrchr (argv0, '/')) == NULL) {
		prog = argv0;
	} else {
		prog++;
	}

	/*
	 *  NOTE! There is an undocumented switch 'r' used by the
	 *        "dnd_printer" program to report the result in an
	 *        efficient manner.
	 */
	fprintf (stderr,
		"Usage: %s [-[(1|2|4|8)[p|l][s]][A|L][n][tN][h|?|S][u][T title] [file ...]\n"
		"  1|2|4|8: number of pages per paper (default 2)\n"
		"  p|l: portrait/landscape per page on the paper, default portrait\n"
		"  s  : Extra small text - longer rows (only for 1 pg/p)\n"
		"  A|L: A4 (default) or Letter\n"
		"  n  : Print line numbers\n"
		"  tN : Use N as tabstop, default N=8\n"
		"  h|?: This text\n"
		"  S  : List details on the different sizes\n"
		"  u  : Use USER instead of GECOS as printed by name\n" 
		"  T  : Title (default is filename or \"stdin\"). Filename replaced"
		" for string \"%%F\"\n"
		"Env var PP_DEFAULTS may be used to set other defaults (e.g"
		" \"4p\")\n",
		prog);
	exit (1);
}


/*
 *  pp_me_parse
 */
static void pp_me_parse (char *args, char *progname)
{
	char	c;
	int 	list_sizes_only = 0;

	while ((c = *args++) != NULL) {
		switch (c) {
			case '1':
				me_format=Form_1P; break;
			case '2':
				me_format=Form_2P; break;
			case '4':
				me_format=Form_4P; break;
			case '8':
				me_format=Form_8P; break;
			case 'p':
				switch (me_format) {
					case Form_1L:
						me_format=Form_1P; break;
					case Form_2L:
						me_format=Form_2P; break;
					case Form_4L:
						me_format=Form_4P; break;
					case Form_8L:
						me_format=Form_8P; break;
					default:
						break;
				} break;
			case 'l':
				switch (me_format) {
					case Form_1P:
						me_format=Form_1L; break;
					case Form_2P:
						me_format=Form_2L; break;
					case Form_4P:
						me_format=Form_4L; break;
					case Form_8P:
						me_format=Form_8L; break;
				} break;
			case 's':
				if (me_format == Form_1P)
					me_format = Form_1Ps;
				else if (me_format == Form_1L)
					me_format = Form_1Ls;
				break;
			case 'A':
				me_paper = A4;
				break;
			case 'L':
				me_paper = Letter;
				break;
			case 'n':
				me_print_line_nums = 1;
				break;
			case 't':
				me_tab = atoi (args);
				for (;
				     (*args>='0')&&(*args<='9');
				     args++)
					;
				break;
			case 'r':
				me_dnd_started = 1;
				break;
			case 'S':
				list_sizes_only = 1;
				break;
			case 'T':
				me_arg2_is_title = 1;
				break;
			case 'u':
				be_use_gecos = 0;
				break;
			case 'h':
			case '?':
			default:
				pp_me_usage (progname);
				break;
		}
	}

	if (list_sizes_only) {
		pp_be_list_sizes (me_format);
		exit (0);
	}
}


/*  EXPORTED SUBPROGRAMS  */

/*
 *  pp_main
 */
void pp_main (int argc, char **argv)
{
	char	c, *fstr = argv[1], *defaults;

	setbuf (stdout, NULL);
	setbuf (stderr, NULL);

	defaults = (char *) getenv ("PP_DEFAULTS");
	if (defaults)
		pp_me_parse (defaults, argv[0]);

	me_arg2_is_title = 0;		/* Not settable via envvar */

	/* parse format */
	if ((argc > 1) && (*fstr == '-')) {
		pp_me_parse (++fstr, argv[0]);
		if (me_arg2_is_title) {
			me_title = argv[2];
			argv++;
			argc--;
		}
		argv++;
		argc--;
	}

	/*  Process input files (or stdin)  */

	yyin = stdin; /* FXO: since we need to close something where printing files */

	if (argc == 1) {		/* stdin */

		file_list = NULL;
		file_count = 0;
		file_to_open = 0;

		gettimeofday(&tval, &tzone);
		curr_clock = localtime (&tval.tv_sec);
		strftime (file_date, 10, "%y-%m-%d", curr_clock);
		strftime (file_time, 10, "%H:%M:%S", curr_clock);

		pp_be_set_new_file (pp_me_make_title ("stdin"), file_date, file_time);
		pp_be_put_prolog (me_format, me_paper, &me_cols_per_row,
				  &me_rows_per_page, &me_pages_per_paper);
		pp_be_new_paper (me_curr_paper);
		pp_be_new_page  (me_curr_page, me_file_page);
		yylex ();
		pp_be_end_page ();
		pp_be_end_paper (me_first_line_on_paper, me_curr_line_no);
		pp_be_put_epilog ();
	} else {				/* file from argv */
		file_list = argv + 1;
		file_count = argc - 1;
		file_to_open = 0;
		pp_yywrap ();			/* Open first file */
		yylex ();
		pp_be_end_page ();
		pp_be_end_paper (me_first_line_on_paper, me_curr_line_no);
		pp_be_put_epilog ();
	}

	if (me_dnd_started) {
		/*  Report results with an easily parsed format  */
		fprintf (stderr, "%d %d",
			 be_total_no_of_papers, me_broken_lines);
	} else {
		if (be_total_no_of_papers == 1)
			fprintf (stderr, "Printed 1 page\n");
		else
			fprintf (stderr, "Printed %d pages\n",
				 be_total_no_of_papers);

		if (me_broken_lines == 1)
			fprintf (stderr, "1 line wrapped because of length\n");
		else if (me_broken_lines > 1)
			fprintf (stderr, "%d lines wrapped because of length\n",
				 me_broken_lines);
	}
}


/*
 *  pp_yywrap
 */
int pp_yywrap ()
{
	FILE	*file;

	if (file_count > 0)
	  fclose (yyin);		/* Close any file opened by us */

	if (file_to_open == file_count)
		return (1);		/* No more input */

	while (file_list [file_to_open] != NULL) {
		file = fopen (file_list [file_to_open], "r");
		file_to_open++;
		if (file != NULL) {

			if (fstat(fileno (yyin), &statb)) {
				pp_be_set_new_file
					(pp_me_make_title (file_list [file_to_open - 1]),
					 "date error",
					 "time error");
			} else {
				curr_clock = localtime(&statb.st_mtime);
				strftime (file_date, 10,
					  "%y-%m-%d", curr_clock);
				strftime (file_time, 10,
					  "%H:%M:%S", curr_clock);
				pp_be_set_new_file
					(pp_me_make_title (file_list [file_to_open - 1]),
					 file_date,
					 file_time);
			}

			if (first_time++ == 0) {
				pp_be_put_prolog (me_format,
						  me_paper,
						  &me_cols_per_row,
						  &me_rows_per_page,
						  &me_pages_per_paper);
			} else {
				pp_be_end_page  ();
				pp_be_end_paper (me_first_line_on_paper, me_curr_line_no);
			}

			yyin = file;
			me_curr_paper   = 1;
			me_curr_page    = 0;
			me_curr_row     = 0;
			me_curr_col     = 0;
			me_first_line_on_paper = 1;
			me_curr_line_no = 1;
			me_file_page	= 1;

			pp_be_new_paper (me_curr_paper);
			pp_be_new_page  (me_curr_page, me_file_page);
			break;	/* Leave the loop */
		} else {
			fprintf (stderr, "Could not open %s\n",
				 file_list [file_to_open - 1]);
		}
	}

	return (file ? 0 : 1);	/* More input? */
}


/*
 *  pp_me_form_feed
 */
void pp_me_form_feed ()
{
	pp_be_end_page ();

	me_file_page++;
	if (me_curr_page == (me_pages_per_paper - 1)) {
		pp_be_end_paper (me_first_line_on_paper, me_curr_line_no);
		me_first_line_on_paper = me_curr_line_no + 1;
		me_curr_paper++;
		pp_be_new_paper (me_curr_paper);
		me_curr_page=0;
	} else {
		me_curr_page++;
	}
	pp_be_new_page (me_curr_page, me_file_page);

	pp_be_set_font (be_curr_font, 1);

	me_curr_row = 0;
	me_curr_col = 0;
}


/*
 *  pp_me_line_feed
 */
void pp_me_line_feed (int line_count_increment)
{
	me_curr_row++;

	if (me_curr_row >= me_rows_per_page) {
		pp_me_form_feed ();
	} else {
		me_curr_col = 0;
	}

	me_curr_line_no += line_count_increment;
}


/*
 *  pp_me_put
 */
void pp_me_put (__u_char *str)
{
	pp_be_put (str, me_curr_row, me_curr_col);
}


/*
 *  pp_me_line_num
 */
void pp_me_line_num ()
{
	if (me_print_line_nums && (me_curr_col == 0)) {
		pp_font_t	font_saved = be_curr_font;

		pp_be_set_font (Font_Line_Num, 1);
		pp_be_put_line_num (me_curr_line_no, me_curr_row);
		pp_be_set_font (font_saved, 1);

		me_curr_col = be_line_num_cols;
	}
}
