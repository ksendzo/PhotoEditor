#include "Selection.h"

Selection::Selection(const Selection& oldS)
{
	for (Rect ir : oldS.Rects)
		Rects.insert(ir);
	name = oldS.name;
}



string Selection::getName() const
{
	return name;
}

set<Rect>& Selection::getRects()
{
	return Rects;
}

bool Selection::isActive() const
{
	return active;
}

void Selection::setActive(bool a)
{
	active = a;
}

bool Selection::isInSelection(pair<int, int> p) const
{
	for (set<Rect>::iterator it = Rects.begin(); it != Rects.end(); it++) 
		if ((it)->coor.first <= p.first && ((it)->dimensions.first + (it)->coor.first - 1) >= p.first && (it)->coor.second <= p.second && ((it)->dimensions.second + (it)->coor.second - 1) >= p.second)
			return true;
	return false;
}


Selection* Selection::createSelection()
{
	cout << "imeSelekcije: x y h w | x y w h |..." << endl;
	string s;
	getline(cin, s);

	regex rx("(.+):(.*)");

	smatch result;
	string sName;
	if (regex_match(s, result, rx)) {
		sName = result.str(1);
		s = result.str(2);
	}

	Selection* newSelection = new Selection(sName);

	regex rx2("([^\\|]+)\\|");
	sregex_iterator begin(s.begin(), s.end(), rx2);
	sregex_iterator end;
	
	while (begin != end) {
		result = *begin;
		string rec = result.str(1);
		int x, y, w, h;

		regex rr(" (.+) (.+) (.+) (.+) ");
		smatch xywh;
		regex_match(rec, xywh, rr);

		x = stoi(xywh.str(1));
		y = stoi(xywh.str(2));
		h = stoi(xywh.str(3));
		w = stoi(xywh.str(4));

		Rect pom(make_pair(x,y), make_pair(h, w));

		newSelection->Rects.insert(pom);
		begin++;
	}

	return newSelection;
}

ostream& operator<<(ostream& it, Selection& s)
{
	it << s.name << endl;
	for (Rect p : s.Rects)
		it << "\t" << p;
	return it << endl;
}

void to_json(json& j, const Selection& l)
{
	j = json{ {"active", l.active}, {"name", l.name}, {"rects", l.Rects} };
}

void from_json(const json& j, Selection& l)
{
	j.at("active").get_to(l.active);
	j.at("name").get_to(l.name);
	j.at("rects").get_to(l.Rects);
}
