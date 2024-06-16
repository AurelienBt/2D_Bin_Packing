#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include "FileData.h"

int FileData::BIN_WIDTH;
int FileData::BIN_HEIGHT;
int FileData::NB_ITEMS;
std::vector<Rect*> FileData::RECT_LIST;

FileData::FileData(){}
FileData::~FileData(){}

void FileData::init()
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
    fileStream >> key >> NB_ITEMS;

    getline(file, line);
    fileStream.clear();
    fileStream.str(line);
    fileStream >> key >> BIN_WIDTH;

    getline(file, line);
    fileStream.clear();
    fileStream.str(line);
    fileStream >> key >> BIN_HEIGHT;

    getline(file, line); getline(file, line); // Ignore les lignes \n et ITEMS
    while (getline(file, line)) {
        if (line.empty() || line == "END") {
            break;
        }
        // Stocke tous les rectangles
        std::istringstream rectStream(line);
        int tmpId; int tmpWidth; int tmpHeight;
        rectStream >> tmpId >> tmpWidth >> tmpHeight;
        Rect* tmpRect = new Rect(tmpId, tmpWidth, tmpHeight);
        RECT_LIST.push_back(tmpRect);
    }

    file.close();
}

void FileData::binPackingToJSON(const std::vector<Bin*>& bins)
{
    std::string json = "{\n    \"bins\": [\n";
    for (int i = 0; i < bins.size(); ++i) {
        json += bins[i]->binToJSON();
        json += ",";
    }
    json.pop_back(); // Supprime la virgule superflue
    json += "    ]\n}";

    std::ofstream file("../../../out/bins.json", std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::ofstream file("../out/bins.json", std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
            return;
        }
    }
    file << json << std::endl;
    file.close();

    std::cout << "Le JSON a ete exporte avec succes." << std::endl;
}

void FileData::binPackingToJSON(const std::vector<Bin2*>& bins)
{
    std::string json = "{\n    \"bins\": [\n";
    for (int i = 0; i < bins.size(); ++i) {
        json += bins[i]->binToJSON();
        json += ",";
    }
    json.pop_back(); // Supprime la virgule superflue
    json += "    ]\n}";

    std::ofstream file("../../../out/bins.json", std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::ofstream file("../out/bins.json", std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
            return;
        }
    }
    file << json << std::endl;
    file.close();

    std::cout << "Le JSON a ete exporte avec succes." << std::endl;
}