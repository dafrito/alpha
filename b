#!/bin/sh
qmake CONFIG+=debug -recursive
make -j && ./demo
