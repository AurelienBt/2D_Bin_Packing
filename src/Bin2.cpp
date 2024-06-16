#include <sstream>
#include <algorithm>
#include <iostream>

#include "Bin2.h"
#include "FileData.h"
using namespace std;

Bin2::Bin2(int id) : id(id), emptySpace(FileData::BIN_HEIGHT* FileData::BIN_WIDTH)
{
}

Bin2::~Bin2()
{
}

int Bin2::getId() const
{
    return this->id;
}

Bin2* Bin2::clone() const {
    Bin2* newBin = new Bin2(this->id);
    newBin->emptySpace = this->emptySpace;
    for (Rect* rect : this->rectInBinList) {
        newBin->rectInBinList.push_back(rect);
    }
    return newBin;
}

int Bin2::getEmptySpace() const
{
    return this->emptySpace;
}

bool Bin2::addRectangle(Rect* rect, int coordX, int coordY)
{
    // Inverse la longueur et la largeur si rotation
    int rectWidth = rect->getRotation() ? rect->getHeight() : rect->getWidth();
    int rectHeight = rect->getRotation() ? rect->getWidth() : rect->getHeight();

    // Vérifie si le rectangle rentre dans la bin
    if (coordX < 0 || coordY < 0 || coordX + rectWidth > FileData::BIN_WIDTH || coordY + rectHeight > FileData::BIN_HEIGHT) {
        cout << coordX << " " << coordY << " " << rectWidth << " " << rectHeight << endl;
        cout << "Rectangle hors de la bin" << endl; // "Rectangle out of bin
        return false;
    }
    // Vérification de l'aire
    if (rect->getArea() > this->getEmptySpace()) {
        cout << "Rectangle trop grand pour la bin" << endl; // "Rectangle too big for the bin
        return false;

    }
    // Vérifie les chevauchements
    for (const Rect* r : this->getRectInBinList()) {
        int rWidth = r->getRotation() ? r->getHeight() : r->getWidth();
        int rHeight = r->getRotation() ? r->getWidth() : r->getHeight();

        if (coordX < r->getX() + rWidth && coordX + rectWidth > r->getX() &&
            coordY < r->getY() + rHeight && coordY + rectHeight > r->getY()) {
            cout << "Chevauchement de rectangles" << endl; // "Rectangles overlap
            return false;
        }
    }

    // Insertion
    this->rectInBinList.push_back(rect);
    this->updateEmptySpace(*rect, true);
    rect->setBinId(this->getId());
    rect->setX(coordX);
    rect->setY(coordY);
    return true;
}

bool Bin2::removeRectangle(Rect* rect)
{
    // Vérifie que le rectangle est bien dans la bin
    std::vector<Rect*>& rectList = this->getRectInBinList();  // Utilisation de la référence
    std::vector<Rect*>::iterator it = std::find(rectList.begin(), rectList.end(), rect);

    if (it != rectList.end()) {
        rectList.erase(it);
        this->updateEmptySpace(*rect, false);
        return true;
    }
    return false;
}

std::vector<Rect*>& Bin2::getRectInBinList()
{
    return this->rectInBinList;
}

const std::vector<Rect*>& Bin2::getRectInBinList() const
{
    return this->rectInBinList;
}

void Bin2::updateEmptySpace(Rect addedRect, bool add)
{
    if (add)
    {
        this->emptySpace -= addedRect.getArea();
    }
    else
    {
        this->emptySpace += addedRect.getArea();
    }

}

std::string Bin2::binToJSON() const
{
    std::stringstream jsonStream;
    jsonStream << "{" << std::endl;
    jsonStream << "    \"id\": " << this->getId() << "," << std::endl;
    jsonStream << "    \"width\": " << FileData::BIN_WIDTH << "," << std::endl;
    jsonStream << "    \"height\": " << FileData::BIN_HEIGHT << "," << std::endl;
    jsonStream << "    \"rectangles\": " << "[" << std::endl;
    if (this->rectInBinList.size() > 0) {
        for (int i = 0; i < this->rectInBinList.size(); i++)
        {
            jsonStream << this->rectInBinList.at(i)->rectToJSON();
            jsonStream << "," << std::endl;
        }
        jsonStream.seekp(-2, jsonStream.cur); // supprime la virgule superflue
    }
    jsonStream << "    ]" << std::endl;
    jsonStream << "}" << std::endl;

    return jsonStream.str();
}
