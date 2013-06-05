#define DIGITS_FUNC "%% Define background digits\n" \
"/DigDict 17 dict def	%% The Digit dictionary\n" \
"DigDict begin\n" \
"/Hht 60 ymm def		%% Text height\n" \
"/BL Hht 2 mul 5 div def	%% The basic unit - the horizontal char width\n" \
"/Angle 12 def		%% Skew angle\n" \
"/BW BL 2 div def	%% BarWidth\n" \
"/IW BW 2 div def	%% Width of the inner white char\n" \
"/BS BL BW 1.1 mul add def	%% Space between chars\n" \
"/Skew {[ 1 0 Angle sin 1 0 0 ] concat} def\n" \
"\n" \
"%% draw right, left, up, down	%% move right, left, up, down\n" \
"/R {//BL 0     rlineto} def	/mR {//BL 0     rmoveto} def\n" \
"/L {//BL neg 0 rlineto} def	/mL {//BL neg 0 rmoveto} def\n" \
"/U {0 //BL     rlineto} def	/mU {0 //BL     rmoveto} def\n" \
"/D {0 //BL neg rlineto} def	/mD {0 //BL neg rmoveto} def\n" \
"\n" \
"%% Space saving macros\n" \
"/DInit {gsave Skew 0.95 setgray} def\n" \
"/DTail {gsave stroke grestore IW setlinewidth 1 setgray stroke grestore} def\n" \
"\n" \
"/ShowNumber {	%% x y (string) ShowNumber\n" \
"	gsave\n" \
"	3 1 roll moveto	%% Set (x,y)\n" \
"	dup		%% We use the string twice\n" \
"\n" \
"	//BW setlinewidth\n" \
"	1 setlinejoin		%% Rounded corners\n" \
"	1 setlinecap		%% Rounded ends\n" \
"\n" \
"	%% TotLen:=(BW+2*BL)*sin(Angle)-2*BW + shownLength(string)\n" \
"	/TotLen Angle sin BL 2 mul BW add mul BW 2 mul sub def\n" \
"	{ 48 sub 1 eq { /TotLen TotLen BL sub def } if	%% '1' is shorter\n" \
"		/TotLen TotLen BS add def\n" \
"	} forall\n" \
"\n" \
"	%% Offcenter to show text centered, both horiz and vert.\n" \
"	TotLen 2 div neg BL Angle cos mul neg rmoveto\n" \
"	{48 sub	%% ASCII -> Number\n" \
"		dup 0 eq { DInit R U U L D D      DTail BS 0 rmoveto } if\n" \
"		dup 1 eq { DInit U U       DTail BS BL sub 0 rmoveto } if\n" \
"		dup 2 eq { DInit mR L U R U L     DTail BS 0 rmoveto } if\n" \
"		dup 3 eq { DInit R U U L mR mD L  DTail BS 0 rmoveto } if\n" \
"		dup 4 eq { DInit mR U U mD L U    DTail BS 0 rmoveto } if\n" \
"		dup 5 eq { DInit R U L U R        DTail BS 0 rmoveto } if\n" \
"		dup 6 eq { DInit mU R D L U U R   DTail BS 0 rmoveto } if\n" \
"		dup 7 eq { DInit mR U U L         DTail BS 0 rmoveto } if\n" \
"		dup 8 eq { DInit R U U L D D mU R DTail BS 0 rmoveto } if\n" \
"		    9 eq { DInit R U U L D R      DTail BS 0 rmoveto } if\n" \
"	} forall	%%  Loop over the string\n" \
"	grestore\n" \
"} def\n" \
"\n" \
"end %% DigDict\n"
