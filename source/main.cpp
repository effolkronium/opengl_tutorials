#include "RenderOpengl.h"
#include <iostream>

int main()
try {
	RenderOpengl opengl;

	opengl.startRenderLoop();
}
catch (const std::exception& ex)
{
	std::cerr << "Main exception: " << ex.what() << std::endl;
}
catch (...)
{
	std::cerr << "\n\nUNSPESIFIED EXCEPTION!!!\n\n";
}