#pragma once
#include <vector>
#include <set>	
#include <utility>
#include "Layer.h"
#include "Selection.h"
#include "BasicOperations.h"
#include "MoreOperations.h"
#include "CompositeFunction.h"
#include "PredefinedFunctions.h"
#include "cOperation.h"
#include "json.hpp"
//#include "Formatter.h"
//#include "BMPFormatter.h"
//#include "PAMFormatter.h"
//#include "JSONFormatter.h"
using nlohmann::json;

class JSONFormatter;
class Image
{
	pair<int, int> dimensions;
	vector<Layer> layers;
	map<string, Selection> selections;
	map<string, CompositeFunction*> compositeOperations;
	

	void doOperation(Operation* op);
	void doCOperation(cOperation* cop);

	void addResizeLayer(Layer& l);
	bool isThereAnActiveSelection();
	bool isPixelActive(pair<int, int>);

public:
	vector<string> cFpath;
	friend class BMPFormatter;
	friend class PAMFormatter;
	friend class JSONFormatter;
	Image() = default;
	~Image();

	map<string, CompositeFunction*>& getMap() { return compositeOperations; }

	void addLayer(); // dodaje sloj trenutnih dimenzija
	void addLayer(pair<int, int>);
	void addLayer(string); // dodaje sliku kao sloj

	void addSelection(Selection&);

	Pixel getPixel(pair<int, int>);

	bool getLayerActive(int);
	void setLayerActive(int, bool);

	bool getSelectionActive(string);
	void setSelectionActive(string, bool);
	
	void add(int arg);
	void sub(int arg);
	void rsub(int arg);
	void mul(int arg);
	void div(int arg);
	void rdiv(int arg);

	void pow(int arg);
	void logar();
	void abso();
	void mini(int arg);
	void maxi(int arg);

	void createCompositeOperation(string n, vector<Operation*>&);
	void doCompositeFunction(string);
	CompositeFunction* getCompositeOperation(string);
	


	void invers();
	void graySh();
	void blacAwhite();
	void median();

	void transp(int);

	friend ostream& operator<<(ostream&, Image&);

	friend void to_json(json& j, const Image& l);
	friend void from_json(const json& j, Image& l);
	
};

