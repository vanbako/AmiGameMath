#pragma once

#include <exec/types.h>

class DtxSize final
{
public:
    DtxSize(ULONG width, ULONG height);
    ~DtxSize() = default;

    ULONG mWidth;
    ULONG mHeight;
};
