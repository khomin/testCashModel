#ifndef CASH_H
#define CASH_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include "blockitem.h"
#include <map>
#include "finderData.h"

class FinderCash{
public:
    FinderData::findResult findRange (const std::pair<uint64_t,uint64_t> & searchRange);
    FinderData::NotFoundIntervals getLastNotFoundIntervals();
    void insertCashValues(std::map<uint64_t, std::shared_ptr<BlockItem>> searchRange);

private:
    std::map<uint64_t, std::shared_ptr<BlockItem>> cash;
    FinderData::NotFoundIntervals notFoundIntervals;
};

#endif // CASH_H
