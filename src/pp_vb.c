/*
 *
 *  pp_vb.c
 *
 */

#define EOS (char *)0
#define EOSC 0

static char	*reserved_words[] = {
	"abs", "access", "addressof", "alias", "and", "appactivate",
	"array", "as", "asc", "atn", "attribute",
	"base", "beep", "begin", "binary", "byref", "byval",
	"call", "callbyname", "case", "chdir", "chdrive", "choose", "chr",
	"class", "close", "command", "compare", "const", "cos", "createobject",
	"curdir", "cverr",
	"date", "dateadd", "datediff", "datepart", "dateserial", "datevalue", "day",
	"ddb", "declare", "defbool", "defbyte", "defint", "deflng", "defcur",
	"defsng", "defdbl", "defdec", "defdate", "defstr", "defobj", "defvar",
	"deletesetting", "dim", "dir", "do", "doevents",
	"each", "else", "elseif", "empty", "end", "enum", "environ", "eof",
	"eqv", "erase", "error", "event", "exit", "exp", "explicit",
	"false", "fileattr", "filecopy", "filedatetime", "filelen", "filter", "fix",
	"for", "format", "formatcurrency", "formatdatetime", "formatnumber",
	"formatpercent", "freefile", "fv", "friend", "function",
	"get", "getallsettings", "getattr", "getautoserversettings", "getobject",
	"getsetting", "gosub", "goto", "hex", "hour",
	"if", "iif", "imestatus", "imp", "implements", "in", "input", "inputbox",
	"instr", "instrrev", "int", "ipmt", "irr", "is", "isarray", "isdate",
	"isempty", "iserror", "ismissing", "isnull", "isnumeric", "isobject",
	"join", "kill",
	"lbound", "lcase", "left", "len", "let", "lib", "like", "line", "load",
	"loadpicture", "loadresdata", "loadrespicture", "loadresstring", "loc",
	"lock", "lof", "log", "loop", "lset", "ltrim",
	"me", "mid", "minute", "mirr", "mkdir", "mod", "module", "month",
	"monthname", "msgbox",
	"name", "new", "next", "not", "nothing", "now", "nper", "npv", "null",
	"oct", "on", "open", "option", "optional", "or",
	"paramarray", "partition", "pmt", "ppmt", "print", "private", "property",
	"public", "put", "pv",
	"qbcolor",
	"raiseevent", "randomize", "rate", "redim", "replace", "reset", "resume",
	"return", "rgb", "right", "rmdir", "rnd", "round",
	"rset", "rtrim",
	"savepicture", "savesetting", "second", "seek", "select", "sendkeys", "set",
	"setattr", "sgn", "shell", "sin", "sln", "space", "spc", "split", "sqr",
	"static", "step", "stop", "str", "strcomp", "strconv", "string",
	"strreverse", "sub", "switch", "syd",
	"tab", "tan", "then", "time", "timer", "timeserial", "timevalue", "to",
	"trim", "true", "type", "typename",
	"ubound", "ucase", "unload", "unlock", "until",
	"val", "vartype", "version",
	"weekday", "weekdayname", "wend", "while", "width", "with",
	"withevents", "write",
	"xor", "year",
	EOS
};

static char	*preprocessor_rw[] = {
	"const", "if", "elseif", "end",
	EOS
};


static char	lc_copy[4096];

/* Make a lower case copy */
static void cp_and_mk_lc (char *word)
{
	int	lc_ix = 0;

	do {
		lc_copy[lc_ix] = tolower(word[lc_ix]);
		lc_ix++;
	} while (word[lc_ix-1] != EOSC);
}

int is_vb_reserved_word (char *word)
{
	int 	ix = 0;
	char	*rw;
	int		rw_ix = 0;

	cp_and_mk_lc (word);

	/* Search in the list */
	while ((rw = reserved_words[rw_ix++]) != EOS) {
		if (strcmp (rw, lc_copy) == 0) {
			return (1);
		}
	}
	return (0);
}


int is_preprocessor_rw (char *word) 
{
	int 	ix = 0;
	char	*rw;
	int		rw_ix = 0;

	cp_and_mk_lc (word);

	/* Search in the list */
	while ((rw = preprocessor_rw[ix++]) != EOS) {
		if (strcmp (rw, lc_copy) == 0) {
			return (1);
		}
	}
	return (0);
}
