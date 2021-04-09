#include "Layer.h"
#include <conio.h>
#include <Windows.h>
#include <regex>
#include "BMPFormatter.h"
#include "PAMFormatter.h"

ostream& operator<<(ostream& it, Layer& l) {
	for (int i = 0; i < (int)l.matrix.size(); i++) {
		for (int j = 0; j < (int)l.matrix.at(i).size(); j++)
			it << l.matrix.at(i).at(j) << " _ " << endl;
		it << endl;
	}
	return it;
}

Layer::Layer(pair<int, int> d):dimensions(d) {
	matrix.resize(dimensions.first);
	for (vector<Pixel>& var : matrix)
	{
		var.resize(dimensions.second); // dodaj pixele
		for (Pixel& it : var)
			it.A = it.R = it.G = it.B = 0;
	}
}

Layer::Layer(string photoPath) {
	regex rbmp("(.*)\.bmp");
	regex rpam(".*\.pam");
	smatch res;
	if (regex_match(photoPath, res, rbmp)) {
		BMPFormatter bf(photoPath);
		bf.inFormat(this);
	}
		
	if (regex_match(photoPath, res, rpam)) {
		PAMFormatter pm(photoPath);
		pm.inFormat(this);
	}

} 

Layer::Layer(const Layer& l)
{
	matrix.resize(l.matrix.size());
	for (int i = 0; i < (int)l.matrix.size(); i++) {
		matrix.at(i).resize(l.matrix.at(i).size());
		for (int j = 0; j < (int)l.matrix.at(i).size(); j++)
			matrix.at(i).at(j) = Pixel(l.matrix.at(i).at(j));
	}
	dimensions = make_pair(l.dimensions.first, l.dimensions.second);
}

void Layer::resizeLayer(pair<int, int> newDim)
{
	if (newDim.first > dimensions.first) {
		matrix.resize(newDim.first);
		for (int i = dimensions.first; i < newDim.first; i++) {
			//matrix.resize(dimensions.second);
			for (int j = 0; j < dimensions.second; j++)
				matrix.at(i).push_back(Pixel(0, 0, 0, 0));
		}
		dimensions = make_pair(matrix.size(), dimensions.second);
	}
	
	if (newDim.second > dimensions.second) {
		for (int i = 0; i < newDim.first; i++) {
			//matrix.resize(newDim.second);
			for (int j = dimensions.second; j < newDim.second; j++)
				matrix.at(i).push_back(Pixel(0, 0, 0, 0));
		}
		dimensions = make_pair(dimensions.first, newDim.second);
	}
		
}


bool Layer::isActive()
{
	return active;
}

void Layer::setActive(bool a)
{
	active = a;
}

vector<vector<Pixel>>& Layer::getMatrix()
{
	return matrix;
}

pair<int, int>& Layer::getDimensions()
{
	return dimensions;
}

Pixel& Layer::getPixel(pair<int, int> d) 
{
	return matrix.at(d.first).at(d.second);
}

void to_json(json& j, const Layer& l)
{
	j = json{ {"active", l.active}, {"matrix", l.matrix} };
}

void from_json(const json& j, Layer& l)
{
	j.at("active").get_to(l.active);
	j.at("matrix").get_to(l.matrix);
}
