// 2DBinPacking.cpp : définit le point d'entrée de l'application.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include "2DBinPacking.h"
#include "Rect.h"
#include "IOUtils.h"
#include "FileData.h"

using namespace std;

int main()
{
    FileData::init();

    /*cout << FileData::BIN_WIDTH << endl;
    cout << FileData::BIN_HEIGHT << endl;
    cout << FileData::NB_ITEMS << endl;
    for (const Rect& r : FileData::RECT_LIST) {
        cout << r << endl;
    }*/


    vector<Bin*> binList;
    Bin binA = Bin(1);
    Bin binB = Bin(2);
    binA.addRectangle(&FileData::RECT_LIST.at(0), 0, 0);
    binB.addRectangle(&FileData::RECT_LIST.at(1), 0, 0);
    binList.push_back(&binA);
    binList.push_back(&binB);
    FileData::binPackingToJSON(binList);

	return 0;
}
