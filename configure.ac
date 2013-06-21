# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([alpha], [1.0], [dafrito@gmail.com], [alpha], [http://bluespot.unfuddle.com])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

# Initialize libtool
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_PREREQ([2.2])
LT_INIT
AC_PROG_LIBTOOL

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext],[CXX_11_CXXFLAGS])
AC_SUBST([CXX_11_CXXFLAGS])

ALPHA_GLOBAL_CXXFLAGS="-g -O2"
AC_SUBST([ALPHA_GLOBAL_CXXFLAGS])

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([FREETYPE2], [freetype2])
PKG_CHECK_MODULES([FTGL], [ftgl])

# Check for Boost
AX_BOOST_BASE([], [:], AC_MSG_ERROR([Boost is required to build lua-cxx]))

# Check for Lua-cxx
if ! pkg-config --print-errors --exists "lua-cxx"; then
    AC_MSG_ERROR([Lua-cxx is required to build Rainback])
fi

AC_SUBST(LUA_CXX_INCLUDE)
AC_SUBST(LUA_CXX_LIBS)
LUA_CXX_INCLUDE=`pkg-config --cflags lua-cxx`
LUA_CXX_LIBS=`pkg-config --libs lua-cxx`

if test x"$have_qt_core" = xno ||
    test x"$have_qt_gui" = xno ||
    test x"$have_qt_moc" = xno ||
    test x"$have_qt_opengl" = xno; then
    AC_MSG_ERROR([Qt is required to build alpha])
fi;

# Check for Qt
AX_HAVE_QT_CORE
AX_HAVE_QT_GUI
AX_HAVE_QT_WIDGETS
AX_HAVE_QT_MOC
AX_HAVE_QT_TEST
AX_HAVE_QT_OPENGL

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

AC_LANG([C++])

# Checks for library functions.

AC_CONFIG_FILES([alpha.m4 alpha.pc Makefile src/Makefile include/Makefile demos/Makefile tests/Makefile rpm.spec])
AC_OUTPUT
