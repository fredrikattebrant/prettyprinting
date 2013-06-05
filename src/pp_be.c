/*
 *  pp_be.c	PrettyPrinter Backend
 */

#include <unistd.h>
#include <stdio.h>
#include <pwd.h>

#include "pp_be.h"
#include "pp_ps.h"
#include "pp_ps_fonts.h"
#include "pp_ps_digits.h"
#include "pp_ps_header.h"

/*  "Exported" variables  */
int	be_line_num_cols = 8;
int	be_total_no_of_papers = 0;
int	be_use_gecos = 1;
pp_font_t	be_curr_font = Font_Undef;


/*  "Private" variables  */
static	char	file_name[BUFSIZ], file_date[BUFSIZ], file_time[BUFSIZ];
static	char	host_and_user[BUFSIZ];

static	struct	{
	int	pages_per_paper;
	int	rotation;	/* degree     */
	int	header_y;	/* millimeter */
	int	header_X;
	double	scale_x;	/* unitless   */
	double	scale_y;
	int	page_height;	/* scaled millimeters! */
	int	page_width;
	int	*next_page_x;	/* millimeter */
	int	*next_page_y;
	double	linestep;
} paper_desc;


/*
 *  This code is very table dependent...
 */
/*
 * linestep => 66 lines on 262 mm => for portrait papers
 * linestep => 46 lines on 175 mm => for landscape papers
 * charstep => 132 chars on 277 mm, always the same...
 */
#define	NROT_LINESTEP	262.0/66	/* 3.9697 mm/line */
#define ROTA_LINESTEP	175.0/46	/* 3.8043 mm/line */
#define CHARSTEP	277.0/132	/* 2.0985 mm/char */


static	int	cols_per_row_tab[] = {
	/* Form_1P  => */  80,		/* Form_1L  => */ 132,
	/* Form_1Ps => */ 132,		/* Form_1Ls => */ 204,
	/* Form_2P  => */  80, 	/* Form_2L  => */ 132,
	/* Form_4P  => */  80, 	/* Form_4L  => */ 132,
	/* Form_8P  => */  80, 	/* Form_8L  => */ 132
};

static	int	rows_per_page_tab[] = {
	/* Form_1P  => */  66,		/* Form_1L  => */  46,
	/* Form_1Ps => */ 109,		/* Form_1Ls => */  70,
	/* Form_2P  => */  66,		/* Form_2L  => */  46,
	/* Form_4P  => */  66,		/* Form_4L  => */  46,
	/* Form_8P  => */  66,		/* Form_8L  => */  46
};

static	int	pages_per_paper_tab[] = {
	/* Form_1P  => */   1,		/* Form_1L  => */   1,
	/* Form_1Ps => */   1,		/* Form_1Ls => */   1,
	/* Form_2P  => */   2,		/* Form_2L  => */   2,
	/* Form_4P  => */   4,		/* Form_4L  => */   4,
	/* Form_8P  => */   8,		/* Form_8L  => */   8
};

static	int	rotation_tab[] = {	/* Rotation in degrees */
	/* Form_1P  => */   0,		/* Form_1L  => */  90,
	/* Form_1Ps => */   0,		/* Form_1Ls => */  90,
	/* Form_2P  => */  90,		/* Form_2L  => */   0,
	/* Form_4P  => */   0,		/* Form_4L  => */  90,
	/* Form_8P  => */  90,		/* Form_8L  => */   0
};

static	int	header_y_tab[] = {	/* Header y pos, mm */
	/* Form_1P  => */ 273,		/* Form_1L  => */ -25,
	/* Form_1Ps => */ 273,		/* Form_1Ls => */ -25,
	/* Form_2P  => */ -25,		/* Form_2L  => */ 273,
	/* Form_4P  => */ 273,		/* Form_4L  => */ -25,
	/* Form_8P  => */ -25,		/* Form_8L  => */ 273
};

static	int	header_X_tab[] = {	/* Header X-max, mm */
	/* Form_1P  => */ 200,		/* Form_1L  => */ 287,
	/* Form_1Ps => */ 200,		/* Form_1Ls => */ 287,
	/* Form_2P  => */ 287,		/* Form_2L  => */ 200,
	/* Form_4P  => */ 200,		/* Form_4L  => */ 287,
	/* Form_8P  => */ 287,		/* Form_8L  => */ 200
};

static	int	physical_page_width_tab[] = {	/* Page widths, mm */
	/* Form_1P  => */ 180,		/* Form_1L  => */ 277,
	/* Form_1Ps => */ 180, 	/* Form_1Ls => */ 277,
	/* Form_2P  => */ 137, 	/* Form_2L  => */ 180,
	/* Form_4P  => */  89, 	/* Form_4L  => */ 137,
	/* Form_8P  => */  68, 	/* Form_8L  => */  89
};

static	int	physical_page_height_tab[] = {	/* Page heights, mm */
	/* Form_1P  => */ 262,		/* Form_1L  => */ 175,
	/* Form_1Ps => */ 262,		/* Form_1Ls => */ 175,
	/* Form_2P  => */ 175,		/* Form_2L  => */ 129,
	/* Form_4P  => */ 129,		/* Form_4L  => */  86,
	/* Form_8P  => */  86,		/* Form_8L  => */  64
};

static	int	page_width_tab[] = {	/* Page widths, scaled mm! */
	/* Form_1P  => */ 180,		/* Form_1L  => */ 277,
	/* Form_1Ps => */ 180*132/80,	/* Form_1Ls => */ 277*204/132,
	/* Form_2P  => */ 180,		/* Form_2L  => */ 277,
	/* Form_4P  => */ 180,		/* Form_4L  => */ 277,
	/* Form_8P  => */ 180,		/* Form_8L  => */ 277
};

static	int	page_height_tab[] = {	/* Page heights, scaled mm! */
	/* Form_1P  => */ 262,		/* Form_1L  => */ 175,
	/* Form_1Ps => */ 262*109/66-2,/* Form_1Ls => */ 175*70/46-2,
	/* Form_2P  => */ 262,		/* Form_2L  => */ 175,
	/* Form_4P  => */ 262, 	/* Form_4L  => */ 175,
	/* Form_8P  => */ 262,		/* Form_8L  => */ 175
};

static	double	scale_x_tab[] = {		/* Page x scale */
	/* Generally:
    physical_page_width_tab[this_form]/page_width_tab[Form_1(P|L)] */
	180.0/180.0,	277.0/277.0,
	180.0/297.0,	277.0/428.1,
	137.0/180.0,	180.0/277.0,
	 89.0/180.0,	137.0/277.0,
	 68.0/180.0,	 89.0/277.0
};

static	double	scale_y_tab[] = {		/* Page y scale */
	/* Generally:
   physical_page_height_tab[this_form]/page_height_tab[Form_1(P|L)] */
	1.0,		1.0,
	262.0/430.7,	175.0/264.3,
	175.0/262.0,	129.0/175.0,
	129.0/262.0,	 86.0/175.0,
	 86.0/262.0,	 64.0/175.0
};

static	int	F1P_x_pos_tab[] = {20};	/* Lists of x pos per page, mm */
static	int	F1L_x_pos_tab[] = {10};	/* Lists of x pos per page, mm */
static	int	F2P_x_pos_tab[] = {10, 149};
static	int	F2L_x_pos_tab[] = {20, 20};
static	int	F4P_x_pos_tab[] = {20, 20, 110, 110};
static	int	F4L_x_pos_tab[] = {10, 10, 149, 149};
static	int	F8P_x_pos_tab[] = {10, 10, 80, 80, 149, 149, 218, 218};
static	int	F8L_x_pos_tab[] = {20, 20, 20, 20, 110, 110, 110, 110};
static	int	*next_page_x_tab[] = {	/* Pointers to x pos tabs */
	F1P_x_pos_tab, F1L_x_pos_tab,
	F1P_x_pos_tab, F1L_x_pos_tab,
	F2P_x_pos_tab, F2L_x_pos_tab,
	F4P_x_pos_tab, F4L_x_pos_tab,
	F8P_x_pos_tab, F8L_x_pos_tab
};

static	int	F1P_y_pos_tab[] = {10}; /* Lists of y pos per page, mm */
static	int	F1L_y_pos_tab[] = {-200}; /* Lists of y pos per page, mm */
static	int	F2P_y_pos_tab[] = {-200, -200};
static	int	F2L_y_pos_tab[] = {143, 10};
static	int	F4P_y_pos_tab[] = {143, 10, 143, 10};
static	int	F4L_y_pos_tab[] = {-112, -200, -112, -200};
static	int	F8P_y_pos_tab[] = {-112, -200, -112, -200, -112,-200,-112,-200};
static	int	F8L_y_pos_tab[] = {208, 142, 76, 10, 208, 142, 76, 10};
static	int	*next_page_y_tab[] = {  /* Pointers to y pos tabs */
	F1P_y_pos_tab, F1L_y_pos_tab,
	F1P_y_pos_tab, F1L_y_pos_tab,
	F2P_y_pos_tab, F2L_y_pos_tab,
	F4P_y_pos_tab, F4L_y_pos_tab,
	F8P_y_pos_tab, F8L_y_pos_tab
};

static	double	linestep_tab[] = {
	NROT_LINESTEP,	ROTA_LINESTEP,
	NROT_LINESTEP,	ROTA_LINESTEP,
	NROT_LINESTEP,	ROTA_LINESTEP,
	NROT_LINESTEP,	ROTA_LINESTEP,
	NROT_LINESTEP,	ROTA_LINESTEP
};


/*  INTERNAL SUBPROGRAMS  */
#define DEBUG	0
#define TRACE(str) if (DEBUG) fprintf(stderr, "%s\n", str)

/*  EXPORTED SUBPROGRAMS  */

/*
 *  pp_be_put_prolog
 */
void pp_be_put_prolog (pp_be_format_t format,
		       pp_be_paper_size_t paper,
		       int *cols_per_row,
		       int *rows_per_page,
		       int *pages_per_paper)
{
	char	hostname[256];
	double	form_factor_x, form_factor_y;
	struct	passwd *pwdinfo;
	
TRACE("put_prolog");

	gethostname (hostname, 256);
	
	if ( !(pwdinfo = getpwuid(getuid())) == NULL) {
	    if (be_use_gecos) {
		strcpy (host_and_user, pwdinfo->pw_gecos);
	    } else {
	        strcpy (host_and_user, pwdinfo->pw_name);
	    }
	} else {
		fprintf(stderr, "Who the hell are you?\n");
	}
	strcat (host_and_user, "@");
	strcat (host_and_user, hostname);

	*cols_per_row    = cols_per_row_tab    [format];
	*rows_per_page   = rows_per_page_tab   [format];
	*pages_per_paper = pages_per_paper_tab [format];

	if (paper == A4) {	/* default */
		form_factor_x = form_factor_y = 1.0;
	} else {		/* Letter */
		if (rotation_tab[format] == 0) { /* Paper is portrait */
			form_factor_x =  8.5 * 25.4 / 210.0;
			form_factor_y = 11.0 * 25.4 / 297.0;
		} else {			 /* Paper is landscape */
			form_factor_x = 11.0 * 25.4 / 297.0;
			form_factor_y =  8.5 * 25.4 / 210.0;
		}
	}

	paper_desc.pages_per_paper = pages_per_paper_tab [format];
	paper_desc.header_y	= header_y_tab    [format];
	paper_desc.header_X	= header_X_tab    [format];
	paper_desc.rotation	= rotation_tab    [format];
	paper_desc.scale_x	= scale_x_tab     [format] * form_factor_x;
	paper_desc.scale_y	= scale_y_tab     [format] * form_factor_y;
	paper_desc.page_height	= page_height_tab [format];
	paper_desc.page_width 	= page_width_tab  [format];
	paper_desc.next_page_x	= next_page_x_tab [format];
	paper_desc.next_page_y	= next_page_y_tab [format];
	paper_desc.linestep	= linestep_tab	  [format];

	printf (PROLOG,
		host_and_user,
		file_date,
		file_time,
		form_factor_x,
		form_factor_y);
	printf (PUT_FONTS);

	printf (HEADER_FUNC,
		paper_desc.header_y,	/* Header's lower Y coord */
		paper_desc.next_page_x[0], /* Header's left X coord */
		paper_desc.header_X,
		paper_desc.rotation);	/* Rotate paper? */
	printf (DIGITS_FUNC);

	printf (PAPERLINES_FUNC, paper_desc.rotation,
		paper_desc.rotation == 0 ? 0 : -210.0);
	switch (format) {
		case Form_1P:
		case Form_1L:
		case Form_1Ps:
		case Form_1Ls:
			break;	/* No lines needed */
		case Form_2P:
			printf (PAPERLINES_BODY, 148.5, 10.0, 148.5, 185.0);
			/*printf (PAPERLINES_BODY, 25.0, 148.5, 200.0, 148.5);*/
			break;
		case Form_2L:
			printf (PAPERLINES_BODY, 20.0, 141.0, 200.0, 141.0);
			break;
		case Form_4P:
			printf (PAPERLINES_BODY, 20.0, 141.0, 200.0, 141.0);
			printf (PAPERLINES_BODY, 109.0, 10.0, 109.0, 273.0);
			break;
		case Form_4L:
			printf (PAPERLINES_BODY, 10.0, 96.5, 287.0, 96.5);
			printf (PAPERLINES_BODY, 148.5, 10.0, 148.5, 185.0);

/*			printf (PAPERLINES_BODY, 113.5, 10.0, 113.5, 287.0);
			printf (PAPERLINES_BODY, 25.0, 148.0, 200.0, 148.0);
*/			break;
		case Form_8P:
			printf (PAPERLINES_BODY,  10.0, 96.5, 287.0,  96.5);
			printf (PAPERLINES_BODY,  79.0, 10.0, 79.0,  185.0);
			printf (PAPERLINES_BODY, 148.5, 10.0, 148.5, 185.0);
			printf (PAPERLINES_BODY, 217.0, 10.0, 217.0, 185.0);

/*			printf (PAPERLINES_BODY, 113.5, 10.0, 113.5, 287.0);
			printf (PAPERLINES_BODY, 25.0,  79.0, 200.0, 79.0);
			printf (PAPERLINES_BODY, 25.0, 148.5, 200.0, 148.5);
			printf (PAPERLINES_BODY, 25.0, 217.0, 200.0, 217.0);
*/			break;
		case Form_8L:
			printf (PAPERLINES_BODY, 109.3, 10.0, 109.3, 273.0);
			printf (PAPERLINES_BODY,  20.0, 74.5, 200.0,  74.5);
			printf (PAPERLINES_BODY,  20.0, 141.0, 200.0, 141.0);
			printf (PAPERLINES_BODY,  20.0, 206.5, 200.0, 206.5);
			break;
	}
	printf (PAPERLINES_END);

	printf (END_PROLOG);
	printf (DOC_SETUP);
}


/*
 *  pp_be_put_epilog
 */
void pp_be_put_epilog ()
{
TRACE("put_epilog");
	printf (EPILOG);
}


/*
 *  pp_be_set_new_file
 */
void pp_be_set_new_file (char *name, char *date, char *time)
{
TRACE("set_new_file");
	strcpy (file_name, name);
	strcpy (file_date, date);
	strcpy (file_time, time);
}


/*
 *  pp_be_new_paper
 */
void pp_be_new_paper (int paper_num)
{
TRACE("new_paper");

	/* Add a header for the new page */
	printf (PAPERSETUP_BEGIN, paper_num, ++be_total_no_of_papers);

	printf (HEADER_CALL,
			host_and_user, file_date, file_time, paper_num, file_name);

	printf (PAPERLINES_CALL);
	printf (PAPERSETUP_END);
}


/*
 *  pp_be_end_paper
 */
void pp_be_end_paper (int first_line_on_paper, int last_line_on_paper)
{
TRACE("end_paper");

	printf (ENDPAPER, first_line_on_paper, last_line_on_paper);
}


/*
 *  pp_be_new_page
 */
void pp_be_new_page  (int page_on_paper, int page_in_file)
{
TRACE("new_page");

	printf (NEWPAGE,
		/* rotate */ paper_desc.rotation,
		/* offs x */ paper_desc.next_page_x[page_on_paper],
		/* offs y */ paper_desc.next_page_y[page_on_paper],
		/* scalex */ paper_desc.scale_x,
		/* scaley */ paper_desc.scale_y);

	if (paper_desc.pages_per_paper > 1)
		printf (DIGITS_CALL,
			paper_desc.page_width/2.0,
			paper_desc.page_height/2.0,
			page_in_file);

	pp_be_set_font (be_curr_font, 1);
}


/*
 *  pp_be_end_page
 */
void pp_be_end_page ()
{
TRACE("end_page");

	printf (ENDPAGE);
}


/*
 *  pp_be_put
 */
void pp_be_put (__u_char *str, int row, int col)
{
TRACE("put_text");

	printf (PUT_TEXT,
		str,
		col * CHARSTEP,
		paper_desc.page_height - (row + 1) * paper_desc.linestep);
}


/*
 *  pp_be_put_line_num
 */
void pp_be_put_line_num (int line_num, int row)
{
TRACE("put_line_num");

	printf (PUT_LINE_NUM,
		line_num,
		paper_desc.page_height - (row + 1) * paper_desc.linestep);
}


/*
 *  pp_be_set_font
 */
void pp_be_set_font (pp_font_t font, int force)
{
TRACE("set_font");
	if ((be_curr_font != font) || (force == 1)) {
		switch (font) {
			case Font_Plain:
				printf (SET_PLAIN);
				be_curr_font = Font_Plain;
				break;
			case Font_Bold:
				printf (SET_BOLD);
				be_curr_font = Font_Bold;
				break;
			case Font_Italic:
				printf (SET_ITALIC);
				be_curr_font = Font_Italic;
				break;
			case Font_BoldItalic:
				printf (SET_BOLDITALIC);
				be_curr_font = Font_BoldItalic;
				break;
			case Font_Line_Num:
				printf (SET_LINE_NUM);
				be_curr_font = Font_Line_Num;
				break;
			default:
				break;
		}
	}
}


static	char	head_line[] =
  "Pages/Paper       switch    cols/row  rows/page   rows/paper\n";
static	char	*format_names_tab[] = {
  "1  Portrait         -1p          %3d        %3d         %4d",
  "1  Landscape        -1l          %3d        %3d         %4d",
  "1  Portrait  small  -1ps         %3d        %3d         %4d",
  "1  Landscape small  -1ls         %3d        %3d         %4d",
  "2  Portrait         -2p          %3d        %3d         %4d",
  "2  Landscape        -2l          %3d        %3d         %4d",
  "4  Portrait         -4p          %3d        %3d         %4d",
  "4  Landscape        -4l          %3d        %3d         %4d",
  "8  Portrait         -8p          %3d        %3d         %4d",
  "8  Landscape        -8l          %3d        %3d         %4d",
};

/*
 *  pp_be_list_sizes
 */
void pp_be_list_sizes (pp_be_format_t chosen)
{
	pp_be_format_t	f;

	fprintf (stderr, head_line);
	for (f = Form_1P; f <= Form_8L; f++) {
		fprintf (stderr, format_names_tab[f],
			 cols_per_row_tab [f],
			 rows_per_page_tab[f],
			 rows_per_page_tab[f] * pages_per_paper_tab[f]);
		if (f == chosen) {
			fprintf (stderr, " %s\n", "*");
		} else {
			fprintf (stderr, "\n");
		}
	}
}
