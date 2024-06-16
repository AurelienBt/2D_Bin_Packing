#ifndef FILEDATA_H
#define FILEDATA_H

#include <vector>

#include "Rect.h"
#include "Bin.h"
#include "Bin2.h"

class FileData {

public:

	FileData();
	~FileData();

	static int BIN_WIDTH;
	static int BIN_HEIGHT;
	static int NB_ITEMS;
	static std::vector<Rect*> RECT_LIST;
	static void init(int choice);

	static void binPackingToJSON(const std::vector<Bin*>& bins);
	static void binPackingToJSON(const std::vector<Bin2*>& bins);

private:

};

#endif