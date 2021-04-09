#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include "Pixel.h"
#include <string>
#include <fstream>
#include "json.hpp"

using namespace std;
using nlohmann::json;
class Layer
{
	bool active = true;
	vector<vector<Pixel>> matrix;
	pair<int, int> dimensions;

public:
	friend class BMPFromatter;

	Layer() = default;
	Layer(pair<int, int>); // pravljenje Layera sa zadatom visinom i sirinom providnih pixela
	Layer(string photoPath);
	Layer(const Layer& l);

	void resizeLayer(pair<int, int>); // popuni praznim pixelima ako je novi sloj veci

	bool isActive();
	void setActive(bool);

	vector<vector<Pixel>>& getMatrix();
	pair<int, int>& getDimensions();

	Pixel& getPixel(pair<int, int> d);

	friend ostream& operator<<(ostream& it, Layer& l);

	friend void to_json(json& j, const Layer& l);
	friend void from_json(const json& j, Layer& l);
};

#endif