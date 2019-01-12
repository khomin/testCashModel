#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include <list>

class BlockItem {
public:
    BlockItem();
    BlockItem(const BlockItem& b);
    int getItemsCount();
    std::pair<uint64_t,uint64_t> timeInterval; //Time interval
    std::list<std::pair<uint64_t, float>> chrArray; // The set of archive values selected from the archive for a given interval
    uint64_t lastUsageTimestamp; // Last access to this data block
};

#endif // BLOCKITEM_H
