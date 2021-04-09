#pragma once
#include "cOperation.h"
#include "BasicOperations.h"
#include "MoreOperations.h"
#include "PredefinedFunctions.h"
#include <map>
#include <vector>
#include <string>
#include "json.hpp"
using nlohmann::json;

class CompositeFunction : public cOperation {	
public:
	vector<Operation*>& listOfOperations;
	CompositeFunction(vector<Operation*>& l): listOfOperations(l) {}
	
	void fun(Pixel& pixel) override {
		for (Operation* it : listOfOperations)
				it->fun(pixel);
	}

	friend void to_json(json& j, const CompositeFunction& p);
	friend void from_json(const json& j, CompositeFunction& p);
};


