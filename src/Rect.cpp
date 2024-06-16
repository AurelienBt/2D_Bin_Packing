#include <iostream>
#include <sstream>

#include "Rect.h"

Rect::Rect(int id, int height, int width): id(id), height(height), width(width), area(height*width), rotation(false), x(-1), y(-1), binId(-1)
{
}

Rect::~Rect()
{
}

int Rect::getId() const
{
	return id;
}

int Rect::getHeight() const
{
	return height;
}

int Rect::getWidth() const
{
	return width;
}

int Rect::getArea() const
{
	return area;
}

bool Rect::getRotation() const
{
	return rotation;
}

void Rect::setRotation(bool rotation)
{
	this->rotation = rotation;
}

int Rect::getBinId() const
{
	return this->binId;
}

void Rect::setBinId(int binId)
{
	this->binId = binId;
}

int Rect::getX() const
{
	return this->x;
}

int Rect::getY() const
{
	return this->y;
}

void Rect::setX(int x)
{
	this->x = x;
}

void Rect::setY(int y)
{
	this->y = y;
}

std::ostream& operator<<(std::ostream& os, const Rect & r)
{
	os << "ID : " << r.getId() << ", Bin ID : " << r.getBinId() << "\n";
	os << "Height : " << r.getHeight() << ", Width : " << r.getWidth() << "\n";
	os << "X : " << r.getX() << ", Y : " << r.getY() << ", Rotation : " << r.getRotation();
	return os;
}

bool Rect::operator==(const Rect& r) const
{
	return this->getId() == r.getId();
}

// opérateur de comparaison utilisé pour trier les rectangles dans l'algorithme LGFi
//bool Rect::operator<(const Rect& r) const {
//	//return this->getArea() < r.getArea();
//	int height = this->getHeight();
//	int width = this->getWidth();
//	if (this->getRotation()) {
//		int tmp = height;
//		height = width;
//		width = tmp;
//	}
//	int otherHeight = r.getHeight();
//	int otherWidth = r.getWidth();
//	if (r.getRotation()) {
//		int tmp = otherHeight;
//		otherHeight = otherWidth;
//		otherWidth = tmp;
//	}
//	return height > otherHeight || (height == otherHeight && width > otherWidth);
//}

//bool Rect::operator<(const Rect& r) const {
//	int height = this->getHeight();
//	int width = this->getWidth();
//	if (this->getRotation()) {
//		std::swap(height, width);
//	}
//
//	int otherHeight = r.getHeight();
//	int otherWidth = r.getWidth();
//	if (r.getRotation()) {
//		std::swap(otherHeight, otherWidth);
//	}
//
//	// Tri par hauteur décroissante
//	if (height != otherHeight) {
//		return height < otherHeight;
//	}
//
//	// Si les hauteurs sont égales, tri par largeur décroissante
//	return width < otherWidth;
//}

bool Rect::compareRects(const Rect* rectG, const Rect* rectD) {
	return rectG->getArea() > rectD->getArea();
	//int lhsHeight = rectG->getHeight();
	//int lhsWidth = rectG->getWidth();
	//if (rectG->getRotation()) {
	//	std::swap(lhsHeight, lhsWidth);
	//}

	//int rhsHeight = rectD->getHeight();
	//int rhsWidth = rectD->getWidth();
	//if (rectD->getRotation()) {
	//	std::swap(rhsHeight, rhsWidth);
	//}

	//// Tri par hauteur décroissante
	//if (lhsHeight != rhsHeight) {
	//	return lhsHeight > rhsHeight;
	//}

	//// Si les hauteurs sont égales, tri par largeur décroissante
	//return lhsWidth > rhsWidth;
}

std::string Rect::rectToJSON() const
{
	std::stringstream jsonStream;
	jsonStream << "{" << std::endl;
	jsonStream << "    \"id\": " << this->getId() << "," << std::endl;
	jsonStream << "    \"width\": " << this->getWidth() << "," << std::endl;
	jsonStream << "    \"height\": " << this->getHeight() << "," << std::endl;
	jsonStream << "    \"rotation\": " << this->getRotation() << "," << std::endl;
	jsonStream << "    \"binId\": " << this->getBinId() << "," << std::endl;
	jsonStream << "    \"x\": " << this->getX() << "," << std::endl;
	jsonStream << "    \"y\": " << this->getY() << std::endl;
	jsonStream << "}" << std::endl;

	return jsonStream.str();
}
