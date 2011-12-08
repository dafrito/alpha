include (../src/src.pro)

TEMPLATE = app
TARGET = run-tests

OBJECTS_DIR = ../build/tests
MOC_DIR = ../build/tests

CONFIG += qt qtestlib

INCLUDEPATH += ../src
DEPENDPATH += ../src

HEADERS *= Vector3Tests.h

SOURCES *= main.cpp
