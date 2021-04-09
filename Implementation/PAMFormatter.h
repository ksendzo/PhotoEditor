#pragma once
#include "Formatter.h"
#include <string>
#include <fstream>
using namespace std;

class PAMFormatter :
	public Formatter
{
	
public:
	PAMFormatter(string s) :Formatter(s) {}

	Layer* inFormat(Layer*);
	void outFormat(Image*);

};

