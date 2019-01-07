#include "finderCash.h"

void FinderCash::insertCashValues(
        std::map<uint64_t, std::shared_ptr<BlockItem>> searchRange) {
    cash = searchRange;
}

FinderData::sFindResult FinderCash::findRange(const std::pair<uint64_t,uint64_t> & searchRange) {
    FinderData::sFindResult result;
    uint64_t firstInterval = searchRange.first;
    uint64_t lastIterval = firstInterval;
    while(lastIterval <= searchRange.second) {
        if(!cash.empty()) {
            auto i = cash.find(firstInterval);
            if(i == cash.end()) {
                result.notFoundIntervals.push_back(
                            std::pair<uint64_t,uint64_t>(firstInterval, lastIterval));
            }
        } else { // иначе еще не кэшиваровали, т.е. ничего нет
            result.notFoundIntervals.push_back(
                        std::pair<uint64_t,uint64_t>(firstInterval, lastIterval));
        }
        lastIterval++;
    }
    result.findResult = cash;
    return result;
}
