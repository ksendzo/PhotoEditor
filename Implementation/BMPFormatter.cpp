#include "BMPFormatter.h"

Layer* BMPFormatter::inFormat(Layer* newLayer)
{
	
	ifstream infile(filePath, ios::in | ios::binary);
	if (!infile.is_open()) {
		cout << "GRESKA" << endl;
		return nullptr;
	}
	int offset = 0x36;
	unsigned char p;
	int first = 0; int second = 0;
	int pixelSize = 0;

	for (int i = 0; i < offset; i++) {
		infile.read((char*)&p, sizeof(p)); // ucitava 8 bita, sto je 1B tj 2h broja

		switch (i) {
		case 0xa: offset = p; break;
		case 0xb: offset += p * 0x100; break;
		case 0xc: offset += p * 0x10000; break;
		case 0xd: offset += p * 0x1000000; break;

		case 0x12: second = p; break;
		case 0x13: second += p * 0x100; break;
		case 0x14: second += p * 0x10000; break;
		case 0x15: second += p * 0x1000000; break;

		case 0x16: first = p; break;
		case 0x17: first += p * 0x100; break;
		case 0x18: first += p * 0x10000; break;
		case 0x19: first += p * 0x1000000; break;

		case 0x1C: pixelSize = p; break;
		case 0x1D: pixelSize += p * 0x100; break;
		}
	}

	newLayer->getMatrix().resize(first);
	for (int i = 0; i < first; i++)
		newLayer->getMatrix().at(i).resize(second);
	Pixel* pom = nullptr;
	int r = 0, g = 0, b = 0, a = 0;
	for (int i = first - 1; i >= 0; i--)
		for (int j = 0; j < second; j++) {
			switch (pixelSize) {
			case 32:
				infile.read((char*)&p, sizeof(p)); // ucitava 8bit sto je tacno 1 boja 0x00
				b = p;
				infile.read((char*)&p, sizeof(p));
				g = p;
				infile.read((char*)&p, sizeof(p));
				r = p;
				infile.read((char*)&p, sizeof(p));
				a = p;

				pom = new Pixel(r, g, b, a);
				break;
			case 24: 
				infile.read((char*)&p, sizeof(p)); // ucitava 8bit sto je tacno 1 boja 0x00
				b = p;
				infile.read((char*)&p, sizeof(p));
				g = p;
				infile.read((char*)&p, sizeof(p));
				r = p;
				pom = new Pixel(r, g, b);
				break;
			case 8:
				infile.read((char*)&p, sizeof(p));
				r = p;
				pom = new Pixel(r);
				break;
			}
			newLayer->getMatrix().at(i).at(j) = *pom;
			delete pom;
		}
	newLayer->getDimensions() = make_pair(first, second);
	return newLayer;
}

void BMPFormatter::outFormat(Image* im)
{
	ofstream outfile(filePath, ios::out | ios::binary);
	outfile.clear();
	unsigned char p;
	cout << "siye " << sizeof(p) << endl;
	unsigned long long size = 36 + 4 * im->dimensions.first * im->dimensions.second;
	unsigned char niz[0x36];
	cout<< "siye " << 0x36 << endl;
	niz[0] = 66;
	cout  << niz[0] << endl;
	niz[1] = 77;

	niz[2] = size % 256; // velicina fajla 4B
	niz[3] = (size / 256) % 256;
	niz[4] = (size / 65536) % 256;
	niz[5] = (size / 16777216) % 256;
	cout << "uc 0 = " << hex << (unsigned char) 0x0 << endl;

	niz[6] = 0; // ne koristi se
	niz[7] = 0;
	niz[8] = 0;
	niz[9] = 0;

	niz[10] = 54; // offset na kome pocinje niz pixela
	niz[11] = 0;
	niz[12] = 0;
	niz[13] = 0;

	niz[14] = 40; // fixno
	niz[15] = 0;
	niz[16] = 0;
	niz[17] = 0;

	niz[18] = im->dimensions.second % 256; // WIDTH
	niz[19] = (im->dimensions.second / 256) % 256;
	niz[20] = (im->dimensions.second / 65536) % 256;
	niz[21] = (im->dimensions.second / 16777216) % 256;

	niz[22] = im->dimensions.first % 256; // HEIGHT
	niz[23] = (im->dimensions.first / 256) % 256;
	niz[24] = (im->dimensions.first / 65536) % 256;
	niz[25] = (im->dimensions.first / 16777216) % 256;

	niz[26] = 1; // fixno
	niz[27] = 0;

	niz[28] = 32; // velicina Pixela u bitovima
	niz[29] = 0;

	niz[30] = 0; // fixno
	niz[31] = 0;
	niz[32] = 0;
	niz[33] = 0;

	size -= 54;

	niz[34] = (size) % 256; // memorija za smestanje Pixela (4xnumPix)
	niz[35] = (size / 256) % 256;
	niz[36] = (size / 65536) % 256;
	niz[37] = (size / 16777216) % 256;

	niz[38] = 19; // fixno
	niz[39] = 11;
	niz[40] = 0;
	niz[41] = 0;

	niz[42] = 19; // fixno
	niz[43] = 11;
	niz[44] = 0;
	niz[45] = 0;

	niz[46] = 0; // fixno
	niz[47] = 0;
	niz[48] = 0;
	niz[49] = 0;

	niz[50] = 0; // fixno
	niz[51] = 0;
	niz[52] = 0;
	niz[53] = 0;

	outfile.write((char*)&niz, 54);

	// sad upisuj pixele
	

	for(int i = im->dimensions.first - 1; i >= 0; i--)
		for (int j = 0; j < im->dimensions.second; j++) {
			Pixel pix = im->getPixel(make_pair(i, j));
			p = pix.B;
			outfile.write((char*)&p, sizeof(p));
			p = pix.G;
			outfile.write((char*)&p, sizeof(p));
			p = pix.R;
			outfile.write((char*)&p, sizeof(p));
			p = pix.A;
			outfile.write((char*)&p, sizeof(p));
		}

}
