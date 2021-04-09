#include "PAMFormatter.h"

Layer* PAMFormatter::inFormat(Layer* l)
{
	ifstream inputFile(filePath, ios::in | ios::binary);

	string s;

	getline(inputFile, s); // procitaj MAGIC NUMBER
	cout << s;
	getline(inputFile, s); // WIDTH
	cout << s;

	regex rx("WIDTH (.*)");
	smatch result;
	if (regex_match(s, result, rx)) 
		l->getDimensions().second = stoi(result.str(1));
	

	getline(inputFile, s); // HEIGHT
	cout << s;
	regex rxHeight("HEIGHT (.*)");

	if (regex_match(s, result, rxHeight)) 
		l->getDimensions().first = stoi(result.str(1));
	

	getline(inputFile, s); // DEPTH - GRAY RGB RGBA
	cout << s;
	regex rxDepth("DEPTH (.*)");
	int d = 0;
	if (regex_match(s, result, rxDepth)) 
		d = stoi(result.str(1));


	getline(inputFile, s); // maxValue
	cout << s;
	getline(inputFile, s); // TUPLTYPE
	cout << s;
	getline(inputFile, s); // END
	cout << s;

	unsigned char r,g,b,a;
	l->getMatrix().resize(l->getDimensions().first);
	for (int i = l->getDimensions().first - 1; i >= 0; i--) {
		for (int j = 0; j < l->getDimensions().second; j++) {
			inputFile.read((char*)&r, sizeof(r));
			if (d == 1) { 
				Pixel pix(r); // GRAY
				l->getMatrix().at(i).push_back(pix);
				continue;
			}
			inputFile.read((char*)&g, sizeof(g));
			inputFile.read((char*)&b, sizeof(b));
			if (d == 3) {
				Pixel pix(r, g, b); // RGB 
				l->getMatrix().at(i).push_back(pix);
				continue;
			}
			inputFile.read((char*)&a, sizeof(a));
			Pixel pix(r, g, b, 255); // RGBA
			l->getMatrix().at(i).push_back(pix);
		}
	}

	return l;
}

void PAMFormatter::outFormat(Image* im)
{
	ofstream outFile(filePath, ios::out | ios::binary);

	string s = "P7\n";
	outFile.write(s.c_str(), s.size());

	s = "WIDTH " + to_string(im->dimensions.second) + "\n";
	outFile.write(s.c_str(), s.size());

	s = "HEIGHT " + to_string(im->dimensions.first) + "\n";
	outFile.write(s.c_str(), s.size());

	s = "DEPTH 4\nMAXVAL 255\nTUPLTYPE RGB_ALPHA\nENDHDR\n";
	outFile.write(s.c_str(), s.size());
	char p;
	for(int i = im->dimensions.first - 1; i >= 0; i--)
		for (int j = 0; j < im->dimensions.second; j++) {
			Pixel pix = im->getPixel(make_pair(i, j));
			p = pix.R;
			outFile.write((char*)&p, sizeof(p));

			p = pix.G;
			outFile.write((char*)&p, sizeof(p));

			p = pix.B;
			outFile.write((char*)&p, sizeof(p));

			p = pix.A;
			outFile.write((char*)&p, sizeof(p));

		}


}
