#ifndef SWAP_H
#define SWAP_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include <map>
#include "blockitem.h"
#include "parceResourceCash.h"
#include "finderData.h"

class FinderSwap{
public:

    FinderData::sFindResult findRange(const FinderData::NotFoundIntervals & intervals);
};

#endif // SWAP_H
