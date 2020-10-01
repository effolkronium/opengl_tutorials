#pragma once

#include "IRender.h"

class Render : public IRender
{
public:
	Render();
	~Render();

	virtual void run() = 0;
};