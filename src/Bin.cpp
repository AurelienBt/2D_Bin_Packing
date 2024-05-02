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

bool Bin::addRectangle(Rect rect, int coordX, int coordY)
{
	// Vérifie si le rectangle rentre dans la bin
	if (coordX < 0 || coordY < 0 || coordX + rect.getWidth() > FileData::BIN_WIDTH || coordY + rect.getHeight() > FileData::BIN_HEIGHT) {
		return false;
	}

	// Vérification de l'aire 
	if (rect.getArea() > this->getEmptySpace()) return false;

	// Vérifie les chevauchements
	//TODO if rotation : inverser les coords
	for (const Rect r : this->getRectInBinList()) {
		if (coordX < r.getX() + r.getWidth() && coordX + rect.getWidth() > r.getX() &&
			coordY < r.getY() + r.getHeight() && coordY + rect.getHeight() > r.getY()) {
			return false;
		}
	}

	// Insertion
	this->getRectInBinList().push_back(rect);
	this->updateEmptySpace(rect, true);
	rect.setBinId(this->getId());
	rect.setX(coordX);
	rect.setY(coordY);
	return true;
}

bool Bin::removeRectangle(Rect rect)
{
	// Vérifie que le rectangle est bien dans la bin
	std::vector<Rect>::iterator it = std::find(this->getRectInBinList().begin(), this->getRectInBinList().end(), rect);
	if (it != this->getRectInBinList().end()) {
		this->getRectInBinList().erase(it);
		this->updateEmptySpace(rect, false);
		return true;
	}
	return false;
}

std::vector<Rect> Bin::getRectInBinList() const
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
	jsonStream << "    \"rectangles\": " << "[" << std::endl;
	std::vector<Rect> tmpRect = this->getRectInBinList();
	for (int i = 0; i < tmpRect.size(); i++)
	{
		jsonStream << tmpRect.at(i).rectToJSON();
		jsonStream << "," << std::endl;
	}
	jsonStream.seekp(-1, jsonStream.cur); // supprime la virgule superflue
	jsonStream << "    ]" << std::endl;
	jsonStream << "}" << std::endl;

	return jsonStream.str();
}

