#ifndef PIXEL_H
#define PIXEL_H
#include "json.hpp"

#include <iostream>
using namespace std;
using nlohmann::json;
class Pixel
{
public:
	int R = 0, G = 0, B = 0, A = 0;
	
	Pixel(int r, int g, int b, int a) ; // RGBA
	Pixel(int r, int g, int b);			// RGB
	Pixel(int s);						// GRAY
	Pixel();							// EMPTY
	Pixel(const Pixel&) = default;
	Pixel(Pixel&&) = default;
	~Pixel() = default;

	Pixel& operator=(const Pixel& p);

	friend ostream& operator<<(ostream& it, Pixel& p);

	void setBound();

	friend void to_json(json& j, const Pixel& p);
	friend void from_json(const json& j, Pixel& p);
};




#endif // !PIXEL_H