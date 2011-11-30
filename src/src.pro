!include(../lua-cxx/lib/lib.pro) {
	message("lua-cxx was not found. You probably need to initialize it by running:")
	message("$ git submodule init")
	message("$ git submodule update")
	error();
}

TEMPLATE = app
DEPENDPATH += . ../lua-cxx/lib
INCLUDEPATH += . ../lua-cxx/lib

DESTDIR = ..
TARGET= demo

LIBS += -lglut
QT += opengl

OBJECTS_DIR = ../build
MOC_DIR = ../build

HEADERS *= DemoTabWidget.h
HEADERS *= GLWidget.h
HEADERS *= BlankGLWidget.h
HEADERS *= SpiralGLWidget.h
HEADERS *= SpiralLinesGLWidget.h
HEADERS *= LogoGLWidget.h
HEADERS *= Logo.h
HEADERS *= RotatableGLDemo.h
HEADERS *= MeasuredTimer.h
HEADERS *= AnimatedGLWidget.h
HEADERS *= PlanetsGLWidget.h
HEADERS *= TriangleGLWidget.h
HEADERS *= TriangleStripGLWidget.h
HEADERS *= StippleGLWidget.h
HEADERS *= RandomStippleGLWidget.h
HEADERS *= DiamondGLDemo.h
HEADERS *= DiamondGLWidget.h
HEADERS *= CubeGLWidget.h
HEADERS *= StarGLDemo.h
HEADERS *= StarGLWidget.h
HEADERS *= TorusGLWidget.h
HEADERS *= FilmRollGLWidget.h
HEADERS *= VehicleGLWidget.h
HEADERS *= LuaGLWidget.h
HEADERS *= Alpha.h
HEADERS *= util.h
HEADERS *= Player.h
HEADERS *= Camera.h
HEADERS *= Vector.h
HEADERS *= PlayerInput.h

SOURCES *= GLWidget.cpp
SOURCES *= demos.cpp
SOURCES *= Logo.cpp
SOURCES *= LogoGLWidget.cpp
SOURCES *= RotatableGLDemo.cpp
SOURCES *= MeasuredTimer.cpp
SOURCES *= AnimatedGLWidget.cpp
SOURCES *= PlanetsGLWidget.cpp
SOURCES *= RandomStippleGLWidget.cpp
SOURCES *= DiamondGLWidget.cpp
SOURCES *= DiamondGLDemo.cpp
SOURCES *= CubeGLWidget.cpp
SOURCES *= StarGLWidget.cpp
SOURCES *= StarGLDemo.cpp
SOURCES *= VehicleGLWidget.cpp
SOURCES *= LuaGLWidget.cpp
SOURCES *= Alpha.cpp
SOURCES *= util.cpp
SOURCES *= Camera.cpp
SOURCES *= PlayerInput.cpp
