#include "DtxObjectToWorld.h"
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	DtxObjectToWorld dtxObjectToWorld{};
	dtxObjectToWorld.GetApp()->Loop();
	return 0;
}
