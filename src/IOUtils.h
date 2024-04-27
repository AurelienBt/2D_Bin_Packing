#ifndef IOUTILS_H
#define IOUTILS_H

#include <vector>

#include "Rect.h"

class IOUtils {
public:

	IOUtils();
	~IOUtils();

	void read(int& binWidth, int& binHeight, int& nbItems, std::vector<Rect>& rectList);

private :

};

#endif
