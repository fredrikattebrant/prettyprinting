/*
 *  pp_fe.c	PrettyPrinter Frontend
 */

#include <unistd.h>
#include <stdio.h>

#include "pp_me.h"
#include "pp_be.h"


static	__u_char	part_to_put[BUFSIZ * 2];
static	__u_char	string_to_put[BUFSIZ * 2];

static	__u_char	*pp_fe_held_ws = NULL;


/*  INTERNAL SUBPROGRAMS  */

/*
 *  pp_fe_esc_parentheses
 */
static void pp_fe_esc_parentheses (__u_char *target, __u_char *source, int length)
{
	int	ix, ox, oct_len;

	for (ix = ox = 0; ix < length; ix++) {
		/* Add a backslash for parentheses and backslashes */
		if ((source[ix] == '(') ||
		    (source[ix] == ')') ||
		    (source[ix] == '\\')) {
			target[ox++] = '\\';
			target[ox++] = source[ix];

		} else if (source[ix] > 160 ) {
			target[ox++] = '\\';
			sprintf ((char *)&target[ox], "%o%n", source[ix], &oct_len);
			ox+=oct_len;

		/* Other printable characters are passed as is */
		} else {
			target[ox++] = source[ix];
		}
	}
	target[ox] = '\0';
}


/*
 *  pp_fe_esc_ctrl_chars
 */
static __u_char *pp_fe_esc_ctrl_chars (__u_char *src, __u_char *trg)
{
	int	length = strlen (src);
	int	ix, ox;
	int	trg_col = me_curr_col;
	int	new_trg_col, tmp;

	for (ix = ox = 0; ix < length; ix++) {
		if (src[ix] == '\t') {
			new_trg_col = (trg_col / me_tab) * me_tab + me_tab;
			for (tmp = trg_col + 1; tmp <= new_trg_col; tmp++)
				trg[ox++] = ' ';
			trg_col = new_trg_col;
		} else if (src[ix] < ' ') {
			trg[ox++] = '^';
			trg[ox++] = src[ix] + '@';
			trg_col += 2;
		 } else if ((src[ix] >= 127) &&
			    (src[ix] <= 160)) {
			trg[ox++] = 'M';
			trg[ox++] = '-';
			trg[ox++] = '^';
			trg[ox++] = src[ix] - '@';
			trg_col += 4;
		} else {
			trg[ox++] = src[ix];
			trg_col += 1;
		}
	}
	trg[ox] = '\0';

	return (trg);
}


/*
 *  pp_fe_put
 */
static void pp_fe_put (__u_char *str)
{
	__u_char	*str_cp = pp_fe_esc_ctrl_chars (str, &string_to_put[0]);
	int	length = strlen (str_cp);
	int	part_length;

	/* Split long lines and print parts */
	while ((me_curr_col + length) > me_cols_per_row) {
		part_length = me_cols_per_row - me_curr_col;
		/* copy "part_length" bytes from "str_cp" to "part_to_put",
		   and escape parentheses */
		pp_fe_esc_parentheses (part_to_put, str_cp, part_length);

		pp_me_put (part_to_put);
		pp_me_line_feed (0); /*  Don't increase line number! */
		me_broken_lines++;
		length -= part_length;
		str_cp += part_length;
	}

	/* Print the end of the string */
	pp_fe_esc_parentheses (part_to_put, str_cp, length);
	pp_me_put (part_to_put);
	me_curr_col += length;
}


/*
 *  pp_fe_put_held_white_space
 */
void pp_fe_put_held_white_space ()
{
	int	ix, length;

	if (!pp_fe_held_ws)
		return;

	length = strlen (pp_fe_held_ws);

	for (ix = 0; ix < length; ix++) {
		pp_me_line_num ();
		switch (pp_fe_held_ws[ix]) {
			case ' ':
				if (me_curr_col == me_cols_per_row) {
					pp_me_line_feed (0);
					me_broken_lines++;
				}
				me_curr_col++;
				break;
			case '\t':
				me_curr_col =
				    (me_curr_col / me_tab) * me_tab + me_tab;
				if (me_curr_col >= me_cols_per_row) {
					int col_save = me_curr_col;
					pp_me_line_feed (0);
					me_broken_lines++;
					me_curr_col=col_save-me_cols_per_row;
				}
				break;
			case '\n':
				pp_me_line_feed (1);
				break;
			case '\f':
				pp_me_form_feed ();
				break;
			default:
				break;
		}
	}

	free (pp_fe_held_ws);
	pp_fe_held_ws = NULL;
}


/*  EXPORTED SUBPROGRAMS  */

/*
 *  pp_fe_white_space
 */
void pp_fe_white_space (__u_char *ws)
{
	/*
	 *  We don't want to print trailing white space: It may
	 *  cost blank papers, so we save the data until we must print it
	 *  (when true text is printed).
	 */
	if (pp_fe_held_ws) {
		int new_len = (strlen (pp_fe_held_ws) + strlen (ws) + 1);
		__u_char *tmp = (__u_char *) malloc (new_len);
		strcpy (tmp, pp_fe_held_ws);
		strcat (tmp, ws);
		free (pp_fe_held_ws);
		pp_fe_held_ws = tmp;
	} else {
		pp_fe_held_ws = (__u_char *) malloc (strlen (ws) + 1);
		strcpy (pp_fe_held_ws, ws);
	}
}


/*
 *  pp_fe_italic
 */
void pp_fe_italic (__u_char *str)
{
	pp_fe_put_held_white_space ();
	pp_me_line_num ();
	pp_be_set_font (Font_Italic, 0);
	pp_fe_put (str);
}


/*
 * pp_fe_bold
 */
void pp_fe_bold (__u_char *str)
{
	pp_fe_put_held_white_space ();
	pp_me_line_num ();
	pp_be_set_font (Font_Bold, 0);
	pp_fe_put (str);
}


/*
 * pp_fe_bolditalic
 */
void pp_fe_bolditalic (__u_char *str)
{
	pp_fe_put_held_white_space ();
	pp_me_line_num ();
	pp_be_set_font (Font_BoldItalic, 0);
	pp_fe_put (str);
}


/*
 *  pp_fe_plain
 */
void pp_fe_plain (__u_char *str)
{
	pp_fe_put_held_white_space ();
	pp_me_line_num ();
	pp_be_set_font (Font_Plain, 0);
	pp_fe_put (str);
}
