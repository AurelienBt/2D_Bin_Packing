#ifndef RECT_H
#define RECT_H

#include <iostream>

#include "Bin.h"

class Rect {
public:

	Rect(int id, int height, int width);
	~Rect();

	int getId() const;
	int getHeight() const;
	int getWidth() const;
	int getArea() const;
	bool getRotation() const;
	void setRotation(bool rotation);

	int getBinId() const;
	void setBinId(int binId);

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

	friend std::ostream& operator<<(std::ostream& os, const Rect & r);
	bool operator==(const Rect& r) const;
	//bool operator<(const Rect& r) const;

	static bool compareRects(const Rect* rectG, const Rect* rectD);

	std::string rectToJSON() const;


private:

	int id;
	int height;
	int width;
	int area;
	bool rotation;
	int binId;

	int x;
	int y;

};

#endif