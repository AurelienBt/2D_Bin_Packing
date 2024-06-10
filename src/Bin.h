#ifndef BIN_H
#define BIN_H

#include <vector>

#include "Rect.h"
class Rect;

class Bin {
public:

	Bin(int id);
	~Bin();

	int getId() const;
	int getEmptySpace() const;
	bool addRectangle(Rect* rect, int coordX, int coordY);
	bool removeRectangle(Rect rect);

	std::vector<Rect*> getRectInBinList() const;

	std::string binToJSON() const;



private:

	int id;
	int emptySpace;
	void updateEmptySpace(Rect addedRect, bool add);

	std::vector<Rect*> rectInBinList;

};

#endif