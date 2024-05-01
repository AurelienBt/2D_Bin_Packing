#include <sstream>

#include "Bin.h"

Bin::Bin() : emptySpace(0)
{
}

Bin::~Bin() 
{
}

int Bin::getEmptySpace() const
{
	//int emptySpace = ;
	return 0;
}

void Bin::addRectangle(Rect rect)
{
	//TODO ajouter v�rif
	this->rectInBinList.push_back(rect);
	//TODO ajouter l'appel d'update empty space 
}

void Bin::removeRectangle(Rect rect)
{
	//TODO
	//TODO ajouter l'appel d'update empty space 
	return;
}

std::vector<Rect> Bin::getRectInBinList() const
{
	return this->rectInBinList;
}

void Bin::updateEmptySpace(Rect addedRect, bool add)
{
	//TODO
	return;
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

