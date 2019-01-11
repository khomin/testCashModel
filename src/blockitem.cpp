#include "include/blockitem.h"

BlockItem::BlockItem() {
    timeInterval.first = 0;
    timeInterval.second = 0;
    lastUsageTimestamp = 0;
}

BlockItem::BlockItem(const BlockItem & b) {
    this->timeInterval = b.timeInterval;
    this->chrArray = b.chrArray;
    this->lastUsageTimestamp = b.lastUsageTimestamp;
}

int BlockItem::getItemsCount() {
    return chrArray.size();
}
