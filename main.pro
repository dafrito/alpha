# A buildfile for QMake

TEMPLATE = app
TARGET = 
DEPENDPATH += . src
INCLUDEPATH += . src

QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/GLDemo.h

SOURCES *= src/GLDemo.cpp
SOURCES *= src/main.cpp
