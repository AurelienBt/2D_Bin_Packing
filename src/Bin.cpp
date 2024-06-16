#include <sstream>

#include "Bin.h"
#include "FileData.h"

Bin::Bin(int id) : id(id), emptySpace(FileData::BIN_HEIGHT* FileData::BIN_WIDTH)
{
}

Bin::~Bin() 
{
}

int Bin::getId() const
{
	return this->id;
}

int Bin::getEmptySpace() const
{
	return this->emptySpace;
}

bool Bin::addRectangle(Rect* rect, int coordX, int coordY)
{
	// Inverse la longueur et la largeur si rotation
	int rectWidth = rect->getRotation() ? rect->getHeight() : rect->getWidth();
	int rectHeight = rect->getRotation() ? rect->getWidth() : rect->getHeight();

	// Vérifie si le rectangle rentre dans la bin
	if (coordX < 0 || coordY < 0 || coordX + rectWidth > FileData::BIN_WIDTH || coordY + rectHeight > FileData::BIN_HEIGHT) {
		return false;
	}

	// Vérification de l'aire 
	if (rect->getArea() > this->getEmptySpace()) return false;

	// Vérifie les chevauchements
	for (const Rect* r : this->getRectInBinList()) {
		int rWidth = r->getRotation() ? r->getHeight() : r->getWidth();
		int rHeight = r->getRotation() ? r->getWidth() : r->getHeight();
		if (coordX < r->getX() + rWidth && coordX + rectWidth > r->getX() &&
			coordY < r->getY() + rHeight && coordY + rectHeight > r->getY()) {
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

bool Bin::removeRectangle(Rect rect)
{
	// Vérifie que le rectangle est bien dans la bin
	std::vector<Rect*>::iterator it = std::find(this->getRectInBinList().begin(), this->getRectInBinList().end(), &rect);
	if (it != this->getRectInBinList().end()) {
		this->getRectInBinList().erase(it);
		this->updateEmptySpace(rect, false);
		return true;
	}
	return false;
}

std::vector<Rect*> Bin::getRectInBinList() const
{
	return this->rectInBinList;
}

void Bin::updateEmptySpace(Rect addedRect, bool add)
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

std::string Bin::binToJSON() const
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

