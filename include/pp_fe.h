/*
 *  pp_fe.c	PrettyPrinter Frontend
 */

#ifndef _PP_FE_H_
#define _PP_FE_H_
#include <sys/types.h>

extern void pp_fe_white_space	(u_char *);
extern void pp_fe_italic		(u_char *);
extern void pp_fe_bold			(u_char *);
extern void pp_fe_bolditalic	(u_char *);
extern void pp_fe_plain			(u_char *);

#endif	/* _PP_FE_H_ */
