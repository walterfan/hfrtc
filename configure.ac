#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# note: replace [FULL-PACKAGE-NAME]
AC_PREREQ([2.63])
AC_INIT(hfrtc, 1.0)
# note: add automake
AM_INIT_AUTOMAKE([-Wall])
#AM_PROG_AR
m4_pattern_allow([AM_PROG_AR], [AM_PROG_AR])

# library building
#AC_PROG_RANLIB
AC_PROG_LIBTOOL

AC_CONFIG_SRCDIR([src/hfrtc.cpp])
AC_CONFIG_HEADERS([config.h])
#AM_CONFIG_HEADER(config.h)
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdint.h stdlib.h string.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_CHECK_FUNCS([gettimeofday strerror])
# note: out Makefile
AC_OUTPUT(Makefile test/Makefile util/Makefile src/Makefile)
