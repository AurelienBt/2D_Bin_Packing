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

