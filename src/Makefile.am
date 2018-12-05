bin_PROGRAMS = rpn

AM_LFLAGS = --header-file=rpn_lex.h

rpn_SOURCES = rpn_lex.l
rpn_SOURCES += arithmetic.c elt.c float.h list.h operator.c rpn.c stack.c strings.h
rpn_SOURCES += arithmetic.h elt.h integer.h main.c operator.h rpn.h stack.h

rpn_CFLAGS = -D_GNU_SOURCE -Wall -Wunused -Werror

rpn_LDADD = -lreadline -lm -lfl
