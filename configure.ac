#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ui-demo], [0.9], [corbe@corbe.net])
AC_CONFIG_SRCDIR([ui.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE()

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.
AC_ARG_ENABLE([gdb],
	[AS_HELP_STRING([--enable-gdb], [Enable Debugging])],
	[DEBUG="-DDEBUG -ggdb"],
	[DEBUG=""])
AC_SUBST([DEBUG])

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
