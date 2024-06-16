#include "Tools.h"
#include "FileData.h"
#include <vector>

using namespace std;

Tools::Tools() {
}

Tools::~Tools() {
}

int Tools::canFit(const Rect& rect, const FreeRect& freeRect) {
    int width = 0;
    int height = 0;
    if (rect.getRotation()) {
        width = rect.getHeight();
        height = rect.getWidth();
    }
    else {
        width = rect.getWidth();
        height = rect.getHeight();
    }
    if (width <= freeRect.width && height <= freeRect.height) {
        return 1;
    }
    if (height <= freeRect.width && width <= freeRect.height) {
        return 2;
    }
    return -1; // Ne peut pas être inséré
}

std::vector<FreeRect> Tools::cutRectangle(const Rect& item, const FreeRect& freeRect) {
    std::vector<FreeRect> newFreeRects;
    int width = 0;
    int height = 0;
    if (item.getRotation() == true) {
        width = item.getHeight();
        height = item.getWidth();
    }
    else {
        width = item.getWidth();
        height = item.getHeight();
    }

    if (freeRect.height - height > freeRect.width - width) {
        // coupe horizontale
        if (width < freeRect.width) {
            newFreeRects.push_back({ freeRect.x + width, freeRect.y, freeRect.width - width, height });
        }
        if (height < freeRect.height) {
            newFreeRects.push_back({ freeRect.x, freeRect.y + height, freeRect.width, freeRect.height - height });
        }
    }
    else {
        // coupe verticale
        if (width < freeRect.width) {
            newFreeRects.push_back({ freeRect.x + width, freeRect.y, freeRect.width - width, freeRect.height });
        }

        if (height < freeRect.height) {
            newFreeRects.push_back({ freeRect.x, freeRect.y + height, width, freeRect.height - height });
        }
    }
    return newFreeRects;
}

double Tools::calculateFitness(const std::vector<Bin2*>& binList) {
    int binsUsed = binList.size();

    if (binsUsed == 0) {
        return 0.0; // Aucune bin utilisée
    }

    const Bin2* lastBin = binList[binsUsed - 1];
    int lastBinArea = FileData::BIN_WIDTH * FileData::BIN_HEIGHT - lastBin->getEmptySpace();

    double fillPercentage = (double)lastBinArea / (FileData::BIN_WIDTH * FileData::BIN_HEIGHT);

    double fitness = binsUsed - 1 + fillPercentage;

    //std::cout << fitness << std::endl;
    return fitness;
}