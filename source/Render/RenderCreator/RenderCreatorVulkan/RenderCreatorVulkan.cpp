#include "RenderCreatorVulkan.h"
#include "RenderVulkan.h"

std::unique_ptr<IRender> RenderCreatorVulkan::create()
{
	return std::make_unique<RenderVulkan>();
}