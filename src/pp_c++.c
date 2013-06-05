/*
 *
 * pp_c++.c
 *
 */

#define EOS (char *)0

char	*reserved_words[] = {
	/* ANSI C */
	"auto","break","case","char","const","continue","default","do",
	"double","else","enum","extern","float","for","goto","if","int",
	"long","main","register","return","short","signed","sizeof",
	"static","struct",
	"switch","typedef","union","unsigned","void","volatile","while",

	/* C++ */
	"catch","class","delete","friend","inline","new","operator",
	"private","protected","public","template","this","throw","try",
	"virtual","wchar_t",
	EOS
};

char	*preprocessor_rw[] = {
	"define","ifdef","ifndef","elif","endif","undef","include",
	"line","error",
	EOS
};

int is_cpp_reserved_word (word)
	char	*word;
{
	int	ix = 0;

	char	*rw;
	int	rw_ix = 0;

	/* Case sensitive. Don't make it lower case. */

	/* Search in the list */
	while ((rw = reserved_words[ix++]) != EOS) {
		if (strcmp (rw, word) == 0) {
			return (1);
		}
	}
	return (0);
}

int is_cpp_preprocessor_rw (word)
	char	*word;
{
	int	ix = 0;

	char	*rw;
	int	rw_ix = 0;

	/* Case sensitive. Don't make it lower case. */

	/* Search in the list */
	while ((rw = preprocessor_rw[ix++]) != EOS) {
		if (strcmp (rw, word) == 0) {
			return (1);
		}
	}
	return (0);
}
