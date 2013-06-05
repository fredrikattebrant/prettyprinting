/*
 *
 * pp_idl.c
 *
 */

#define EOS (char *)0
#define EOSC 0

char	*reserved_words[] = {
	"allocate", "aggregatable", "appobject", "arrays", "async", "async_uuid",
	"auto_handle",

	"base_types", "bindable", "boolean", "broadcast", "byte", "byte_count",

	"call_as", "callback", "char", "coclass", "code", "comm_status", "const",
	"context_handle", "context_handle_noserialize", "context_handle_serialize",
	"control", "cpp_quote", "custom",

	"decode", "default", "defaultbind", "defaultcollelem", "defaultvalue",
	"defaultvtable", "dispinterface", "displaybind", "dllname", "double",
	"dual",

	"enable_allocate", "encode", "endpoint", "entry", "enum", "error_status_t",
	"explicit_handle",

	"fault_status", "field_attributes", "first_is", "float",

	"handle", "handles", "handle_t", "heap", "helpcontext", "helpfile",
	"helpstring", "helpstringdll", "hidden", "hyper",

	"id", "idempotent", "ignore", "iid_is", "immediatebind", "implicit_handle",
	"import", "importlib", "in", "include", "in_line", "int", "__int64",
	"interface",

	"last_is", "lcid", "length_is", "library", "licensed", "local", "long",

	"max_is", "maybe", "message", "midl_pragma_warning", "midl_user_allocate",
	"midl_user_free", "min_is", "module", "ms_union",

	"ncacn_at_dsp", "ncacn_dnet_nsp", "ncacn_http", "ncacn_ip_tcp",
	"ncacn_nb_ipx", "ncacn_nb_nb", "ncacn_nb_tcp", "ncacn_nb", "ncacn_spx",
	"ncacn_vns_spp", "ncadg_ip_udp", "ncadg_ipx", "ncadg_mq", "ncalrpc",
	"nocode", "nonbrowsable", "noncreatable", "nonextensible", "notify",

	"object", "odl", "oleautomation", "optimize", "optional", "out",
	"out_of_line",

	"pipe", "pointer_default", "pointers", "pragma", "propget", "propput",
	"propputref", "public", "ptr",

	"range", "readonly", "ref", "represent_as", "requestedit", "restricted",
	"retval",

	"shape", "short", "signed", "size_is", "small", "source",
	"strict_context_handle", "string", "struct", "switch", "switch_is",
	"switch_type",

	"transmit_as", "typedef",

	"union", "uidefault", "unique", "unsigned", "user_marshal",
	"usesgetlasterror", "uuid",

	"v1_enum", "vararg", "version", "void",

	"wchar_t", "wire_marshal",
	EOS
};

char    lc_copy[4096];
 
/* Make a lower case copy */
void cp_and_mk_lc (word)
        char    *word;
{
        int lc_ix = 0;
 
        do {
                lc_copy[lc_ix] = tolower(word[lc_ix]);
                lc_ix++;
        } while (word[lc_ix-1] != EOSC);
}
 
int is_idl_reserved_word (word)
        char    *word;
{
        char    *rw;
        int     rw_ix = 0;
 
        cp_and_mk_lc (word);
 
        /* Search in the list */
        while ((rw = reserved_words[rw_ix++]) != EOS) {
                if (strcmp (rw, lc_copy) == 0) {
                        return (1);
                }
        }
        return (0);
}
