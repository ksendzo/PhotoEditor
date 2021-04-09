#pragma once
#include "Operation.h"
#include "Pixel.h"
#include <vector>

class Inversion : public Operation {
public:
	void fun(Pixel& pixel) override {
		pixel.R = 255 - pixel.R;
		pixel.G = 255 - pixel.G;
		pixel.B = 255 - pixel.B;
	}
};

class Gray : public Operation {
public: 
	void fun(Pixel& pixel) override {
		int i = (pixel.R + pixel.G + pixel.B) / 3;
		pixel.R = pixel.G = pixel.B = i;
	}
};

class BlackWhite : public Operation {
public:
	void fun(Pixel& pixel) override {
		if ((pixel.R + pixel.G + pixel.B) / 3 < 127)
			pixel.R = pixel.G = pixel.B = 0;
		else
			pixel.R = pixel.G = pixel.B = 255;

	}
};

