#ifndef BIN_H
#define BIN_H

#include <vector>

#include "Rect.h"
class Rect;

class Bin {
public:

	Bin();
	~Bin();

	int getEmptySpace() const;
	void addRectangle(Rect rect);
	void removeRectangle(Rect rect);

	std::vector<Rect> getRectInBinList() const;

	std::string binToJSON() const;



private:

	int emptySpace;
	void updateEmptySpace(Rect addedRect, bool add);

	std::vector<Rect> rectInBinList;

};

#endif