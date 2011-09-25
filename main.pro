# A buildfile for QMake

TEMPLATE = app
TARGET = 
DEPENDPATH += . src
INCLUDEPATH += . src

QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/glwidget.h
HEADERS *= src/qtlogo.h
HEADERS *= src/window.h

SOURCES *= src/qtlogo.cpp
SOURCES *= src/glwidget.cpp
SOURCES *= src/main.cpp
SOURCES *= src/window.cpp
