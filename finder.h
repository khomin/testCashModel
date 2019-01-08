#ifndef FINDER_H
#define FINDER_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include <blockitem.h>
#include <finderCash.h>
#include <finderSwap.h>
#include "finderData.h"

class Finder {
public:
    FinderData::findResult getRangeFromCash(const std::pair<uint64_t,uint64_t> & range);
    FinderData::NotFoundIntervals getLastNotFoundIntervalsCash();

    FinderData::findResult getRangeFromSwap(const FinderData::NotFoundIntervals & intervals);

    std::map<uint64_t, std::shared_ptr<BlockItem>> getFindResult();
    void updateCash(FinderData::findResult & updateValues);
private:
    FinderCash cash;
    FinderSwap swap;
    std::map<uint64_t, std::shared_ptr<BlockItem>> findResult;
};

#endif // FINDER_H
