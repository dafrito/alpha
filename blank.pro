# A buildfile for QMake

TEMPLATE = app
TARGET = demo-blank
DEPENDPATH += . src
INCLUDEPATH += . src

QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/GLDemo.h
HEADERS *= src/BlankGLDemo.h

SOURCES *= src/GLDemo.cpp
