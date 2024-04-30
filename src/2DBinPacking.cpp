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

using namespace std;

int main()
{
	int BIN_WIDTH;
	int BIN_HEIGHT;
	int NB_ITEMS;
	vector<Rect> RECT_LIST;
    IOUtils ioUtils = IOUtils();
	ioUtils.read(BIN_WIDTH, BIN_HEIGHT, NB_ITEMS, RECT_LIST);
    cout << BIN_WIDTH << endl;
    cout << BIN_HEIGHT << endl;
    cout << NB_ITEMS << endl;
    for (const Rect& r : RECT_LIST) {
        cout << r << endl;
    }

	return 0;
}
