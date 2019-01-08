#include "finder.h"

FinderData::findResult Finder::getRangeFromCash(const std::pair<uint64_t,uint64_t> & range) {
    auto res = cash.findRange(range);
    return res;
}

FinderData::NotFoundIntervals Finder::getLastNotFoundIntervalsCash() {
    return cash.getLastNotFoundIntervals();
}

FinderData::findResult Finder::getRangeFromSwap(const FinderData::NotFoundIntervals & intervals) {
    auto res = swap.findRange(intervals);
    return res;
}

std::map<uint64_t, std::shared_ptr<BlockItem>> Finder::getFindResult() {
    return findResult;
}

void Finder::updateCash(FinderData::findResult & updateValues) {
    cash.insertCashValues(updateValues);
}
