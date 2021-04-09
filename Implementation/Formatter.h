#pragma once
#include "Image.h"
#include <string>

class Formatter
{
protected:
	string filePath;
public:
	Formatter(string s) : filePath(s) {}
	//Formatter() = default;
	
	//virtual Layer* inFormat(Layer*) = 0;
	//virtual void outFormat(Image*) = 0;
};

