dnl config.m4 for extension includemonitor

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([includemonitor],
dnl   [for includemonitor support],
dnl   [AS_HELP_STRING([--with-includemonitor],
dnl     [Include includemonitor support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([includemonitor],
  [whether to enable includemonitor support],
  [AS_HELP_STRING([--enable-includemonitor],
    [Enable includemonitor support])],
  [no])

if test "$PHP_INCLUDEMONITOR" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, INCLUDEMONITOR_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-includemonitor -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/includemonitor.h"  # you most likely want to change this
  dnl if test -r $PHP_INCLUDEMONITOR/$SEARCH_FOR; then # path given as parameter
  dnl   INCLUDEMONITOR_DIR=$PHP_INCLUDEMONITOR
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for includemonitor files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       INCLUDEMONITOR_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$INCLUDEMONITOR_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the includemonitor distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-includemonitor -> add include path
  dnl PHP_ADD_INCLUDE($INCLUDEMONITOR_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-includemonitor -> check for lib and symbol presence
  dnl LIBNAME=INCLUDEMONITOR # you may want to change this
  dnl LIBSYMBOL=INCLUDEMONITOR # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_INCLUDEMONITOR_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your includemonitor library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $INCLUDEMONITOR_DIR/$PHP_LIBDIR, INCLUDEMONITOR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_INCLUDEMONITOR_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your includemonitor library.])
  dnl ],[
  dnl   -L$INCLUDEMONITOR_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(INCLUDEMONITOR_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_INCLUDEMONITOR, 1, [ Have includemonitor support ])

  PHP_NEW_EXTENSION(includemonitor, includemonitor.c, $ext_shared)
fi
