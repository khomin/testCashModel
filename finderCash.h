#ifndef CASH_H
#define CASH_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include "blockitem.h"
#include <map>

class finderCash{
public:
    std::map<uint64_t, std::shared_ptr<BlockItem>> findRange(const std::pair<uint64_t,uint64_t> & range);
    void insertCashValues(std::map<uint64_t, std::shared_ptr<BlockItem>> range);

private:
    std::map<uint64_t, std::shared_ptr<BlockItem>> cashValues;
};

#endif // CASH_H
