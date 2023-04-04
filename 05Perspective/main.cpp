#include "DtxPerspective.h"
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	DtxPerspective dtxPerspective{};
	dtxPerspective.GetApp()->Loop();
	return 0;
}
