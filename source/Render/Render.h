#pragma once

#include "IRender.h"

class Render : public IRender
{
public:
	Render();

	virtual void run() = 0;
};