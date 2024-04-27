#ifndef RECT_H
#define RECT_H

#include <iostream>

#include "Bin.h"
class Bin;

class Rect {
public:

	Rect(int id, int height, int width);
	~Rect();

	int getId() const;
	int getHeight() const;
	int getWidth() const;
	bool getRotation() const;
	void setRotation(bool rotation);

	int getBinId() const;
	void setBinId(int binId);

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

	friend std::ostream& operator<<(std::ostream& os, const Rect & r);


private:

	int id;
	int height;
	int width;
	bool rotation;
	int binId;

	int x;
	int y;

};

#endif