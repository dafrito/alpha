# Buildfile for an OpenGL demonstration showing a spiral

TEMPLATE = app
TARGET = demo-spiral
DEPENDPATH += . src
INCLUDEPATH += . src

QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/GLDemo.h

SOURCES *= src/GLDemo.cpp
SOURCES *= src/spiral.cpp
