#include "blockitem.h"

BlockItem::BlockItem() {
    timeInterval.first = 0;
    timeInterval.second = 0;
    lastUsageTimestamp = 0;
}

int BlockItem::getItemsCount() {
    return chrArray.size();
}
