#define HEADER_FUNC "/HeaderDict 17 dict def\n" \
"HeaderDict begin\n" \
"	/hRlen 30 xmm def\n" \
"	/hRhht 15 ymm def\n" \
"	/hY %d ymm def    %% Note! Written by pp_be.c!\n" \
"	/hXmin %d xmm def %% again...\n" \
"	/hXmax %d xmm def %% and again...\n" \
"	/hRot  %d def     %% and again\n" \
"	/hXgap //hXmax //hXmin sub //hRlen 2 mul sub def\n" \
"\n" \
"	/filename_show {%% stack: (str) w x y ^\n" \
"		/oldmat matrix currentmatrix def\n" \
"			/tY exch def /tX exch def /tW exch def\n" \
"			dup stringwidth pop\n" \
"			/sL exch def /xscale tW sL div def\n" \
"			xscale 1 gt {\n" \
"				%% If xscale is ridicously high, change the\n" \
"				%% scale and the offset point\n" \
"				/xscale 1 def\n" \
"				/tX tX tW 2 div add sL 2 div sub def\n" \
"			} if\n" \
"			tX tY 2 ymm add translate\n" \
"			[ xscale 0 12 sin 1 0 0 ] concat\n" \
"			0 0 moveto DoShow\n" \
"		oldmat setmatrix\n" \
"	} def\n" \
"\n" \
"	/center_show {	%% stack: (str) x y ^\n" \
"		2 xmm add\n" \
"		3 -1 roll dup stringwidth pop 2 div	%% x new_y (str) len/2\n" \
"		4 -1 roll exch sub			%% new_y (str) new_x\n" \
"		3 -1 roll				%% (str) new_x new_y\n" \
"		moveto\n" \
"		/oldmat matrix currentmatrix def\n" \
"			[ 1 0 12 sin 1 0 0 ] concat\n" \
"			DoShow\n" \
"		oldmat setmatrix\n" \
"	} def\n" \
"\n" \
"	/left_show {  %%stack: (str) x y ^\n" \
"		0.5 ymm add exch 1 xmm add exch moveto\n" \
"		/oldmat matrix currentmatrix def\n" \
"			[ 1 0 12 sin 1 0 0 ] concat\n" \
"			DoShow\n" \
"		oldmat setmatrix\n" \
"	} def\n" \
"\n" \
"	/outline {\n" \
"		//hXmin //hY moveto\n" \
"		//hXmax //hXmin sub 0 rlineto\n" \
"		0 //hRhht rlineto\n" \
"		//hRlen 2 mul neg 0 rlineto\n" \
"		0 //hRhht 2 div neg rlineto\n" \
"		//hXgap //hRlen 2 mul sub neg 0 rlineto\n" \
"		0 //hRhht 2 div rlineto\n" \
"		//hRlen 2 mul neg 0 rlineto\n" \
"		closepath\n" \
"	} def\n" \
"\n" \
"	/DrawLine {\n" \
"		//hXgap setlinewidth\n" \
"		[ 0.5 xmm 0.5 ymm ] 0 setdash\n" \
"		//hXmax //hXmin sub 2 div //hXmin add //hY moveto\n" \
"		0 //hRhht 2 div rlineto\n" \
"		stroke\n" \
"	} def\n" \
"\n" \
"	/PutTexts {\n" \
"		FFile //hXgap 2 xmm sub\n" \
"		      //hXmin //hRlen add 1 xmm add //hY filename_show\n" \
"		FPage //hXmax //hRlen 2 div sub //hY center_show\n" \
"		FDaTi //hXmin //hRlen 2 div add //hY center_show\n" \
"		FDaTi //hXmin //hRlen 2 div add //hY //hRhht 2 div add center_show\n" \
"		FUser //hRlen\n" \
"		      //hXmax //hRlen 2 mul sub\n" \
"		      //hY //hRhht 2 div add filename_show\n" \
"	} def\n" \
"\n" \
"	/ShowHeader {\n" \
"		%% Stack: (h&u) (fdate) (time) (papernum) (fname)\n" \
"		gsave\n" \
"			//hRot rotate\n" \
"\n" \
"			0.95 setgray outline fill\n" \
"\n" \
"			0 setgray\n" \
"			dup 6 1 roll	%% Save filename below all strings\n" \
"			/DoShow {show} def PutTexts\n" \
"\n" \
"			0.8 setgray\n" \
"			DrawLine\n" \
"\n" \
"			/DoShow {false charpath clip newpath} def\n" \
"			FFile //hXmax //hXmin sub //hRlen 2 mul sub 2 xmm sub\n" \
"			      //hXmin //hRlen add 1 xmm add //hY filename_show\n" \
"\n" \
"			0.5 setgray\n" \
"			DrawLine\n" \
"		grestore\n" \
"	} def\n" \
"\n" \
"	/ShowLines {\n" \
"		%% Stack: (firstline) (lastline) ^\n" \
"		gsave\n" \
"			//hRot rotate\n" \
"			/DoShow {show} def\n" \
"			FPLin //hXmin //hRlen add //hY //hRhht 2 div add left_show\n" \
"			FPLin //hXmin //hRlen add //hY //hRhht 3 mul 4 div add left_show\n"\
"		grestore\n" \
"	} def\n" \
"end\n"
