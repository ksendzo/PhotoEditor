#include "CompositeFunction.h"

void to_json(json& ji, const CompositeFunction& p)
{
	// imam vektor pokazivaca na neke funkcije sa nekim argumentima
	json j;
	for (Operation* op: p.listOfOperations) {
		cout << typeid(*op).name() << endl;
		if (dynamic_cast<Addition*>(op))
			j.push_back({ {"type", "Addition"}, {"arg", ((Addition*)op)->arg } });
		if (dynamic_cast<Subtraction*>(op))
			j.push_back({ {"type", "Subtraction"}, {"arg", ((Subtraction*)op)->arg } });
		if (dynamic_cast<rSubtraction*>(op))
			j.push_back({ {"type", "rSubtraction"}, {"arg", ((rSubtraction*)op)->arg } });
		if (dynamic_cast<Multiplication*>(op))
			j.push_back({ {"type", "Multiplication"}, {"arg", ((Multiplication*)op)->arg } });
		if (dynamic_cast<Division*>(op))
			j.push_back({ {"type", "Division"}, {"arg", ((Division*)op)->arg} });
		if (dynamic_cast<rDivision*>(op))
			j.push_back({ {"type", "rDivision"}, {"arg", ((rDivision*)op)->arg } });
		if (dynamic_cast<Transparency*>(op))
			j.push_back({ {"type", "Transparency"}, {"arg", ((Transparency*)op)->arg } });

		if (dynamic_cast<Power*>(op))
			j.push_back({ {"type", "Power"}, {"arg", ((Power*)op)->arg } });
		if (dynamic_cast<Logarithm*>(op))
			j.push_back({ {"type", "Logarithm" } });
		if (dynamic_cast<Absolute*>(op))
			j.push_back({ {"type", "Absolute"} });
		if (dynamic_cast<Minimal*>(op))
			j.push_back({ {"type", "Minimal"}, {"arg", ((Minimal*)op)->arg } });
		if (dynamic_cast<Maximum*>(op))
			j.push_back({ {"type", "Maximum"}, {"arg", ((Maximum*)op)->arg } });

		if (dynamic_cast<Mediana*>(op))
			j.push_back({ {"type", "Mediana" } });
		
		if (dynamic_cast<Inversion*>(op))
			j.push_back({ {"type", "Inversion" } });
		if (dynamic_cast<Gray*>(op))
			j.push_back({ {"type", "Gray" } });
		if (dynamic_cast<BlackWhite*>(op))
			j.push_back({ {"type", "BlackWhite" } });
	}
	ji = j;
}

void from_json(const json& j, CompositeFunction& p)
{
	vector<Operation*>* lop = new vector<Operation*>;
	for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it) {
		string name = it->at("type");
		//name.append(0);
		int arg = 0;
		if (((string)"Addition").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new Addition(arg));
		}
		if (((string)"Subtraction").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new Subtraction(arg));
		}
		if (((string)"rSubtraction").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new rSubtraction(arg));
		}
		if (((string)"Multiplication").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new Multiplication(arg));
		}
		if (((string)"Division").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new Division(arg));
		}
		if (((string)"rDivision").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new rDivision(arg));
		}
		if (((string)"Transparency").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new Transparency(arg));
		}

		if (((string)"Power").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new Power(arg));
		}
		if (((string)"Logarithm").find(name) != string::npos) {
			lop->push_back(new Logarithm);
		}
		if (((string)"Absolute").find(name) != string::npos) {
			lop->push_back(new Absolute);
		}
		if (((string)"Minimal").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new Minimal(arg));
		}
		if (((string)"Maximum").find(name) != string::npos) {
			arg = it->at("arg");
			lop->push_back(new Maximum(arg));
		}

		if (((string)"Mediana").find(name) != string::npos) {
			lop->push_back(new Mediana);
		}
		if (((string)"Inversion").find(name) != string::npos) {
			lop->push_back(new Inversion);
		}
		if (((string)"Gray").find(name) != string::npos) {
			lop->push_back(new Gray);
		}
		if (((string)"BlackWhite").find(name) != string::npos){
			lop->push_back(new BlackWhite);
		}

		
	}
	p.listOfOperations = *lop;
}
