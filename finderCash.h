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
    std::map<uint64_t, BlockItem> findRange(const std::pair<uint64_t,uint64_t> & range);
    void insertCashValues(std::map<uint64_t, BlockItem>);

private:
    std::map<uint64_t, BlockItem> cashValues;
};

#endif // CASH_H
