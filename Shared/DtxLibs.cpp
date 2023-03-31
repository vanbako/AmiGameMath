#include "DtxLibs.h"

const int DtxLibs::DtxIntuitionVersion{ 45 };
const int DtxLibs::DtxGfxVersion{ 45 };

DtxLibs::DtxLibs()
    : mpIntuition{ nullptr }
    , mpGfx{ nullptr }
{
	mpIntuition = OpenLibrary("intuition.library", DtxIntuitionVersion);
	mpGfx = OpenLibrary("graphics.library", DtxGfxVersion);
    return;
}

DtxLibs::~DtxLibs()
{
    if (mpIntuition != nullptr)
        CloseLibrary(mpIntuition);
    if (mpGfx != nullptr)
        CloseLibrary(mpGfx);
}
