/*
 *  pp_me.h	PrettyPrinter Midend
 */

#ifndef _PP_ME_H_
#define _PP_ME_H_

extern void pp_main   (int argc, char **argv);
extern int  pp_yywrap ();

extern void pp_me_line_feed (int line_count_increment);
extern void pp_me_form_feed ();
extern void pp_me_put	    (__u_char *str);
extern void pp_me_line_num  ();

extern	int	me_cols_per_row, me_tab;
extern	int	me_curr_col, me_broken_lines;

#endif	/* _PP_ME_H_ */
