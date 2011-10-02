# Buildfile for an OpenGL demonstration showing a spiral

TEMPLATE = app
TARGET = demo-spiral
DEPENDPATH += . src
INCLUDEPATH += . src

QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/GLDemo.h
HEADERS *= src/SpiralGLDemo.h

SOURCES *= src/GLDemo.cpp
