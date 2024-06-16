#ifndef TOOLS_H
#define TOOLS_H

#include <vector>

#include "Rect.h"
#include "Bin2.h"

struct FreeRect {
    int x;
    int y;
    int width;
    int height;

    bool operator==(const FreeRect& other) const {
        return x == other.x && y == other.y && width == other.width && height == other.height;
    }

};

class Tools {
public:

    Tools();
    ~Tools();
    int canFit(const Rect& rect, const FreeRect& freeRect);
    std::vector<FreeRect> cutRectangle(const Rect& item, const FreeRect& freeRect);
    double calculateFitness(const std::vector<Bin2*>& binList);

private:

};

#endif