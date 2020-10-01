#include "RenderCreatorOpengl.h"
#include "RenderOpengl.h"

std::unique_ptr<IRender> RenderCreatorOpengl::create()
{
	return std::make_unique<RenderOpengl>();
}