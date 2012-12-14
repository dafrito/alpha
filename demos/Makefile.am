bin_PROGRAMS = demo
demo_CPPFLAGS = -I$(top_srcdir)/src @CXX_11_CXXFLAGS@ @QT_CXXFLAGS@ @LUA_CXX_INCLUDE@ @FREETYPE2_CFLAGS@ @LUA_INCLUDE@ @FTGL_CFLAGS@ @GL_CFLAGS@ -DMEDIA_DIR="\"$(abs_srcdir)/../media\""
demo_LDADD = -L../src -lalpha @QT_LIBS@ @LUA_CXX_LIBS@ @FREETYPE2_LIBS@ @FTGL_LIBS@ @LUA_LIB@ @GL_LIBS@

# moc-generated source files
demo_MOC_SOURCES = \
	moc_GLWidget.cpp \
	moc_AnimatedGLWidget.cpp \
	moc_CubeGLWidget.cpp \
	moc_DemoTabWidget.cpp \
	moc_DiamondGLDemo.cpp \
	moc_DiamondGLWidget.cpp \
	moc_FontGLWidget.cpp \
	moc_LogoGLWidget.cpp \
	moc_LuaGLDemo.cpp \
	moc_LuaGLWidget.cpp \
	moc_PlanetsGLWidget.cpp \
	moc_RandomStippleGLWidget.cpp \
	moc_RotatableGLDemo.cpp \
	moc_StarGLDemo.cpp \
	moc_StarGLWidget.cpp \
	moc_VehicleGLWidget.cpp

demo_SOURCES = \
	$(demo_MOC_SOURCES) \
	GLWidget.h \
	GLWidget.cpp \
	AnimatedGLWidget.cpp \
	CubeGLWidget.cpp \
	DiamondGLDemo.cpp \
	DiamondGLWidget.cpp \
	FontGLWidget.cpp \
	Logo.cpp \
	LogoGLWidget.cpp \
	LuaGLDemo.cpp \
	LuaGLWidget.cpp \
	PlanetsGLWidget.cpp \
	RandomStippleGLWidget.cpp \
	RotatableGLDemo.cpp \
	StarGLDemo.cpp \
	StarGLWidget.cpp \
	VehicleGLWidget.cpp \
	AnimatedGLWidget.h \
	BlankGLWidget.h \
	CubeGLWidget.h \
	DemoTabWidget.h \
	DiamondGLDemo.h \
	DiamondGLWidget.h \
	FilmRollGLWidget.h \
	FontGLWidget.h \
	GLWidget.h \
	Heights.h \
	LogoGLWidget.h \
	Logo.h \
	LuaGLDemo.h \
	LuaGLWidget.h \
	PlanetsGLWidget.h \
	RandomStippleGLWidget.h \
	RotatableGLDemo.h \
	SpiralGLWidget.h \
	SpiralLinesGLWidget.h \
	StarGLDemo.h \
	StarGLWidget.h \
	StippleGLWidget.h \
	TorusGLWidget.h \
	TriangleGLWidget.h \
	TriangleStripGLWidget.h \
	VehicleGLWidget.h \
	main.cpp

mostlyclean-local:
	rm -f $(demo_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: %.h
	@QT_MOC@ -o $@ $<

moc_%.cpp: %.hpp
	@QT_MOC@ -o $@ $<
