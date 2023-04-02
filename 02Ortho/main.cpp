#include "DtxOrtho.h"
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	DtxOrtho dtxOrtho{};
	dtxOrtho.GetApp()->Loop();
	return 0;
}
