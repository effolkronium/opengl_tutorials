#pragma once

#include "Render.h"

class RenderVulkan : public Render
{
public:
	RenderVulkan();

	void run() override;
};