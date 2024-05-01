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
    cout << FileData::BIN_WIDTH << endl;
    cout << FileData::BIN_HEIGHT << endl;
    cout << FileData::NB_ITEMS << endl;
    for (const Rect& r : FileData::RECT_LIST) {
        cout << r << endl;
    }

	return 0;
}
