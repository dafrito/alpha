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
HEADERS *= src/LogoGLWidget.h
HEADERS *= src/Logo.h
HEADERS *= src/LogoGLDemo.h

SOURCES *= src/GLDemo.cpp
SOURCES *= src/demos.cpp
SOURCES *= src/Logo.cpp
SOURCES *= src/LogoGLWidget.cpp
SOURCES *= src/LogoGLDemo.cpp
