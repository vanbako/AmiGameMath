#pragma once

#include <exec/types.h>

class DtxRect final
{
public:
    DtxRect(ULONG left, ULONG top, ULONG width, ULONG height);
    ~DtxRect() = default;

    ULONG mLeft;
    ULONG mTop;
    ULONG mWidth;
    ULONG mHeight;
};
