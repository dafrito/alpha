# A buildfile for QMake

TEMPLATE = app
DEPENDPATH += . src
INCLUDEPATH += . src

LIBS += -lglut
QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/DemoTabWidget.h
HEADERS *= src/GLWidget.h
HEADERS *= src/BlankGLWidget.h
HEADERS *= src/SpiralGLWidget.h
HEADERS *= src/SpiralLinesGLWidget.h
HEADERS *= src/LogoGLWidget.h
HEADERS *= src/Logo.h
HEADERS *= src/RotatableGLDemo.h
HEADERS *= src/AnimatedGLWidget.h
HEADERS *= src/PlanetsGLWidget.h
HEADERS *= src/TriangleGLWidget.h
HEADERS *= src/TriangleStripGLWidget.h
HEADERS *= src/StippleGLWidget.h
HEADERS *= src/RandomStippleGLWidget.h
HEADERS *= src/DiamondGLDemo.h
HEADERS *= src/DiamondGLWidget.h
HEADERS *= src/QuadGLWidget.h
HEADERS *= src/StarGLDemo.h
HEADERS *= src/StarGLWidget.h
HEADERS *= src/TorusGLWidget.h

SOURCES *= src/GLWidget.cpp
SOURCES *= src/demos.cpp
SOURCES *= src/Logo.cpp
SOURCES *= src/LogoGLWidget.cpp
SOURCES *= src/RotatableGLDemo.cpp
SOURCES *= src/AnimatedGLWidget.cpp
SOURCES *= src/PlanetsGLWidget.cpp
SOURCES *= src/RandomStippleGLWidget.cpp
SOURCES *= src/DiamondGLWidget.cpp
SOURCES *= src/DiamondGLDemo.cpp
SOURCES *= src/QuadGLWidget.cpp
SOURCES *= src/StarGLWidget.cpp
SOURCES *= src/StarGLDemo.cpp
