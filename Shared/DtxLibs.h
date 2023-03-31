#pragma once

#include <clib/exec_protos.h>

class DtxLibs final
{
public:
	DtxLibs();
	~DtxLibs();

	Library
		*mpIntuition,
		*mpGfx;
private:
	static const int DtxIntuitionVersion;
	static const int DtxGfxVersion;
};
