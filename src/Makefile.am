noinst_LTLIBRARIES = libalpha.la
libalpha_la_CPPFLAGS = @CXX_11_CXXFLAGS@ @QT_CXXFLAGS@ @LUA_CXX_INCLUDE@ @FREETYPE2_CFLAGS@ @LUA_INCLUDE@ @FTGL_CFLAGS@ @GL_CFLAGS@
libalpha_la_LIBADD = @QT_LIBS@ @LUA_CXX_LIBS@ @FREETYPE2_LIBS@ @FTGL_LIBS@ @LUA_LIB@ @GL_LIBS@

# moc-generated source files
libalpha_la_MOC_SOURCES = \
	moc_Alpha.cpp \
	moc_AnimatedGLWidget.cpp \
	moc_CubeGLWidget.cpp \
	moc_DemoTabWidget.cpp \
	moc_DiamondGLDemo.cpp \
	moc_DiamondGLWidget.cpp \
	moc_FontGLWidget.cpp \
	moc_GLWidget.cpp \
	moc_LogoGLWidget.cpp \
	moc_LuaGLDemo.cpp \
	moc_LuaGLWidget.cpp \
	moc_MeasuredTimer.cpp \
	moc_PlanetsGLWidget.cpp \
	moc_RandomStippleGLWidget.cpp \
	moc_RotatableGLDemo.cpp \
	moc_StarGLDemo.cpp \
	moc_StarGLWidget.cpp \
	moc_VehicleGLWidget.cpp

libalpha_la_SOURCES = \
	$(libalpha_la_MOC_SOURCES) \
	Alpha.cpp \
	AnimatedGLWidget.cpp \
	Camera.cpp \
	CubeGLWidget.cpp \
	Cuboid.cpp \
	DiamondGLDemo.cpp \
	DiamondGLWidget.cpp \
	FontGLWidget.cpp \
	GLWidget.cpp \
	Logo.cpp \
	LogoGLWidget.cpp \
	LuaGLDemo.cpp \
	LuaGLWidget.cpp \
	MeasuredTimer.cpp \
	PlanetsGLWidget.cpp \
	PlayerInput.cpp \
	RandomStippleGLWidget.cpp \
	RotatableGLDemo.cpp \
	StarGLDemo.cpp \
	StarGLWidget.cpp \
	ntgl.cpp \
	Vector3.cpp \
	VehicleGLWidget.cpp \
	Alpha.h \
	AnimatedGLWidget.h \
	BlankGLWidget.h \
	Camera.h \
	config.h \
	CubeGLWidget.h \
	Cuboid.h \
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
	MeasuredTimer.h \
	Object.h \
	PlanetsGLWidget.h \
	Player.h \
	PlayerInput.h \
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
	ntgl.h \
	Vector3.h \
	VehicleGLWidget.h

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
