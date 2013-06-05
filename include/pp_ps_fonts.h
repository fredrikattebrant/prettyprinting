#define PUT_FONTS /* Set ISO encoding for all used fonts */ \
"/MakeISOFont {\n" \
"    ISOLatin1Encoding 3 1 roll\n" \
"    findfont begin\n" \
"	currentdict dup length dict begin\n" \
"	    {1 index /FID ne {def} {pop pop} ifelse } forall\n" \
"	    /FontName exch def\n" \
"	    dup length 0 ne {\n" \
"		/Encoding Encoding 256 array copy def\n" \
"		0 exch {\n" \
"		    dup type /nametype eq {\n" \
"			Encoding 2 index 2 index put\n" \
"			pop 1 add\n" \
"		    }{\n" \
"			exch pop\n" \
"		    } ifelse\n" \
"		} forall\n" \
"	    } if\n" \
"	    currentdict dup\n" \
"	end\n" \
"    end\n" \
"    /FontName get exch definefont pop pop\n" \
"} bind def\n" \
"\n"
