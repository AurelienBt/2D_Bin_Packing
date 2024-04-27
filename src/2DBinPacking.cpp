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
/*
void read(int & binWidth, int & binHeight, int & nbItems, vector<Rect> & rectList) {
    cout << filesystem::absolute("2DBinPacking.cpp") << endl;
	ifstream file("../../../data/binpacking2d-01.bp2d");
	if (!file.is_open()) {
		cout << "Erreur lors de l'ouverture du fichier." << endl;
		return;
	}

	string line;
    getline(file, line); getline(file, line); // Ignore les deux premières lignes

    getline(file, line);
    istringstream fileStream(line);
    string key;
    fileStream >> key >> nbItems;

    getline(file, line);
    fileStream.clear();
    fileStream.str(line);
    fileStream >> key >> binWidth;

    getline(file, line);
    fileStream.clear();
    fileStream.str(line);
    fileStream >> key >> binHeight;

    getline(file, line); getline(file, line); // Ignore les lignes \n et ITEMS
    while (getline(file, line)) {
        if (line.empty() || line == "END") {
            break;
        }
        // Stocke tous les rectangles
        istringstream rectStream(line);
        int tmpId; int tmpWidth; int tmpHeight;
        rectStream >> tmpId >> tmpWidth >> tmpHeight;
        Rect tmpRect(tmpId, tmpWidth, tmpHeight);
        rectList.push_back(tmpRect);
    }

	file.close();

}
*/
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
