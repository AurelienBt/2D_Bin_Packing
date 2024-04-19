#ifndef RECT_H
#define RECT_H

#include <vector>

#include "Bin.h"

class Rect {
public:

	Rect();
	~Rect();

	int getHeight();
	int getWidth();
	bool getRotation();
	void setRotation();

	Bin getBin();
	void setBin(Bin bin);

	int getX();
	int getY();
	void setX(int x);
	void setY(int y);


private:

	int height;
	int width;
	bool rotation;
	Bin bin;

	int x;
	int y;

};

#endif