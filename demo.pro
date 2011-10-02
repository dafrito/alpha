# A buildfile for QMake

TEMPLATE = app
DEPENDPATH += . src
INCLUDEPATH += . src

QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/GLWidget.h
HEADERS *= src/BlankGLWidget.h
HEADERS *= src/SpiralGLWidget.h
HEADERS *= src/LogoGLWidget.h
HEADERS *= src/Logo.h
HEADERS *= src/LogoGLDemo.h

SOURCES *= src/GLWidget.cpp
SOURCES *= src/demos.cpp
SOURCES *= src/Logo.cpp
SOURCES *= src/LogoGLWidget.cpp
SOURCES *= src/LogoGLDemo.cpp
