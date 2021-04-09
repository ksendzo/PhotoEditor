#include "Pixel.h"

Pixel::Pixel():R(0), G(0), B(0), A(0) {}

Pixel::Pixel(int r, int g, int b, int a) :R(r), G(g), B(b), A(a) {}

Pixel::Pixel(int r, int g, int b):R(r), G(g), B(b), A(255) {}

Pixel::Pixel(int s):R(s), G(s), B(s), A(255){}

Pixel& Pixel::operator=(const Pixel& p)
{
	R = p.R;
	G = p.G;
	B = p.B;
	A = p.A;
	return *this;
}

void Pixel::setBound()
{
	if (R > 255) R = 255;
	if (G > 255) G = 255;
	if (B > 255) B = 255;
	if (A > 255) A = 255;

	if (R < 0) R = 0;
	if (G < 0) G = 0;
	if (B < 0) B = 0;
	if (A < 0) A = 0;
}

ostream& operator<<(ostream& it, Pixel& p) {
	//it << std::hex << p.R << " " << p.G << " " << p.B << " " << p.A;
	it  << "a->" << p.A << " r->" << p.R << " g->" << p.G << " b->" << p.B;
	return it;
}

void to_json(json& j, const Pixel& p)
{
	j = json{ {"R", p.R}, {"G", p.G}, {"B", p.B}, {"A", p.A} };
}

void from_json(const json& j, Pixel& p)
{
	j.at("R").get_to(p.R);
	j.at("G").get_to(p.G);
	j.at("B").get_to(p.B);
	j.at("A").get_to(p.A);
}
