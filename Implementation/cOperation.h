#pragma once
#include <vector>
#include <algorithm>
#include "Operation.h"
#include "Layer.h"
#include "Pixel.h"
#include "Selection.h"

class cOperation : public Operation {
protected:
	vector<Layer>* lay;
	pair<int, int>* coor;
	int* nmb;

public:
	cOperation():lay(nullptr), coor(nullptr), nmb(nullptr) {}

	void setLayersAndDim(vector<Layer>* l, pair<int, int>*p, int* n) {
		lay = l;
		coor = p;
		nmb = n;
	}
};

class Mediana : public cOperation {
public:
	//Mediana() = default;
	void fun(Pixel& pixel) override {
		vector<int> R, G, B;
		R.push_back(pixel.R);
		G.push_back(pixel.G);
		B.push_back(pixel.B);

		if (coor->first > 0) {
			pair<int, int> tr(*coor);
			tr.first -= 1;
			R.push_back(lay->at(*nmb).getPixel(tr).R);
			G.push_back(lay->at(*nmb).getPixel(tr).G);
			B.push_back(lay->at(*nmb).getPixel(tr).B);
		}
		if (coor->second > 0) {
			pair<int, int> tr(*coor);
			tr.second -= 1;
			R.push_back(lay->at(*nmb).getPixel(tr).R);
			G.push_back(lay->at(*nmb).getPixel(tr).G);
			B.push_back(lay->at(*nmb).getPixel(tr).B);
		}
		if (coor->first < lay->at(0).getDimensions().first - 1) {
			pair<int, int> tr(*coor);
			tr.first += 1;
			R.push_back(lay->at(*nmb).getPixel(tr).R);
			G.push_back(lay->at(*nmb).getPixel(tr).G);
			B.push_back(lay->at(*nmb).getPixel(tr).B);
		}
		if (coor->second < lay->at(0).getDimensions().second - 1) {
			pair<int, int> tr(*coor);
			tr.second += 1;
			R.push_back(lay->at(*nmb).getPixel(tr).R);
			G.push_back(lay->at(*nmb).getPixel(tr).G);
			B.push_back(lay->at(*nmb).getPixel(tr).B);
		}

		sort(R.begin(), R.end());
		sort(G.begin(), G.end());
		sort(B.begin(), B.end());

		int i = R.size() / 2;

		pixel.R = R.at(i);
		pixel.G = G.at(i);
		pixel.B = B.at(i);

	}
};

