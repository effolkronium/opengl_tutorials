#pragma once

#include "Render.h"

class RenderOpengl : public Render
{
public:
	RenderOpengl();

	void run() override;
};