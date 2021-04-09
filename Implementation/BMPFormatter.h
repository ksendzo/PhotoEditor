#pragma once
#include "Formatter.h"

class Layer;

class BMPFormatter :
	public Formatter
{
public:
	BMPFormatter(string fP) :Formatter(fP) {}

	Layer* inFormat(Layer*);
	void outFormat(Image*);
};

