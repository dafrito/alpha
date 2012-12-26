noinst_LTLIBRARIES = libalpha.la
libalpha_la_CPPFLAGS = @CXX_11_CXXFLAGS@ @QT_CXXFLAGS@ @LUA_CXX_INCLUDE@ @FREETYPE2_CFLAGS@ @LUA_INCLUDE@ @FTGL_CFLAGS@ @GL_CFLAGS@ -DMEDIA_DIR="\"$(abs_srcdir)/../media\"" @ALPHA_GLOBAL_CXXFLAGS@
libalpha_la_LIBADD = @QT_LIBS@ @LUA_CXX_LIBS@ @FREETYPE2_LIBS@ @FTGL_LIBS@ @LUA_LIB@ @GL_LIBS@

# moc-generated source files
libalpha_la_MOC_SOURCES = \
	moc_Alpha.cpp \
	moc_MeasuredTimer.cpp

libalpha_la_SOURCES = \
	$(libalpha_la_MOC_SOURCES) \
	gl/GLOperation.cpp \
	gl/GLOperation.hpp \
	gl/Camera.hpp \
	gl/Camera.cpp \
	gl/util.hpp \
	gl/util.cpp \
	gl/Cuboid.cpp \
	gl/Cuboid.hpp \
	gl/RenderLayer.hpp \
	gl/DirectRenderLayer.hpp \
	gl/Renderable.hpp \
	gl/Physical.hpp \
	math.hpp \
	MeasuredTimer.cpp \
	PlayerInput.cpp \
	Vector3.hpp \
	config.h \
	MeasuredTimer.hpp \
	Object.hpp \
	Player.hpp \
	PlayerInput.h \
	ArrayVoxmap.hpp \
	gl/Viewport.hpp \
	gl/Viewport.cpp \
	Alpha.h \
	Alpha.cpp

bin_PROGRAMS = alpha
alpha_CPPFLAGS = $(libalpha_la_CPPFLAGS)
alpha_LDADD = libalpha.la $(libalpha_la_LIBADD)

alpha_SOURCES = \
	main.cpp

mostlyclean-local:
	rm -f $(alpha_MOC_SOURCES) $(libalpha_la_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: %.h
	@QT_MOC@ -o $@ $<

moc_%.cpp: %.hpp
	@QT_MOC@ -o $@ $<
