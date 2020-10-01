#pragma once

#include "IRender.h"
#include <memory>

class IRenderCreator
{
public:
	virtual std::unique_ptr<IRender> create() = 0;
};