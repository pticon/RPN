AC_PREREQ([2.69])
AC_INIT([rpn], [1.0], [pme.lebleu@gmail.com], [], [https://github.com/pticon/rpn])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Check for programs
AC_PROG_CC
AC_LANG(C)
AC_CONFIG_HEADERS([src/config.h])


# Configure options
AC_ARG_ENABLE([debug], AC_HELP_STRING([--enable-debug], [Enable debug compilation]),
[ if test "x$enableval" = "xyes"; then
	AC_DEFINE([DEBUG], [1], [Enable debug compilation, assertions, etc.])
fi ])
AC_PREFIX_DEFAULT(/usr/local)


# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT8_T
AC_TYPE_UINT8_T
AC_TYPE_INT16_T
AC_TYPE_UINT16_T
AC_TYPE_INT32_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_SIZE_T
AC_STRUCT_TM

AC_C_INLINE
AC_C_CONST

AC_FUNC_ALLOCA
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_FUNC_STAT
AC_FUNC_STRERROR_R
AC_FUNC_STRFTIME
AC_FUNC_VPRINTF



# Check for OS type
AC_CANONICAL_HOST
case "$host_os" in
	linux*)		OS=linux ;;
	freebsd*)	OS=freebsd ;;
	*)		AC_MSG_ERROR([Unknown or unsupported OS "$host_os".  Only "linux" and "freebsd" are supported in this version of Aker.]) ;;
esac
AC_SUBST([OS])

# Add defines relative to the OS type
if test "x$OS" = "xfreebsd"; then
	AC_DEFINE([__FreeBSD__], [uname -r | cut -d . -f 1], [FreeBSD machine.])
else if test "x$OS" = "xlinux"; then
	AC_DEFINE([__LINUX__], [1], [Linux machine.])
else
	AC_MSG_ERROR([Unknown or unsupported OS "$host_os".  Only "linux" and "freebsd" are supported in this version of Aker.])
fi
fi


# Check for headers
AC_CHECK_HEADER(errno.h, [], [echo "error: errno.h not found!"; exit -1])
AC_CHECK_HEADER(math.h, [], [echo "error: math.h not found!"; exit -1])
AC_CHECK_HEADER(readline/history.h, [], [echo "error: readline/history.h not found!"; exit -1])
AC_CHECK_HEADER(readline/readline.h, [], [echo "error: readline/readline.h not found!"; exit -1])
AC_CHECK_HEADER(stdio.h, [], [echo "error: stdio.h not found!"; exit -1])
AC_CHECK_HEADER(stdlib.h, [], [echo "error: stdlib.h not found!"; exit -1])
AC_CHECK_HEADER(string.h, [], [echo "error: string.h not found!"; exit -1])
AC_CHECK_HEADER(unistd.h, [], [echo "error: unistd.h not found!"; exit -1])


# Checks for library functions.
#AC_CHECK_FUNCS([strlcat])

# Checks for flex
AC_PROG_LEX
if test "x$LEX" != xflex; then
	LEX="$SHELL $missing_dir/missing flex"
	AC_SUBST([LEX_OUTPUT_ROOT], [lex.yy])
	AC_SUBST([LEXLIB], [''])
fi

AC_OUTPUT([Makefile src/Makefile])


AC_MSG_RESULT([
        $PACKAGE $VERSION
        ========

        prefix:                 ${prefix}
        libdir:                 ${libdir}
        sysconfdir:             ${sysconfdir}
        exec_prefix:            ${exec_prefix}
        bindir:                 ${bindir}
        datarootdir:            ${datarootdir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
        ldflags:                ${LDFLAGS}
])
