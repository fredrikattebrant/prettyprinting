# Makefile to make the pp_* programs.
#

#CC		= /opt/GNUgcc/bin/gcc

PP_ADA_EXE	= ../bin/pp_ada
PP_C_EXE	= ../bin/pp_c
PP_CPP_EXE	= ../bin/pp_c++
PP_IDL_EXE	= ../bin/pp_idl
PP_JAVA_EXE	= ../bin/pp_java
PP_SH_EXE	= ../bin/pp_sh
PP_TEXT_EXE	= ../bin/pp_text
PP_VB_EXE	= ../bin/pp_vb

PP_COMMON_OFILES = pp_fe.o pp_me.o pp_be.o

PP_ADA_OFILES	= pp_ada.o pp_ada_lex.o $(PP_COMMON_OFILES)
PP_C_OFILES		= pp_c.o pp_c_lex.o $(PP_COMMON_OFILES)
PP_CPP_OFILES	= pp_c++.o pp_c++_lex.o $(PP_COMMON_OFILES)
PP_IDL_OFILES	= pp_idl.o pp_idl_lex.o $(PP_COMMON_OFILES)
PP_JAVA_OFILES  = pp_java.o pp_java_lex.o $(PP_COMMON_OFILES)
PP_SH_OFILES	= pp_sh.o pp_sh_lex.o $(PP_COMMON_OFILES)
PP_TEXT_OFILES	= pp_text_lex.o $(PP_COMMON_OFILES)
PP_VB_OFILES	= pp_vb.o pp_vb_lex.o $(PP_COMMON_OFILES)


CFLAGS		= -c -g -I../include
LDFLAGS		= 
LIBS		= #-ll
LEXFLAGS	= -l

PUT	=	echo `date +%H:%M:%S` +++


# disable the built-in .c.a rule
.c.a:;

.c.o:
	@$(PUT) Compiling $<
	@$(CC) $(CFLAGS) $<

.l.c:
	@$(PUT) "Create $@ from $<"
	@lex $(LEXFLAGS) $<
	@rm -f $@
	@mv lex.yy.c $@

.l.o:
	@$(PUT) Compiling $<
	@lex $(LEXFLAGS) $<
	@rm -f $@
	@mv lex.yy.c `basename $@ .o`.c
	@$(CC) $(CFLAGS) `basename $@ .o`.c

#
# Rules
# First is default (all)
#
all: $(PP_ADA_EXE) $(PP_C_EXE) $(PP_CPP_EXE) $(PP_IDL_EXE) $(PP_JAVA_EXE) \
     $(PP_SH_EXE) $(PP_TEXT_EXE) $(PP_VB_EXE)

pp_fe.o: ../include/pp_fe.h ../include/pp_me.h ../include/pp_be.h
pp_me.o: ../include/pp_me.h ../include/pp_be.h
pp_be.o: ../include/pp_be.h ../include/pp_ps.h ../include/pp_ps_digits.h \
	 ../include/pp_ps_fonts.h ../include/pp_ps_header.h

#
#  pp_ada
#
$(PP_ADA_EXE): $(PP_ADA_OFILES)
	@$(PUT) "Linking $@"
	@$(CC) -o $@ $(PP_ADA_OFILES) $(LDFLAGS) $(LIBS)


#
#  pp_c
#
$(PP_C_EXE): $(PP_C_OFILES)
	@$(PUT) "Linking $@"
	@$(CC) -o $@ $(PP_C_OFILES) $(LDFLAGS) $(LIBS)


#
#  pp_c++
#
$(PP_CPP_EXE): $(PP_CPP_OFILES)
	@$(PUT) "Linking $@"
	@$(CC) -o $@ $(PP_CPP_OFILES) $(LDFLAGS) $(LIBS)


#
#  pp_idl
#
$(PP_IDL_EXE): $(PP_IDL_OFILES)
	@$(PUT) "Linking $@"
	@$(CC) -o $@ $(PP_IDL_OFILES) $(LDFLAGS) $(LIBS)


#
#  pp_java
#
$(PP_JAVA_EXE):	$(PP_JAVA_OFILES)
	@$(PUT) "Linking $@"
	@$(CC) -o $@ $(PP_JAVA_OFILES) $(LDFLAGS) $(LIBS)


#
#  pp_sh
#
$(PP_SH_EXE): $(PP_SH_OFILES)
	@$(PUT) "Linking $@"
	@$(CC) -o $@ $(PP_SH_OFILES) $(LDFLAGS) $(LIBS)


#
#  pp_text
#
$(PP_TEXT_EXE): $(PP_TEXT_OFILES)
	@$(PUT) "Linking $@"
	@$(CC) -o $@ $(PP_TEXT_OFILES) $(LDFLAGS) $(LIBS)


#
#  pp_vb
#
$(PP_VB_EXE): $(PP_VB_OFILES)
	@$(PUT) "Linking $@"
	@$(CC) -o $@ $(PP_VB_OFILES) $(LDFLAGS) $(LIBS)


#
#  clean
#
clean: cleanx cleano cleanc

cleanx:
	@$(PUT) "Removing executables"
	@rm -f $(PP_ADA_EXE) $(PP_C_EXE) $(PP_CPP_EXE) $(PP_IDL_EXE) \
		$(PP_JAVA_EXE) $(PP_SH_EXE) $(PP_TEXT_EXE) $(PP_VB_EXE)

cleano:
	@$(PUT) "Removing object files"
	@rm -f $(PP_COMMON_OFILES) $(PP_ADA_OFILES) $(PP_C_OFILES) \
		$(PP_CPP_OFILES) $(PP_IDL_OFILES) $(PP_JAVA_OFILES) \
		$(PP_SH_OFILES) $(PP_TEXT_OFILES) $(PP_VB_OFILES)

cleanc:
	@$(PUT) "Removing derived C files (lex output)"
	@rm -f pp_ada_lex.c pp_c_lex.c pp_c++_lex.c pp_idl_lex.c \
		pp_java_lex.c pp_shell_lex.c pp_text_lex.c pp_vb_lex.c
