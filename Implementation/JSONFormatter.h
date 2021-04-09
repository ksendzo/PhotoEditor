#pragma once
#include "Formatter.h"
#include "json.hpp"

using json = nlohmann::json;

class JSONFormatter :
	public Formatter
{
public:
	JSONFormatter(string s) :Formatter(s) {}

	void outFormat(CompositeFunction* cf);
	void inFormat(CompositeFunction* cf);

	void outFormat(Image* im);
	void inFormat(Image* im);
};

