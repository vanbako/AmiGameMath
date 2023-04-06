#!/usr/bin/bash
/opt/amiga/bin/m68k-amigaos-g++ --std=c++11 -lamiga \
../Shared/DtxRect.cpp ../Shared/DtxSize.cpp ../Shared/DtxPoint.cpp \
../Shared/DtxLibs.cpp ../Shared/DtxWindow.cpp \
DtxApp.cpp DtxMesh.cpp DtxCylinder.cpp DtxCamera.cpp DtxPerspective.cpp main.cpp -o 05Perspective
