#pragma once

#include "IRenderCreator.h"

class RenderCreatorVulkan : public IRenderCreator
{
public:
	std::unique_ptr<IRender> create() override;
};