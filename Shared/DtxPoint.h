#pragma once

#include <exec/types.h>

class DtxPoint final
{
public:
    DtxPoint(WORD x, WORD y);
    ~DtxPoint() = default;

    WORD mX;
    WORD mY;
};
