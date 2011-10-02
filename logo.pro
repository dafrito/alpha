# A buildfile for QMake

TEMPLATE = app
TARGET = 
DEPENDPATH += . src
INCLUDEPATH += . src

QT += opengl

OBJECTS_DIR = build
MOC_DIR = build

HEADERS *= src/LogoGLWidget.h
HEADERS *= src/Logo.h
HEADERS *= src/LogoGLDemo.h

SOURCES *= src/main.cpp
SOURCES *= src/Logo.cpp
SOURCES *= src/LogoGLWidget.cpp
SOURCES *= src/LogoGLDemo.cpp
