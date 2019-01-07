#include "finder.h"

FinderData::sFindResult Finder::getRangeFromCash(const std::pair<uint64_t,uint64_t> & range) {
    auto res = cash.findRange(range);
    return res;
}

FinderData::sFindResult Finder::getRangeFromSwap(const FinderData::NotFoundIntervals & intervals) {
    auto res = swap.findRange(intervals);
    return res;
}

std::map<uint64_t, std::shared_ptr<BlockItem>> Finder::getFindResult() {
    return findResult;
}
