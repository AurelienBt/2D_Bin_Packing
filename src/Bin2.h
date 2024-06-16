#ifndef BIN2_H
#define BIN2_H

#include <vector>

#include "Rect.h"
class Rect;

class Bin2 {
public:

	Bin2(int id);
	~Bin2();

	int getId() const;
	int getEmptySpace() const;
	bool addRectangle(Rect* rect, int coordX, int coordY);
	bool removeRectangle(Rect* rect);
	std::vector<Rect*>& getRectInBinList();
	const std::vector<Rect*>& getRectInBinList() const;
	Bin2* clone() const;
	std::string binToJSON() const;



private:

	int id;
	int emptySpace;
	void updateEmptySpace(Rect addedRect, bool add);

	std::vector<Rect*> rectInBinList;

};

#endif