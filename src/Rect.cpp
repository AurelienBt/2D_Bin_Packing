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

std::string Rect::rectToJSON() const
{
	std::stringstream jsonStream;
	jsonStream << "{" << std::endl;
	jsonStream << "    \"id\": " << this->getId() << "," << std::endl;
	jsonStream << "    \"width\": " << this->getWidth() << "," << std::endl;
	jsonStream << "    \"height\": " << this->getHeight() << std::endl;
	jsonStream << "    \"rotation\": " << this->getRotation() << std::endl;
	jsonStream << "    \"binId\": " << this->getBinId() << std::endl;
	jsonStream << "    \"x\": " << this->getX() << std::endl;
	jsonStream << "    \"y\": " << this->getY() << std::endl;
	jsonStream << "}" << std::endl;

	return jsonStream.str();
}
