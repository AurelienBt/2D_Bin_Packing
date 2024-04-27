#include "Bin.h"

Bin::Bin() 
{
	this->emptySpace = 0;
}

Bin::~Bin() 
{

}

int Bin::getEmptySpace() const
{
	//TODO
	return 0;
}

void Bin::addRectangle(Rect rect)
{
	//TODO ajouter vérif
	this->rectInBinList.push_back(rect);
}

void Bin::removeRectangle(Rect rect)
{
	//TODO
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

