#include "finderCash.h"

void finderCash::insertCashValues(std::map<uint64_t, BlockItem> values) {
    cashValues = values;
}

std::map<uint64_t, BlockItem> finderCash::findRange(const std::pair<uint64_t,uint64_t> & range) {
    return cashValues;
}
