#include "Rect.h"

Rect::Rect(pair<int,int> c, pair<int,int> d):coor(c), dimensions(d)
{
}



ostream& operator<<(ostream& it, Rect& r)
{
	return it << "x: " << r.coor.first << " y: " << r.coor.second << " h: " << r.dimensions.first << " w: " << r.dimensions.second << endl;
}

void to_json(json& j, const Rect& l)
{
	j = json{ {"coor", l.coor}, {"dim", l.dimensions } };	
}

void from_json(const json& j, Rect& l)
{
	j.at("coor").get_to(l.coor);
	j.at("dim").get_to(l.dimensions);
}

bool Rect::operator<(Rect& r2)
{
	if (coor.first < r2.coor.first)
		return true;
	if (coor.first > r2.coor.first)
		return false;

	if (coor.second < r2.coor.second)
		return true;
	if (coor.second > r2.coor.second)
		return false;

	if (dimensions.first < r2.dimensions.first)
		return true;
	if (dimensions.first > r2.dimensions.first)
		return false;

	if (dimensions.second < r2.dimensions.second)
		return true;
	if (dimensions.second > r2.dimensions.second)
		return false;

	return false;
}

bool Rect::operator<(const Rect& r2) {
	if (coor.first < r2.coor.first)
		return true;
	if (coor.first > r2.coor.first)
		return false;

	if (coor.second < r2.coor.second)
		return true;
	if (coor.second > r2.coor.second)
		return false;

	if (dimensions.first < r2.dimensions.first)
		return true;
	if (dimensions.first > r2.dimensions.first)
		return false;

	if (dimensions.second < r2.dimensions.second)
		return true;
	if (dimensions.second > r2.dimensions.second)
		return false;

	return false;
}


bool operator<(Rect& r1, Rect& r2)
{
	if (r1.coor.first < r2.coor.first)
		return true;
	if (r1.coor.first > r2.coor.first)
		return false;

	if (r1.coor.second < r2.coor.second)
		return true;
	if (r1.coor.second > r2.coor.second)
		return false;

	if (r1.dimensions.first < r2.dimensions.first)
		return true;
	if (r1.dimensions.first > r2.dimensions.first)
		return false;

	if (r1.dimensions.second < r2.dimensions.second)
		return true;
	if (r1.dimensions.second > r2.dimensions.second)
		return false;

	return false;
}

bool operator<(const Rect& r1, const Rect& r2) {
	if (r1.coor.first < r2.coor.first)
		return true;
	if (r1.coor.first > r2.coor.first)
		return false;

	if (r1.coor.second < r2.coor.second)
		return true;
	if (r1.coor.second > r2.coor.second)
		return false;

	if (r1.dimensions.first < r2.dimensions.first)
		return true;
	if (r1.dimensions.first > r2.dimensions.first)
		return false;

	if (r1.dimensions.second < r2.dimensions.second)
		return true;
	if (r1.dimensions.second > r2.dimensions.second)
		return false;

	return false;
}