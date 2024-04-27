#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include "IOUtils.h"
#include "Rect.h"

IOUtils::IOUtils() {}

IOUtils::~IOUtils() {}

void IOUtils::read(int& binWidth, int& binHeight, int& nbItems, std::vector<Rect>& rectList)
{
    std::ifstream file("../../../data/binpacking2d-01.bp2d");
    if (!file.is_open()) {
        std::cout << "Erreur lors de l'ouverture du fichier." << std::endl;
        return;
    }

    std::string line;
    getline(file, line); getline(file, line); // Ignore les deux premières lignes

    getline(file, line);
    std::istringstream fileStream(line);
    std::string key;
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
        std::istringstream rectStream(line);
        int tmpId; int tmpWidth; int tmpHeight;
        rectStream >> tmpId >> tmpWidth >> tmpHeight;
        Rect tmpRect(tmpId, tmpWidth, tmpHeight);
        rectList.push_back(tmpRect);
    }

    file.close();
}