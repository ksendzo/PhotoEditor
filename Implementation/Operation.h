#pragma once
#include "Pixel.h"

class Operation
{
public:
	Operation() = default;
	virtual void fun(Pixel& p) =  0;
};

