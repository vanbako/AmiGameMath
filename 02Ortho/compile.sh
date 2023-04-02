#!/usr/bin/bash
/opt/amiga/bin/m68k-amigaos-g++ --std=c++11 -lamiga \
../Shared/DtxRect.cpp ../Shared/DtxSize.cpp ../Shared/DtxPoint.cpp \
../Shared/DtxLibs.cpp ../Shared/DtxWindow.cpp ../Shared/DtxApp.cpp \
../Shared/DtxMesh.cpp ../Shared/DtxCylinder.cpp \
DtxOrtho.cpp main.cpp -o main
