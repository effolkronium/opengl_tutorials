#pragma once

#include "IRenderCreator.h"

class RenderCreatorOpengl : public IRenderCreator
{
public:
	std::unique_ptr<IRender> create() override;
};