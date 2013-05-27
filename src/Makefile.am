lib_LTLIBRARIES = libalpha.la
libalpha_la_CPPFLAGS = @CXX_11_CXXFLAGS@ @QT_CXXFLAGS@ @LUA_CXX_INCLUDE@ \
	@FREETYPE2_CFLAGS@ @FTGL_CFLAGS@ @GL_CFLAGS@ \
	-DMEDIA_DIR="\"$(abs_srcdir)/../media\"" @ALPHA_GLOBAL_CXXFLAGS@ \
	-I$(top_srcdir)/include

libalpha_la_LIBADD = @QT_LIBS@ @LUA_CXX_LIBS@ @FREETYPE2_LIBS@ @FTGL_LIBS@ @GL_LIBS@

# moc-generated source files
libalpha_la_MOC_SOURCES = \
	gl/moc_ScreenGLWidget.cpp \
	moc_MeasuredTimer.cpp \
	input/moc_PlayerInputFilter.cpp

libalpha_la_SOURCES = \
	$(libalpha_la_MOC_SOURCES) \
	config.h \
	gl/GLOperation.cpp \
	gl/Camera.cpp \
	gl/util.cpp \
	gl/Cuboid.cpp \
	gl/PerspectiveProjection.cpp \
	MeasuredTimer.cpp \
	PlayerInput.cpp \
	input/PlayerInputFilter.cpp \
	InputMotion.cpp \
	PerlinNoise.cpp \
	PlayerInput.h \
	gl/Viewport.cpp \
	gl/Screen.cpp \
	gl/ScreenGLWidget.cpp \
	SystemLoop.cpp

bin_PROGRAMS = alpha
alpha_CPPFLAGS = $(libalpha_la_CPPFLAGS)
alpha_LDADD = libalpha.la $(libalpha_la_LIBADD)

alpha_MOC_SOURCES = \
	moc_Alpha.cpp \
	moc_Bootstrapper.cpp

alpha_SOURCES = \
	$(alpha_MOC_SOURCES) \
	Bootstrapper.cpp \
	Alpha.h \
	Alpha.cpp \
	main.cpp

mostlyclean-local:
	rm -f $(alpha_MOC_SOURCES) $(libalpha_la_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: $(top_srcdir)/include/%.h
	@QT_MOC@ -o $@ $<

moc_%.cpp: $(top_srcdir)/include/%.hpp
	@QT_MOC@ -o $@ $<

input/moc_%.cpp: $(top_srcdir)/include/input/%.hpp
	mkdir -p `dirname $@`
	cd `dirname $@` && @QT_MOC@ -o `basename $@` ../$<

gl/moc_%.cpp: $(top_srcdir)/include/gl/%.hpp
	mkdir -p `dirname $@`
	cd `dirname $@` && @QT_MOC@ -o `basename $@` ../$<
