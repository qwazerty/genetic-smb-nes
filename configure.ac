AC_INIT([genetic-smb-nes], [0.1])
AC_CONFIG_AUX_DIR(build-aux)

AC_CONFIG_FILES(Makefile
                src/genetic/Makefile)

AM_CXXFLAGS="-Wall -Wextra -Werror -std=c++0x -pedantic -lpthread"

AC_ARG_WITH([debug])
AC_ARG_WITH([clang])
AM_INIT_AUTOMAKE([silent-rules])
AM_SILENT_RULES([yes])

if test "$with_clang" = "yes"; then
    CXX="clang++"
fi

if test "$with_debug" = "yes"; then
    AC_MSG_NOTICE("Adding debug flags")
    CXXFLAGS="$AM_CXXFLAGS -O0 -DDEBUG -g -ggdb"
else
    CXXFLAGS="$AM_CXXFLAGS -DNODEBUG"
fi

PYTHON='python'

AC_PROG_CXX
AC_PROG_RANLIB
AC_SUBST([PYTHON])
AC_SUBST([AM_CXXFLAGS])
AM_PROG_AR

AC_DEFUN([AC_PROG_FCEUX], [AC_CHECK_PROG(FCEUX,fceux,yes)])
AC_PROG_FCEUX
if test x"${FCEUX}" != x"yes" ; then
    AC_MSG_ERROR([Please install Fceux before trying to build.])
fi

AC_DEFUN([AC_PROG_UNBUFFER], [AC_CHECK_PROG(UNBUFFER,unbuffer,yes)])
AC_PROG_UNBUFFER
if test x"${UNBUFFER}" != x"yes" ; then
    AC_MSG_ERROR([Please install unbuffer before trying to build.])
fi

AM_INIT_AUTOMAKE(foreign -Wall)

AC_OUTPUT
