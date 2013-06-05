/*
 *
 * pp_java.c
 *
 */

#define EOS (char *)0

char	*reserved_words[] = {
	"abstract", "boolean", "break", "byte", "case", "cast", "catch", 
	"char", "class", "const", "continue", "default", "do", "double", 
	"else", "extends", "final", "finally", "float", "for", "future",
	"generic", "goto", "if", "implements", "import", "inner",
	"instanceof", "int", "interface", "long", "native", "new", "null",
	"operator", "outer", "package", "private", "protected", "public",
	"rest", "return", "short", "static", "super", "switch", "synchronized",
	"this", "throw", "throws", "transient", "try", "var", "void",
	"volatile", "while",
	EOS
};

int is_java_reserved_word (word)
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

int is_java_preprocessor_word (word)
        char    *word;
{
	return (0);
}
