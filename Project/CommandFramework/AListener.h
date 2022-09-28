#pragma once
#include "ACommand.h"

class AListener
{
public:
	void virtual operator()(ACommand* command) = 0;
};


