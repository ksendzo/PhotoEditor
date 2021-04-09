#pragma once
#include <iostream>
#include "json.hpp"
using namespace std;
using nlohmann::json;
class Rect
{
	
public:
	pair<int, int> coor;
	pair<int, int> dimensions;
	
	Rect(pair<int,int>, pair<int,int>);
	Rect(const Rect&) = default;
	Rect(){}
	friend ostream& operator<<(ostream&, Rect&);
	bool operator<(Rect&);
	bool operator<(const Rect&);
	//friend bool operator<(Rect&, Rect&);

	friend void to_json(json& j, const Rect& l);
	friend void from_json(const json& j, Rect& l);

	friend bool operator<(Rect& r1, Rect& r2);
	friend bool operator<(const Rect& r1, const Rect& r2);
};

