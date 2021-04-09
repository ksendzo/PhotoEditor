#pragma once
#include "Operation.h"
#include <math.h>
#include <algorithm>

class Power : public Operation {
public:
	int arg;
	Power(int a) : arg(a) {}

	void fun(Pixel& pixel) override {
		pixel.R = (int)pow(pixel.R, arg);
		pixel.G = (int)pow(pixel.G, arg);
		pixel.B = (int)pow(pixel.B, arg);
	}
};

class Logarithm : public Operation {
public:
	Logarithm() {}

	void fun(Pixel& pixel) override {
		pixel.R = (int)log(pixel.R);
		pixel.G = (int)log(pixel.G);
		pixel.B = (int)log(pixel.B);
	}
};

class Absolute : public Operation {
public:
	Absolute(){}

	void fun(Pixel& pixel) override {
		pixel.R = abs(pixel.R);
		pixel.G = abs(pixel.G);
		pixel.B = abs(pixel.B);
	}
};

class Minimal : public Operation {
public:
	int arg;
	Minimal(int a) : arg(a) {}

	void fun(Pixel& pixel) override {
		pixel.R = min(pixel.R, arg);
		pixel.G = min(pixel.G, arg);
		pixel.B = min(pixel.B, arg);
	}
};

class Maximum : public Operation {
public:
	int arg;
	Maximum( int a) : arg(a) {}

	void fun(Pixel& pixel) override {
		pixel.R = max(pixel.R, arg);
		pixel.G = max(pixel.G, arg);
		pixel.B = max(pixel.B, arg);
	}
};
