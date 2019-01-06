#include "finderCash.h"

void finderCash::insertCashValues(std::map<uint64_t, std::shared_ptr<BlockItem>> range) {
    cashValues = range;
}

std::map<uint64_t, std::shared_ptr<BlockItem>> finderCash::findRange(const std::pair<uint64_t,uint64_t> & range) {
    return cashValues;
}
