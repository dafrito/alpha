# A buildfile for QMake

TEMPLATE = app
DEPENDPATH += . src
INCLUDEPATH += . src

QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/GLDemo.h
HEADERS *= src/BlankGLDemo.h
HEADERS *= src/SpiralGLDemo.h

SOURCES *= src/GLDemo.cpp
SOURCES *= src/demos.cpp
