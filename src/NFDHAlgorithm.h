#ifndef NFDHALGORITHM_H
#define NFDHALGORITHM_H

#include <vector>

#include "Rect.h"
#include "Bin.h"

class NFDHALGORITHM {
public:

	NFDHAlgorithm();
	~NFDHAlgorithm();

	void runAlgorithm(std::vector<Rect> RectList, std::vector<Bin> BinList);

private:

};

#endif