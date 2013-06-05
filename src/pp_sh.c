/*
 *
 * pp_sh.c
 *
 */

#define EOS (char *)0

char	*reserved_words[] = {
"CTSmake", "CTSrevert","CTSset_latest","CTSset_version","CTSset_view_version",
"GLcmap","Links","Mail","Rsh","acctcom","acledit","aclget","aclput","ada",
"ada6000_sync","adb","addX11input","addbib","adfutil","admin","afe","aixims",
"aixterm","aixwm","ali","anno","apex","apexinit","apexrc","apply","appres",
"apropos","ar","arcv","as","asa","at","ate","atobm","atq","atrm","autostart",
"awk","axeb","b2m","banner","basename","bash","batch","bc","bdftopcf",
"bdftosnf","bdiff","bellmail","bfs","biff","bison","bitmap","bmtoa","bootlist",
"bosboot","bs","bsh","build","build_creation_date_file","burst","c++","c89",
"cal","calendar","cancel","captoinfo","capture","cat","cb","cc","cdc",
"cflow","chcolor","chcursor","chdisp","check_release_status",
"checkcw","checkeq","checkmm","checkmm1","checknr","chfn","chfont","chgPcon",
"chgroup","chgrp","chgrpmem","chhwkbd","chie","chiin","chkbd","chkey","chkeymap",
"chlang","chlicense","chmod","chnamsv","chnumvt","chown","chprtsv","chque",
"chquedev","chrctcp","chroot","chserver","chsh","chsound","chssys","chtz",
"chuser","cksum","cleandir","clear","cmp","col","colcrt","collect_c_archives",
"collect_secondary","colrm","comb","comm","comp","compress","confer","connect",
"copy","cp","cpdir","cpio","create_release_notes","create_secondary","cronadm",
"crontab","csh","csplit","ct","ctags","cu","custom","cut","cvtgdf","cw","cxref",
"date","dbx","dc","dd","del","delete","deleteX11input","delete_secondary",
"delta","demodr","demomon","deroff","df","di","diction","diff","diff3",
"diffmk","dircmp","dirname","disable","diskusg","dist","domainname","dosdel",
"dosdir","dosformat","dosread","doswrite","dprog","dspcat","dspmsg","du",
"dump","dwa.exp","dynamic_ext","e","ebxa","echo","ecs","ecsrf","ed","edit",
"edit_secondary","editres","edquota","egrep","emacs","emacsclient","enable",
"enq","enroll","enscript","env","eqn","errclear","errinstall","errlogger",
"errmsg","errpt","errsql","errupdate","etags","ex","excoterm","exer","expand",
"explain","expr","f","factor","false","fdformat","ff","ffill","fformat","fgrep",
"file","filemon","fileplace","fill","filter_out_mains","find",
"find_imported_c_archives","find_imports","find_target_library","finger",
"fjust","fmt","fold","folder","folders","fontutil","format","forw","fpr","from",
"fs","fsconf","fsinfo","fslsfonts","fsplit","fstobdf","ftp","g++","gPafut",
"gPgated","gPhost","gPinit","gPq","gPterm","gPtutor","gai.exp","gcc","gencat",
"genclass","genkex","genkld","genld","genxlt","get","get_view","getconf",
"getopt","ghost","gm","gnatbind","gnatbl","gnatchop","gnatchp","gnatf","gnatk8",
"gperf","gprof","graf","grap","graph","graphics","greek","grep","groups",
"grpck","gunzip","gzexe","gzip","hc","head","help","history","host","hostent",
"hostid","hostname","housekeep","hp","hplj","hyphen","ibm3812","ibm3816",
"ibm5587G","iconv","id","iebase","inc","indent","indxbib","inetexp","inetimp",
"inetserv","info","infohelp","inst_updt","install","iostat","ipcrm","ipcs",
"ipreport","iptrace","istat","join","joinconf","just","keycomp","keylogin",
"keymaps","kill","killall","ksh","last","lastcomm","ld","learn","leave","lex",
"li","line","lint","list4tar","listX11input","listres","ln","loadAbx",
"loadDWA","loadMbx","loadPex","loadavgd","locale","localedef","lock","logger",
"login","logname","logout","look","lookbib","lorder","lp","lppchk","lpq","lpr",
"lprm","lpstat","lptest","ls","ls6098","lsadpnm","lsallq","lsallqdev","lscolor",
"lsdisp","lsfont","lsgPcon","lsgPlvl","lsgroup","lsie","lsiin","lskbd","lslicense",
"lslpp","lsnamsv","lsprtsv","lsque","lsquedev","lsscreen","lssrc","lsuser",
"lvedit","m4","macref","mail","mailq","mailx","make","make_paired_view",
"makedev","makekey","man","mant","mark","mesg","mfyi","mgti","mhmail","mhpath",
"mkcatdefs","mkdir","mkfifo","mkfont","mkfontdir","mkgPcon","mkgroup","mkkbd",
"mknamsv","mknotify","mkprtsv","mkque","mkquedev","mkserver","mkssys","mkstr",
"mksysb","mkszfile","mktcpip","mkuser","mlock","mm","mmt","monitor","more",
"move","move_target_dir","msgchk","msgs","msh","msmit","mt","mv","mvt","mwm",
"mxdw","myni","namerslv","ndx","neqn","netpmon","netstat","newaliases",
"newfile","newform","newgrp","news","next","nice","nl","nm","nohup","notinet",
"nroff","nslookup","nvload","obsolete_paired_view","oclock","od","odmadd",
"odmchange","odmcreate","odmdelete","odmdrop","odme","odmget","odmshow",
"on","onena","only_move_target_dir","only_update_secondary","only_update_vc_control",
"open","oslevel","pac","pack","packf","page","pagesize","panel20","passwd",
"paste","patch","pathchk","pax","pcat","pcfsnfdir","pcftobdf","pg","pic","pick",
"pixed","post_accept","pr","prev","printenv","printf","prof","proff","prompter",
"protoize","prs","prtty","ps","ps4014","ps630","psc","psdit","psplot","psrev",
"psroff","ptx","pwd","pwdadm","pwdck","qadm","qcan","qchk","qpri","qprt",
"querykbd","quot","quota","quotacheck","quotaoff","quotaon","r1000_to_apex",
"ranlib","rcp","rcs-checkin","rdist","readfile","red","refer","refile",
"refresh","regcmp","remsh","repl","repquota","reset","resize","rev","rexec",
"rgb","rlogin","rm","rmail","rmap","rmdel","rmdir","rmf","rmgroup","rmhist",
"rmm","rmnamsv","rmnotify","rmprtsv","rmque","rmquedev","rmserver","rmss",
"rmssys","rmuser","roffbib","rpcgen","rpcinfo","rpl","rsh","runcat","rup",
"ruptime","ruser","rusers","rwho","sact","sag","sar","scan","sccs","sccsdiff",
"sccshelp","script","sdiff","sed","send","sendbug","setclock","setgroups",
"setmaps","setsenv","sh","shell","show","showfont","showmount","showrgb",
"showsnf","size","sleep","smit","smitty","sno","soelim","sort","sortbib",
"sortm","spell","spellin","spellout","spline","split","splp","startsrc",
"startx","static_ext","stinet","stopsrc","strace","strclean","strerr",
"strings","strip","stripnm","struct","stty","style","su","subj","subsystemname_of",
"sum","svmon","swkbd","sync","syscall","sysck","sysdumpdev","sysdumpstart",
"sysline","ta","tab","tabs","tail","talk","tar","tar_apex","tbl","tc","tcbck",
"tcopy","tctl","tdigest","te","tee","tellxdt3","telnet","termdef","test",
"tftp","tic","time","timex","tip","tk_mount","tk_mount.ksh","tn","tn3270",
"touch","tplot","tprof","tput","tr","trace","traceroute","tracesoff",
"traceson","trcdead","trcnm","trcoff","trcon","trcrpt","trcstop","trcupdate",
"troff","true","tset","tsh","tsort","tty","tvi","twfontutil","twm","u","uil",
"ul","uname","uncompress","unexpand","unget","unifdef","uniq","units","unpack",
"unprotoize","untab","update_all_for_1.0","uptime","users","usrck","utftp",
"uucp","uudecode","uuencode","uulog","uuname","uupick","uupoll","uuq","uusend",
"uusnap","uustat","uuto","uux","vacation","val","vc","vedit","versions","vgrind",
"vi","view","viewname_of","viewres","virscan","vmh","vmstat","w","wall","wc",
"what","whatis","whatnow","whereis","which","who","whoami","whois","whom",
"write","xargs","xauth","xautolock","xbiff","xcalc","xclipboard","xclock",
"xcmsdb","xcomms","xconsole","xcrtca","xde","xditview","xdm","xdpr","xdpyinfo",
"xdt","xdt3","xdt3info","xdt3newuser","xdtpanel","xdtwait","xedit","xfd",
"xfontsel","xget","xhost","xinit","xkill","xlc","xload","xlock","xlogo",
"xlsatoms","xlsclients","xlsfonts","xmag","xman","xmanage","xmbind","xmg.mon",
"xmg.stat","xmg.view","xmh","xmodem","xmodmap","xmonitor","xopen","xpr","xpreview",
"xprop","xrdb","xrefresh","xsccd","xscope","xsend","xset","xsetroot","xss",
"xstdcmap","xstr","xtalk","xterm","xtk.log","xtt","xv","xwd","xwininfo",
"xwud","yacc","yes","ypcat","ypmatch","yppasswd","ypwhich","zcat","zcmp",
"zdiff","zforce","zgrep","zmore","znew",

/* ksh reserved words */
"alias", "autoload", "bg", "break", "case", "esac", "cd", "continue",
"eval", "exec", "exit", "export", "fc", "fg", "for", "do", "done", "function",
"functions", "getopts", "hash", "if", "fi", "then", "else", "elif", "in",
"integer", "jobs", "let", "print", "read", "readonly", "return", "select",
"set", "shift", "times", "trap", "type", "typeset", "ulimit", "umask",
"unalias", "unset", "until", "wait", "whence", "while",
EOS
};

int is_sh_reserved_word (word)
	char	*word;
{
	char	*rw;
	int	rw_ix = 0;

	/* Search in the list */
	while ((rw = reserved_words[rw_ix++]) != EOS) {
		if (strcmp (rw, word) == 0) {
			return (1);
		}
	}
	return (0);
}
