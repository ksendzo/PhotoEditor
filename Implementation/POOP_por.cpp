// POOP_projekat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Layer.h"
#include <string>
#include <windows.data.json.h>
#include "Selection.h"
#include "Image.h"
#include "Rect.h"
#include "BMPFormatter.h"
#include "PAMFormatter.h"
#include "JSONFormatter.h"
using namespace std;

void addImage(Image*& im) {
    im = new Image;
}

void addNewLayer(Image* im) {
    cout << "1: Add an empty Layer with old dimensions" << endl
        << "2: Add an empty Layer with new dimensions" << endl
        << "3: Add a Layer with Photo" << endl;
    
    int meni, a, b;
    string s;
    std::cin >> meni;
    switch (meni)
    {
    case 1: 
        im->addLayer(); 
        break;
    case 2: 
        cout << "set new Dimensions" << endl;
        std::cin >> a >> b;
        im->addLayer(make_pair(a, b));
        break;
    case 3: 
        cout << "set Photo Path" << endl;
        std::cin >> s;
        im->addLayer(s);
        break;
    default:
        cout << "BAD INPUT" << endl;
        break;
    }
}

void addNewSelection(Image* im) {
    cout << "imeSelekcije: x y h w | x y w h |..." << endl;
    string s;
    std::cin.ignore();
    getline(std::cin, s);

    regex rx("(.+):(.*)");

    smatch result;
    string sName;
    if (regex_match(s, result, rx)) {
        sName = result.str(1);
        s = result.str(2);
    }

    Selection* newSelection = new Selection(sName);

    regex rx2("([^\\|]+)\\|");
    sregex_iterator begin(s.begin(), s.end(), rx2);
    sregex_iterator end;

    while (begin != end) {
        result = *begin;
        string rec = result.str(1);
        int x, y, w, h;

        regex rr(" (.+) (.+) (.+) (.+) ");
        smatch xywh;
        regex_match(rec, xywh, rr);

        x = stoi(xywh.str(1));
        y = stoi(xywh.str(2));
        h = stoi(xywh.str(3));
        w = stoi(xywh.str(4));

        Rect pom(make_pair(x, y), make_pair(h, w));

        newSelection->getRects().insert(pom);
        begin++;
    }
    im->addSelection(*newSelection);
}

void addNewCompositeFunction(Image* im) {
    cout << "name?" << endl;
    string name;
    cin >> name;
    vector<Operation*>* lOp = new vector<Operation*>;

    cout << "1: add x" << endl
        << "2: sub x" << endl
        << "3: rsub x" << endl
        << "4: mul x" << endl
        << "5: div x" << endl
        << "6: rdiv x" << endl
        << "7: pow x" << endl
        << "8: log" << endl
        << "9: abs" << endl
        << "10: min x" << endl
        << "11: max x" << endl
        << "12: inversion" << endl
        << "13: makeGray" << endl
        << "14: make black&white" << endl
        << "15: mediana" << endl
        << "16: composite function" << endl
        << "17: transparency x" << endl
        << "0: end" << endl;
    int meni, arg;
    string s;
    std::cin >> meni;
    while (meni) {
        if ((meni > 0 && meni <= 7) || (meni == 10 || meni == 11 || meni == 17))
            std::cin >> arg;
        if (meni == 16) {
            std::cout << "Name?" << endl;
            cin >> s;
        }

        switch (meni)
        {
        case 1: lOp->push_back(new Addition(arg)); break;
        case 2: lOp->push_back(new Subtraction(arg)); break;
        case 3: lOp->push_back(new rSubtraction(arg)); break;
        case 4: lOp->push_back(new Multiplication(arg)); break;
        case 5: lOp->push_back(new Division(arg)); break;
        case 6: lOp->push_back(new rDivision(arg)); break;
        case 7: lOp->push_back(new Power(arg)); break;
        case 8: lOp->push_back(new Logarithm); break;
        case 9: lOp->push_back(new Absolute); break;
        case 10: lOp->push_back(new Minimal(arg)); break;
        case 11: lOp->push_back(new Maximum(arg)); break;
        case 12: lOp->push_back(new Inversion); break;
        case 13: lOp->push_back(new Gray); break;
        case 14: lOp->push_back(new BlackWhite); break;
        case 15: lOp->push_back(new Mediana); break;
        case 16: lOp->insert(lOp->end(), im->getCompositeOperation(s)->listOfOperations.begin(), im->getCompositeOperation(s)->listOfOperations.end()); break;
        case 17: lOp->push_back(new Transparency(arg)); break;

        default:
            cout << "BAD INPUT" << endl;
            break;
        }
        cin >> meni;
    }
    im->createCompositeOperation(name, *lOp);

}

void doOperation(Image* im) {
    cout << "1: add x" << endl
        << "2: sub x" << endl
        << "3: rsub x" << endl
        << "4: mul x" << endl
        << "5: div x" << endl
        << "6: rdiv x" << endl
        << "7: pow x" << endl
        << "8: log" << endl
        << "9: abs" << endl
        << "10: min x" << endl
        << "11: max x" << endl
        << "12: inversion" << endl
        << "13: makeGray" << endl
        << "14: make black&white" << endl
        << "15: mediana" << endl
        << "16: composite function" << endl
        << "17: transparency x" << endl;
    int meni, arg;
    string s;
    std::cin >> meni;
    if ((meni > 0 && meni <= 7) || (meni == 10 || meni == 11 || meni == 17))
        std::cin >> arg;
    if (meni == 16) {
        std::cout << "Name?" << endl;
        cin >> s;
    }
    
    switch (meni)
    {
    case 1: im->add(arg); break;
    case 2: im->sub(arg); break;
    case 3: im->rsub(arg); break;
    case 4: im->mul(arg); break;
    case 5: im->div(arg); break;
    case 6: im->rdiv(arg); break;
    case 7: im->pow(arg); break;
    case 8: im->logar(); break;
    case 9: im->abso(); break;
    case 10: im->mini(arg); break;
    case 11: im->maxi(arg); break;
    case 12: im->invers(); break;
    case 13: im->graySh(); break;
    case 14: im->blacAwhite(); break;
    case 15: im->median(); break;
    case 16: im->doCompositeFunction(s); break;
    case 17: im->transp(arg); break;

    default:
        break;
    }
}

void activateLS(Image* im) {
    cout << "1: (de)Activate a Layer" << endl
        << "2: Is a Layer active" << endl
        << "3: (de)Activate a Selection" << endl
        << "4: Is a Selection active" << endl;
    int meni, l;
    bool b;
    string s;
    std::cin >> meni;
    
    switch (meni)
    {
    case 1: 
        cout << "Layer val" << endl;
        std::cin >> l >> b;
        im->setLayerActive(l, b);
        break;
    case 2:
        cout << "Layer?" << endl;
        std::cin >> l;
        cout << "Layer " << l << " is ";
        if (im->getLayerActive(l))
            cout << "active" << endl;
        else
            cout << "not active" << endl;
        break;
    case 3:
        cout << "Selection val" << endl;
        std::cin >> s >> b;
        im->setSelectionActive(s, b);
        break;
    case 4:
        cout << "Selection name" << endl;
        std::cin >> s;
        cout << "Selection " << s << " is ";
        if (im->getSelectionActive(s))
            cout << "active" << endl;
        else
            cout << "not active" << endl;
        break;
    default:
        break;
    }
 }
string saveCF(Image* im, string name) {
    string filePath = "outputFiles\\" + name + ".fun";

    JSONFormatter jf(filePath);
    jf.outFormat(im->getCompositeOperation(name));
    return filePath;
}

void saveImage(Image* im) {
    cout << "enter new Image path" << endl;
    
    string filePath;
    std::cin >> filePath;

    regex rbmp("(.*)\.bmp");
    regex rpam("(.*)\.pam");
    regex rjson("(.*)\.json");

    smatch res;
    if (regex_match(filePath, res, rbmp)) {
        BMPFormatter bf(filePath);
        bf.outFormat(im);
    }

    if (regex_match(filePath, res, rpam)) {
        PAMFormatter pm(filePath);
        pm.outFormat(im);
    }

    if (regex_match(filePath, res, rjson)) {

        for (map<string, CompositeFunction*>::iterator it = im->getMap().begin(); it != im->getMap().end(); it++) {
            im->cFpath.push_back(saveCF(im, it->first));
        }

        JSONFormatter jsf(filePath);
        jsf.outFormat(im);
    }

    
}

void saveCompositeFunction(Image* im) {
    cout << "enter function name" << endl;
    string name;
    cin >> name;
    saveCF(im, name);
}

CompositeFunction* openOldCompositeFunction(Image* im, string path) {
    JSONFormatter jsf(path);
    vector<Operation*>* pom = new vector<Operation*>;
    CompositeFunction* cf = new CompositeFunction(*pom);
    jsf.inFormat(cf);
    string name = path.substr(0, path.length() - 4);
    im->getMap()[name] = cf;
    return cf;
}

void openOldProject(Image*& im) {
    cout << "Enter JSON file path" << endl;

    string s;
    std::cin >> s;

    im = new Image;
    JSONFormatter jsf(s);
    jsf.inFormat(im);    

    for (string s : im->cFpath) {
        
        CompositeFunction* cf = openOldCompositeFunction(im, s);
    }
}

void openOldCF(Image* im) {
    cout << "path" << endl;
    string path;
    cin >> path;
    openOldCompositeFunction(im, path);
}

void endProject(Image* im) {
    cout << "Do you want to save your project? y/n" << endl;
    char c;
    std::cin >> c;
    if (c == 'y') 
        saveImage(im);
    
}

int main()
{
    int meni = -1;
    Image* im = nullptr;

    while (meni) {
        cout << "1: Create new Image" << endl
            << "2: Add new Layer" << endl
            << "3: Add new Selection" << endl
            << "4: Add new Composite Operation" << endl
            << "5: Do some operation" << endl
            << "6: (De)activate some Layer/Selection" << endl
            << "7: Save Image" << endl
            << "8: Save Composite Function" << endl
            << "9: Open old Composite Function" << endl
            << "10: Open old project" << endl
            << "0: End project" << endl;

        std::cin >> meni;

        switch (meni)
        {
        case 1: addImage(im); break;
        case 2: addNewLayer(im); break;
        case 3: addNewSelection(im); break;
        case 4: addNewCompositeFunction(im); break;
        case 5: doOperation(im); break;
        case 6: activateLS(im); break;
        case 7: saveImage(im); break;
        case 8: saveCompositeFunction(im); break;
        case 9: openOldCF(im); break;
        case 10: openOldProject(im); break;
        case 0: endProject(im); break;
        default: cout << "BAD INPUT" << endl;
            break;
        }
        cout << endl;
    }


    std::cout << "Hello World!\n";

    return 0;
}

