#pragma once

#include "Render.h"
#include <memory>

class RenderOpengl : public Render
{
public:
	RenderOpengl();
	~RenderOpengl();

	void run() override;
private:
	class Impl;
	std::unique_ptr<Impl> m_impl;
};