#!/bin/sh

[ -f Makefile ] && {
	echo "make clean"
	make clean
}

GENERATED_FILES=Makefile.in
GENERATED_FILES="$GENERATED_FILES aclocal.m4"
GENERATED_FILES="$GENERATED_FILES autom4te.cache/"
GENERATED_FILES="$GENERATED_FILES compile"
GENERATED_FILES="$GENERATED_FILES config.h.in"
GENERATED_FILES="$GENERATED_FILES configure"
GENERATED_FILES="$GENERATED_FILES depcomp"
GENERATED_FILES="$GENERATED_FILES install-sh"
GENERATED_FILES="$GENERATED_FILES missing"
GENERATED_FILES="$GENERATED_FILES src/Makefile.in"
GENERATED_FILES="$GENERATED_FILES Makefile"
GENERATED_FILES="$GENERATED_FILES config.h"
GENERATED_FILES="$GENERATED_FILES config.log"
GENERATED_FILES="$GENERATED_FILES config.status"
GENERATED_FILES="$GENERATED_FILES src/.deps/"
GENERATED_FILES="$GENERATED_FILES src/Makefile"
GENERATED_FILES="$GENERATED_FILES stamp-h1"
GENERATED_FILES="$GENERATED_FILES src/config.h"
GENERATED_FILES="$GENERATED_FILES src/config.h.in"
GENERATED_FILES="$GENERATED_FILES src/stamp-h1"
GENERATED_FILES="$GENERATED_FILES src/config.h.in~"
GENERATED_FILES="$GENERATED_FILES config.guess"
GENERATED_FILES="$GENERATED_FILES config.sub"
GENERATED_FILES="$GENERATED_FILES rpn-1.0.tar.gz"

echo "clean generated files"
rm -rf $GENERATED_FILES