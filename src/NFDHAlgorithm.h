#ifndef NFDHALGORITHM_H
#define NFDHALGORITHM_H

#include <vector>

#include "Rect.h"
#include "Bin2.h"
#include "Tools.h"
using namespace std;

class NFDHAlgorithm {
public:

	NFDHAlgorithm();
	~NFDHAlgorithm();
	pair<vector<Bin2*>, vector<vector<FreeRect>>>runAlgorithm();

private:

};

#endif