#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <set>
#include "Rect.h"
#include "json.hpp"

using namespace std;
using nlohmann::json;

class Selection {
	set<Rect> Rects;
	bool active = true;
	string name;

public:
	Selection() = default;
	Selection(string n) :name(n) {}
	Selection(const Selection&); // TREBALO BI DA MOZE I BEZ OVOGA

	/*Selection(string s, pair<int, int> coor, pair<int, int> dim):name(s){
		Rects.insert(*(new Rect(coor, dim)));
	} */
		

	string getName() const;

	set<Rect>& getRects();

	bool isActive() const;
	void setActive(bool);

	bool isInSelection(pair<int, int>) const;

	static Selection* createSelection();

	friend ostream& operator<<(ostream&, Selection&);

	friend bool operator<(const Selection& s1, const Selection& s2) {
		return s1.name < s2.name;
	}

	friend void to_json(json& j, const Selection& l);
	friend void from_json(const json& j, Selection& l);

};

