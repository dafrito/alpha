# ===========================================================================
#    http://www.dafrito.com
# ===========================================================================
#
# SYNOPSIS
#
#   AX_HAVE_LUA_CXX
#
# DESCRIPTION
#
#   Test for lua-cxx
#
#   This macro calls:
#
#     AC_SUBST(LUA_CXX_INCLUDE)
#     AC_SUBST(LUA_CXX_LIBS)
#
#   And sets:
#
#     HAVE_LUA_CXX
#
# LICENSE
#
#   Copyright (c) 2012 Aaron Faanes <dafrito@gmail.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

AC_DEFUN([AX_HAVE_LUA_CXX],
[
	AC_ARG_WITH([lua-cxx],
    AS_HELP_STRING([--with-lua-cxx], [use lua-cxx]),
    [
      if test x"$withval" = "xno"; then
        want_LUA_CXX="no";
      else
        want_LUA_CXX="yes";
      fi
    ],
    [want_LUA_CXX="yes"]
  )

  if test x"$want_LUA_CXX" = "xyes"; then
    AC_MSG_CHECKING([for lua-cxx])

    # Ensure we have a suitable C++ compiler
    AC_REQUIRE([AC_PROG_CC])
    AC_REQUIRE([AX_HAVE_QT_CORE])
    AC_REQUIRE([AC_PROG_CXX])

    ax_LUA_CXX_saved_CPPFLAGS="$CPPFLAGS"
    ax_LUA_CXX_INCLUDE=""
    CPPFLAGS="$CPPFLAGS $QT_CXXFLAGS $ax_LUA_CXX_INCLUDE"
    export CPPFLAGS

    ax_LUA_CXX_saved_LIBS="$LIBS"
    ax_LUA_CXX_LIBS=""
    LIBS="$LIBS $ax_LUA_CXX_LIBS $QT_LIBS"
    export LIBS

    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM(
        [[@%:@include <lua-cxx/LuaEnvironment.hpp>]],
        [[
          Lua lua;
          return 0;
        ]]
      )],
      ax_have_LUA_CXX=yes,
      ax_have_LUA_CXX=no
    )
    AC_LANG_POP([C++])

    AC_MSG_RESULT([$ax_have_LUA_CXX])
    if test x"$ax_have_LUA_CXX" = "xyes"; then
      AC_DEFINE(HAVE_LUA_CXX,,[define if lua-cxx is available])
      LUA_CXX_INCLUDE="$ax_LUA_CXX_INCLUDE"
      dnl This doesn't yet test the location of this project
      LUA_CXX_LIBS="$ax_LUA_CXX_LIBS -llua-cxx"
    else
      AC_MSG_ERROR([Could not find lua-cxx])
      LUA_CXX_INCLUDE=""
      LUA_CXX_LIBS=""
    fi
    AC_SUBST(LUA_CXX_INCLUDE)
    AC_SUBST(LUA_CXX_LIBS)

    CPPFLAGS="$ax_LUA_CXX_saved_CPPFLAGS"
    LIBS="$ax_LUA_CXX_saved_LIBS"
  fi;
])
