#ifndef FILEDATA_H
#define FILEDATA_H

#include <vector>

#include "Rect.h"

class FileData {

public:

	FileData();
	~FileData();

	static int BIN_WIDTH;
	static int BIN_HEIGHT;
	static int NB_ITEMS;
	static std::vector<Rect> RECT_LIST;
	static void init();

	//TODO json

private:

};

#endif