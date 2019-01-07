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
    FinderData::sFindResult findRange (const std::pair<uint64_t,uint64_t> & searchRange);
    void insertCashValues(std::map<uint64_t, std::shared_ptr<BlockItem>> searchRange);

private:
    std::map<uint64_t, std::shared_ptr<BlockItem>> cash;
};

#endif // CASH_H
