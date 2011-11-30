#!/bin/sh
qmake CONFIG+=debug -recursive
make -j 4 && ./demo
