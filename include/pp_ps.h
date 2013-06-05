#ifndef _PP_PS_H_
#define _PP_PS_H_

#define PROLOG		"%%!PS-Adobe-3.0\n" \
			"%%%%Title: pp output\n" \
			"%%%%Creator: %s\n" \
			"%%%%CreationDate: %s %s\n" \
			"%%%%DocumentFonts: Courier Courier-Bold Courier-Oblique Helvetica\n" \
			"%%%%EndComments\n" \
			"%%%%BeginProlog\n" \
			"/Put {moveto show} def\n" \
			"/mm { 2.835 mul } def\n" \
			"/xmm { 2.835 mul %6.6f mul } def\n" \
			"/ymm { 2.835 mul %6.6f mul } def\n"
#define	END_PROLOG	"%%%%EndProlog\n"

#define DOC_SETUP	"%%%%BeginSetup\n" \
			"/Courier-ISO /Courier MakeISOFont\n" \
			"/Courier-Bold-ISO /Courier-Bold MakeISOFont\n" \
			"/Courier-Oblique-ISO /Courier-Oblique MakeISOFont\n" \
			"/Courier-BoldOblique-ISO /Courier-BoldOblique MakeISOFont\n" \
			"/Helvetica-ISO /Helvetica MakeISOFont\n" \
			"/FPlain   {/Courier-ISO 10 selectfont} def\n" \
			"/FBold    {/Courier-Bold-ISO 10 selectfont} def\n" \
			"/FItalic  {/Courier-Oblique-ISO 10 selectfont} def\n" \
			"/FBoldItalic  {/Courier-BoldOblique-ISO 10 selectfont} def\n" \
			"/FLineNum {/Courier-Bold-ISO 8 selectfont} def\n" \
			"/FFile {/Helvetica-ISO  6 ymm selectfont} bind def\n" \
			"/FDaTi {/Helvetica-ISO  6 ymm selectfont} bind def\n" \
			"/FUser {/Helvetica-ISO  6 ymm selectfont} bind def\n" \
			"/FPage {/Helvetica-ISO 12 ymm selectfont} bind def\n" \
			"/FPLin {/Helvetica-ISO  3 ymm selectfont} bind def\n" \
			"%%%%EndSetup\n"

#define PAPERLINES_FUNC	"/PaperLines {0.12 setlinewidth %d rotate 0 %6.1f ymm translate\n"
#define PAPERLINES_BODY	"%6.4f xmm %6.4f ymm moveto %6.4f xmm %6.4f ymm lineto\n"
#define PAPERLINES_END	"stroke} def\n"

#define PAPERSETUP_BEGIN "%%%%Page: %d %d\n" \
			"%%%%BeginPageSetup\n" \
			"save\n"
#define HEADER_CALL	"HeaderDict begin\n" \
			"    (%s) (%s) (%s) (%d) (%s) ShowHeader\n" \
			"end\n"
#define PAPERLINES_CALL	"PaperLines\n"
#define PAPERSETUP_END	"restore\n" \
			"%%%%EndPageSetup\n"

#define ENDPAPER	"HeaderDict begin\n" \
					"  (First line: %d) (Last line: %d) ShowLines\n" \
					"end\n" \
					"showpage\n" \
					"%%%%EndPage\n"

#define NEWPAGE		"%% PageBreak\n" \
			"save\n" \
			"%d rotate %d xmm %d ymm translate %6.4f %6.4f scale\n"
#define DIGITS_CALL	"DigDict begin %6.4f mm %6.4f mm (%d) ShowNumber end\n"

#define ENDPAGE		"restore\n"

#define PUT_TEXT	"(%s) %6.4f mm %6.4f mm Put\n"
#define PUT_LINE_NUM	"(%6d:) 0 %6.4f mm Put\n"

#define SET_PLAIN	"FPlain\n"
#define SET_BOLD	"FBold\n"
#define SET_ITALIC	"FItalic\n"
#define SET_BOLDITALIC	"FBoldItalic\n"
#define SET_LINE_NUM	"FLineNum\n"

#define EPILOG		"%%%%Trailer\n"

#endif	/* _PP_PS_H_ */
