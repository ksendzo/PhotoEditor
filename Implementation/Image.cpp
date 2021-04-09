#include "Image.h"



void Image::doOperation(Operation* op)
{
	bool sel = isThereAnActiveSelection();
	pair<int, int> pp;
	for (pp.first = 0; pp.first < dimensions.first; pp.first++)
		for (pp.second = 0; pp.second < dimensions.second; pp.second++)
			if (!sel || isPixelActive(pp)) 
				for (vector<Layer>::iterator it = layers.begin(); it != layers.end(); it++) {
					op->fun(it->getPixel(pp));
					it->getPixel(pp).setBound();
				}
}

void Image::doCOperation(cOperation* cop)
{
	bool sel = isThereAnActiveSelection();

	vector<Layer>* nLayers = new vector<Layer>(layers); // Deep Copy (namesti Layer da ume da se kopira)

	pair<int, int>* dim = new pair<int, int>(0, 0);

	int* nmb = new int(0);

	cop->setLayersAndDim(nLayers, dim, nmb);
	
	for(int i = 0; i < dimensions.first; i++)
		for (int j = 0; j < (dimensions.second);j++)
			if(!sel || isPixelActive(*dim))
				for (*nmb = 0; *nmb < (int)layers.size(); *nmb = *nmb + 1) {
					*dim = make_pair(i, j);
					cop->fun(layers.at(*nmb).getPixel(*dim));
					layers.at(*nmb).getPixel(*dim).setBound();
				}

}

void Image::addResizeLayer(Layer& l)
{
	if (layers.size() > 0 && !(dimensions == l.getDimensions())) {
		for (vector<Layer>::iterator it = layers.begin(); it != layers.end(); it++)
			it->resizeLayer(l.getDimensions());
		dimensions = layers.at(0).getDimensions();
		l.resizeLayer(dimensions);
	}


	layers.push_back(l);

	dimensions = layers.at(0).getDimensions();
}

Image::~Image()
{
	for (map<string, CompositeFunction*>::iterator it = compositeOperations.begin(); it != compositeOperations.end(); it++) {
		delete it->second;
	}
}

void Image::addLayer()
{
	layers.push_back(*(new Layer(dimensions)));
}

void Image::addLayer(pair<int, int> p)
{
	Layer l(p);
	addResizeLayer(l);
}

void Image::addLayer(string photoPath)
{
	Layer l(photoPath);

	addResizeLayer(l);
}

void Image::addSelection(Selection& s)
{
	selections.insert(make_pair(s.getName(), s));
}


bool Image::isThereAnActiveSelection()
{
	for (map<string, Selection>::iterator it = selections.begin(); it != selections.end(); it++)
		if (it->second.isActive())
			return true;
	return false;
}

bool Image::isPixelActive(pair<int, int> d)
{
	for (map<string, Selection>::iterator it = selections.begin(); it != selections.end(); it++)
		if (it->second.isInSelection(d) && it->second.isActive())
			return true;
	return false;
}

Pixel Image::getPixel(pair<int, int> d) 
{
	Pixel pixel(0, 0, 0, 0);
	int ostatak = 255;
	for (vector<Layer>::iterator it = layers.begin(); it != layers.end() && pixel.A < 255; it++) {
		pixel.R += it->getPixel(d).R * ostatak * it->getPixel(d).A / 255 / 255;
		pixel.G += it->getPixel(d).G * ostatak * it->getPixel(d).A / 255 / 255;
		pixel.B += it->getPixel(d).B * ostatak * it->getPixel(d).A / 255 / 255;
		pixel.A += it->getPixel(d).A * ostatak / 255;	
		ostatak -= pixel.A * ostatak / 255;
	}
	return pixel;
}

bool Image::getLayerActive(int i) 
{
	return layers.at(i).isActive();
}

void Image::setLayerActive(int i, bool b)
{
	layers.at(i).setActive(b);
}

bool Image::getSelectionActive(string s)
{
	return selections[s].isActive();
}

void Image::setSelectionActive(string s, bool b)
{
	selections[s].setActive(b);
}

void Image::add(int arg)
{
	Operation* op = new Addition(arg);
	doOperation(op);
	delete op;
}

void Image::sub(int arg)
{
	Operation* op = new Subtraction(arg);
	doOperation(op);
	delete op;
}

void Image::rsub(int arg)
{
	Operation* op = new rSubtraction(arg);
	doOperation(op);
	delete op;
}

void Image::mul(int arg)
{
	Operation* op = new Multiplication(arg);
	doOperation(op);
	delete op;
}

void Image::div(int arg)
{
	Operation* op = new Division(arg);
	doOperation(op);
	delete op;
}

void Image::rdiv(int arg)
{
	Operation* op = new rDivision(arg);
	doOperation(op);
	delete op;
}

void Image::pow(int arg)
{
	Operation* op = new Power(arg);
	doOperation(op);
	delete op;
}

void Image::logar()
{
	Operation* op = new Logarithm;
	doOperation(op);
	delete op;
}

void Image::abso()
{
	Operation* op = new Absolute;
	doOperation(op);
	delete op;
}

void Image::mini(int arg)
{
	Operation* op = new Minimal(arg);
	doOperation(op);
	delete op;
}

void Image::maxi(int arg)
{
	Operation* op = new Maximum(arg);
	doOperation(op);
	delete op;
}

void Image::createCompositeOperation(string n, vector<Operation*>& l)
{
	CompositeFunction* cop = new CompositeFunction(l);
	//doCOperation(cop);
	compositeOperations[n] = cop;
}

void Image::doCompositeFunction(string s)
{
	cOperation* cop = compositeOperations[s];
	doCOperation(cop);
}

CompositeFunction* Image::getCompositeOperation(string s)
{
	return compositeOperations[s];
}


void Image::invers()
{
	Operation* op = new Inversion;
	doOperation(op);
}

void Image::graySh()
{
	Operation* op = new Gray;
	doOperation(op);
}

void Image::blacAwhite()
{
	Operation* op = new BlackWhite;
	doOperation(op);
}

void Image::median()
{
	cOperation* cop = new Mediana;
	doCOperation(cop);

}

void Image::transp(int arg)
{
	Operation* op = new Transparency(arg);
	doOperation(op);
}

ostream& operator<<(ostream& it, Image& im)
{
	for (Layer il : im.layers)
		it << il << endl;

	//for (map<string, Selection>::iterator iter = im.selections.begin(); iter != im.selections.end(); iter++)
	//	it << iter->second << endl;

	return it;
}

void to_json(json& j, const Image& l)
{
	
	j = json{ {"dimensions", l.dimensions}, {"layers", l.layers}, {"selections",l.selections}, {"cfPaths", l.cFpath} };
}

void from_json(const json& j, Image& l)
{
	j.at("dimensions").get_to(l.dimensions);
	j.at("layers").get_to(l.layers);
	j.at("selections").get_to(l.selections);
	j.at("cfPaths").get_to(l.cFpath);
}
