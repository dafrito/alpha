noinst_LTLIBRARIES = libalpha.la
libalpha_la_CPPFLAGS = @CXX_11_CXXFLAGS@ @QT_CXXFLAGS@ @LUA_CXX_INCLUDE@ @FREETYPE2_CFLAGS@ @LUA_INCLUDE@ @FTGL_CFLAGS@ @GL_CFLAGS@ -DMEDIA_DIR="\"$(abs_srcdir)/../media\"" @ALPHA_GLOBAL_CXXFLAGS@
libalpha_la_LIBADD = @QT_LIBS@ @LUA_CXX_LIBS@ @FREETYPE2_LIBS@ @FTGL_LIBS@ @LUA_LIB@ @GL_LIBS@

# moc-generated source files
libalpha_la_MOC_SOURCES = \
	moc_Alpha.cpp \
	moc_MeasuredTimer.cpp

libalpha_la_SOURCES = \
	$(libalpha_la_MOC_SOURCES) \
	GLOperation.cpp \
	GLOperation.hpp \
	Alpha.cpp \
	Camera.cpp \
	Cuboid.cpp \
	MeasuredTimer.cpp \
	PlayerInput.cpp \
	ntgl.cpp \
	Vector3.cpp \
	Alpha.h \
	Camera.h \
	config.h \
	Cuboid.h \
	MeasuredTimer.h \
	Object.h \
	Player.h \
	PlayerInput.h \
	ntgl.h \
	RenderLayer.hpp \
	DirectRenderLayer.hpp \
	Renderable.hpp \
	Physical.hpp \
	Vector3.h

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
