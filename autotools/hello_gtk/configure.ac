# -*- Autoconf -*-

AC_PREREQ([2.64])
AC_INIT([hello], [0.1], [David.Villa@uclm.es])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES(GTK, gtk+-2.0 > 2.2)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
