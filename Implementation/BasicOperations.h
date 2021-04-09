#pragma once
#include "Operation.h"

class Addition : public Operation {
public:
	int arg;
	Addition(int a):arg(a) {}

	void fun(Pixel& pixel) override {
		pixel.R += arg;
		pixel.G += arg;
		pixel.B += arg;
	}
};

class Subtraction : public Operation {
public:
	int arg;
	Subtraction(int a): arg(a){}

	void fun(Pixel& pixel) override {
		pixel.R -= arg;
		pixel.G -= arg;
		pixel.B -= arg;
	}
};

class rSubtraction : public Operation {
public:
	int arg;
	rSubtraction(int a) : arg(a) {}

	void fun(Pixel& pixel) override {
		pixel.R = arg - pixel.R;
		pixel.G = arg - pixel.G;
		pixel.B = arg - pixel.B;
	}
};

class Multiplication : public Operation {
public:
	int arg;
	Multiplication(int a) : arg(a) {}

	void fun(Pixel& pixel) override {
		pixel.R *= arg;
		pixel.G *= arg;
		pixel.B *= arg;
	}
};


class Division : public Operation {
public:
	int arg;
	Division(int a) : arg(a) {}

	void fun(Pixel& pixel) override {
		pixel.R /= arg;
		pixel.G /= arg;
		pixel.B /= arg;
	}
};

class rDivision : public Operation {
public:
	int arg;
	rDivision(int a) : arg(a) {}

	void fun(Pixel& pixel) override {
		pixel.R = arg / pixel.R;
		pixel.G = arg / pixel.G;
		pixel.B = arg / pixel.B;
	}
};

class Transparency : public Operation {
public:
	int arg;
	Transparency(int a) :arg(a) {}
	void fun(Pixel& pixel) override {
		pixel.A = arg;
	}
};
