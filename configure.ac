AC_PREREQ(2.61)
AC_INIT([saft], [0.0.3], [sylvain.foret@anu.edu.au])
AC_CONFIG_SRCDIR([src/libsaft/saftsequence.h])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE()

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for pkg-config
PKG_PROG_PKG_CONFIG(0.16)

# Checks for libraries.

PKG_CHECK_MODULES(GSL,
                  gsl >= 1.12, ,
                  AC_MSG_ERROR(Test for GSL failed. See the file 'INSTALL' for help.))

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

changequote(,)dnl
if test "x$GCC" = "xyes"; then
  case " $CFLAGS " in
  *[\ \	]-Wall[\ \	]*) ;;
  *) CFLAGS="$CFLAGS -Wall" ;;
  esac
fi
changequote([,])dnl

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memset pow sqrt strdup])

AC_OUTPUT([
	Makefile
	src/Makefile
	src/saft/Makefile
	src/libsaft/Makefile
	src/tests/Makefile])
