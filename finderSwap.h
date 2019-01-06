#ifndef SWAP_H
#define SWAP_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include "blockitem.h"
#include <map>

class finderSwap{
public:
    std::map<uint64_t, BlockItem> findRange(const std::pair<uint64_t,uint64_t> & range);
};

#endif // SWAP_H
