#include <iostream>

#include "Rect.h"

Rect::Rect(int id, int height, int width): id(id), height(height), width(width), rotation(false), x(-1), y(-1), binId(-1)
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
