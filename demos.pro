!exists(lua-cxx/lua-cxx.pro) {
	message("lua-cxx was not found. You probably need to initialize it by running:")
	message("$ git submodule init")
	message("$ git submodule update")
	error();
}

TEMPLATE = subdirs
SUBDIRS = lua-cxx src
CONFIG += ordered
