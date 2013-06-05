/*
 *
 * pp_ada.c
 *
 */

#define EOS  (char *)0
#define EOSC 0
#define PRAGMA "pragma"
#define PAGE   "page"

char	*reserved_words[] = {
	"abort","abs","abstract","accept","access","aliased","all","and",
	"array","at","begin","body","case","constant","declare","delay",
	"delta","digits","do","else","elsif","end","entry","exception",
	"exit","for","function","generic","goto","if","in","is","limited",
	"loop","mod","new","not","null","of","or","others","out","package",
	PRAGMA,"private","procedure","protected","raise","range","record",
	"rem","renames","requeue","return","reverse","select","separate",
	"subtype","tagged","task","terminate","then","type","until","use",
	"when","while","with","xor",
	EOS
};

char	lc_copy[4096];

/* Make a lower case copy */
void cp_and_mk_lc (word)
	char	*word;
{
	int lc_ix = 0;

	do {
		lc_copy[lc_ix] = tolower(word[lc_ix]);
		lc_ix++;
	} while (word[lc_ix-1] != EOSC);
}

int is_ada_reserved_word (word)
	char	*word;
{
	char	*rw;
	int	rw_ix = 0;

	cp_and_mk_lc (word);

	/* Search in the list */
	while ((rw = reserved_words[rw_ix++]) != EOS) {
		if (strcmp (rw, lc_copy) == 0) {
			return (1);
		}
	}
	return (0);
}

int is_pragma (word)
	char	*word;
{
	cp_and_mk_lc (word);

	return (strcmp (PRAGMA, lc_copy) == 0 ? 1 : 0);
}

int is_page (word)
	char	*word;
{
	cp_and_mk_lc (word);

	return (strcmp (PAGE, lc_copy) == 0 ? 1 : 0);
}
