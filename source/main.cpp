#include "RenderCreatorOpengl.h"

int main()
{
	auto render = RenderCreatorOpengl{}.create();
	render->run();
}