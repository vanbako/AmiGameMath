#include "DtxMouse.h"
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	DtxMouse dtxMouse{};
	dtxMouse.GetApp()->Loop();
	return 0;
}
