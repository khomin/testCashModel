#include "finderCash.h"

void FinderCash::insertCashValues(
        std::map<uint64_t, std::shared_ptr<BlockItem>> searchRange) {
    cash.insert(searchRange.begin(), searchRange.end());
}

FinderData::sFindResult FinderCash::findRange(const std::pair<uint64_t,uint64_t> & searchRange) {
    FinderData::sFindResult result;

    auto lowerInterval = cash.lower_bound(searchRange.first);
    auto endInterval = cash.upper_bound(searchRange.second);

    if(endInterval == cash.end()) {
        for(auto tend = cash.rbegin(); tend!=cash.rend(); tend++) {
            if((*tend).second.get()->timeInterval.second <= searchRange.second) {
                endInterval = (--tend.base());
                auto endTest = (*endInterval);
                break;
            }
        }
    }

    if((lowerInterval != cash.end()) && (endInterval != cash.end())) {
        if((*lowerInterval).second.get()->timeInterval.first > searchRange.first) {
            result.notFoundIntervals.push_back(
                        std::pair<uint64_t,uint64_t>(searchRange.first, (*lowerInterval).second.get()->timeInterval.first));
        }
        if((*endInterval).second.get()->timeInterval.first > searchRange.first) {
            result.notFoundIntervals.push_back(
                        std::pair<uint64_t,uint64_t>((*endInterval).second.get()->timeInterval.second, searchRange.second));
        }
    } else {
        result.notFoundIntervals.push_back(
                    std::pair<uint64_t,uint64_t>(searchRange.first, searchRange.second));
    }

    result.findResult = cash;
    return result;
}
