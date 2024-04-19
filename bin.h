#ifndef BIN_H
#define BIN_H

#include <vector>

class Bin {
public:

	Bin();
	~Bin();

	int getEmptySpace();
	void addRectangle(Rect rect);
	void removeRectangle(Rect rect);

	std::vector<Rect> getRectInBinList();



private:

	int emptySpace;
	void updateEmptySpace(Rect addedRect, bool add);

	std::vector<Rect> rectInBinList;

};

#endif