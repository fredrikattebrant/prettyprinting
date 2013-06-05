/*
 *  pp_be.h	PrettyPrinter Backend
 */

#ifndef _PP_BE_H_
#define _PP_BE_H_

typedef enum {
	Form_1P,	/*  1 page/paper  portrait	*/
	Form_1L,	/*  1 page/paper  landscape */
	Form_1Ps,	/*  1 page/paper, smaller text) portrait   */
	Form_1Ls,	/*  1 page/paper, smaller text) landscape  */
	Form_2P,	/*  2 pages/paper portrait  */
	Form_2L,	/*  2 pages/paper landscape */
	Form_4P,	/*  4 pages/paper portrait  */
	Form_4L,	/*  4 pages/paper landscape */
	Form_8P,	/*  8 pages/paper portrait  */
	Form_8L		/*  8 pages/paper landscape */
} pp_be_format_t;

typedef enum {
	A4,
	Letter
} pp_be_paper_size_t;

typedef enum {
	Font_Undef,
	Font_Plain,
	Font_Bold,
	Font_Italic,
	Font_BoldItalic,
	Font_Line_Num
} pp_font_t;

extern int be_line_num_cols;
extern int be_total_no_of_papers;
extern pp_font_t be_curr_font;

extern int be_use_gecos;

extern void pp_be_put_prolog (pp_be_format_t format,
			      pp_be_paper_size_t paper,
			      int *cols_per_row,
			      int *rows_per_page,
			      int *pages_per_paper);
extern void pp_be_put_epilog ();

extern void pp_be_set_new_file (char *name, char *date, char *time);

extern void pp_be_new_page  (int page_on_paper, int page_in_file);
extern void pp_be_new_paper (int paper_num);
extern void pp_be_end_paper (int first_line_on_paper, int last_line_on_paper);

extern void pp_be_put (__u_char *str, int row, int col);
extern void pp_be_put_line_num (int line_num, int row);

extern void pp_be_set_font  (pp_font_t font, int force);

extern void pp_be_list_sizes (pp_be_format_t chosen);

#endif	/* _PP_BE_H_ */
