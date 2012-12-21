bin_PROGRAMS = demo
demo_CPPFLAGS = -I$(top_srcdir)/src @CXX_11_CXXFLAGS@ @QT_CXXFLAGS@ @LUA_CXX_INCLUDE@ @FREETYPE2_CFLAGS@ @LUA_INCLUDE@ @FTGL_CFLAGS@ @GL_CFLAGS@ -DMEDIA_DIR="\"$(abs_srcdir)/../media\"" @ALPHA_GLOBAL_CXXFLAGS@
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
	GLWidget.hpp \
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
	AnimatedGLWidget.hpp \
	BlankGLWidget.hpp \
	CubeGLWidget.hpp \
	DemoTabWidget.hpp \
	DiamondGLDemo.hpp \
	DiamondGLWidget.hpp \
	FilmRollGLWidget.hpp \
	FontGLWidget.hpp \
	GLWidget.hpp \
	Heights.hpp \
	LogoGLWidget.hpp \
	Logo.hpp \
	LuaGLDemo.hpp \
	LuaGLWidget.hpp \
	PlanetsGLWidget.hpp \
	RandomStippleGLWidget.hpp \
	RotatableGLDemo.hpp \
	SpiralGLWidget.hpp \
	SpiralLinesGLWidget.hpp \
	StarGLDemo.hpp \
	StarGLWidget.hpp \
	StippleGLWidget.hpp \
	TorusGLWidget.hpp \
	TriangleGLWidget.hpp \
	TriangleStripGLWidget.hpp \
	VehicleGLWidget.hpp \
	main.cpp

mostlyclean-local:
	rm -f $(demo_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: %.hpp
	@QT_MOC@ -o $@ $<
