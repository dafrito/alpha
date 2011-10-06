# A buildfile for QMake

TEMPLATE = app
DEPENDPATH += . src
INCLUDEPATH += . src

LIBS += -lglut
QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/GLWidget.h
HEADERS *= src/BlankGLWidget.h
HEADERS *= src/SpiralGLWidget.h
HEADERS *= src/LogoGLWidget.h
HEADERS *= src/Logo.h
HEADERS *= src/LogoGLDemo.h
HEADERS *= src/AtomGLWidget.h
HEADERS *= src/TriangleGLWidget.h
HEADERS *= src/RandomStippleGLWidget.h
HEADERS *= src/DiamondGLDemo.h
HEADERS *= src/DiamondGLWidget.h

SOURCES *= src/GLWidget.cpp
SOURCES *= src/demos.cpp
SOURCES *= src/Logo.cpp
SOURCES *= src/LogoGLWidget.cpp
SOURCES *= src/LogoGLDemo.cpp
SOURCES *= src/AtomGLWidget.cpp
SOURCES *= src/RandomStippleGLWidget.cpp
SOURCES *= src/DiamondGLWidget.cpp
SOURCES *= src/DiamondGLDemo.cpp
