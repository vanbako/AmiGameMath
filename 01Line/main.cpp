#include "../Shared/DtxLibs.h"
#include "../Shared/DtxApp.h"
#include "../Shared/DtxWindow.h"
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	DtxLibs dtxLibs{};
	DtxApp dtxApp{};
	DtxRect
		dtxRect{ 20, 20, 640, 512 },
		dtxRectButton{ 20, 20, 100, 25 };
	DtxSize
		dtxMinSize{ 160, 128 },
		dtxMaxSize{ 1280, 1024 };
	DtxWindow *pDtxWindow{ dtxApp.AddWindow("GameMath, 01Line", dtxRect, dtxMinSize, dtxMaxSize) };
	pDtxWindow->OpenWindow();
	std::vector<DtxPoint> dtxTriangle{
		{ 300, 50 },
		{ 400, 250 },
		{ 200, 250 }
	};
	pDtxWindow->DrawPolyLine(dtxTriangle);
	dtxApp.Loop();
	return 0;
}
