#include "finderCash.h"

void FinderCash::insertCashValues(
        std::map<uint64_t, std::shared_ptr<BlockItem>> searchRange) {
    cash.insert(searchRange.begin(), searchRange.end());
}

void FinderCash::clearLastNotFound() {
    notFoundIntervals.clear();
}

FinderData::findResult FinderCash::findRange(const std::pair<uint64_t,uint64_t> & searchRange) {
    FinderData::findResult resMap;
    auto lowerInterval = cash.lower_bound(searchRange.first);
    auto endInterval = cash.upper_bound(searchRange.second);

    if((lowerInterval == cash.end())) {
        auto lowerOffset = cash.begin();
        if(lowerOffset != cash.end()) {
            for(auto i=cash.begin(); i!=cash.end(); i++) {
                if((*i).first <= searchRange.first) {
                    lowerInterval = i;
                } else {
                    break;
                }
            }
        }
    }

    if(lowerInterval != cash.begin()) {
        if((*lowerInterval).first > searchRange.first) {
            lowerInterval--;
        }
    }

    if((lowerInterval != cash.end())) {
        // заносим  сколько не нашли слева
        if((*lowerInterval).second.get()->timeInterval.first > searchRange.first) {
            notFoundIntervals.push_back(
                        std::pair<uint64_t,uint64_t>(searchRange.first, (*lowerInterval).second.get()->timeInterval.first));
        }

        if(endInterval != cash.end()) {
            // заносим сколько не нашли справа
            if((*endInterval).second.get()->timeInterval.second > searchRange.second) {
                notFoundIntervals.push_back(
                            std::pair<uint64_t,uint64_t>((*endInterval).second.get()->timeInterval.second, searchRange.second));
            }
        } else {
            auto lastItem = (++cash.rbegin()).base();
            if((*lastItem).second.get()->timeInterval.second < searchRange.second) {
                notFoundIntervals.push_back(
                            std::pair<uint64_t,uint64_t>((*lastItem).second.get()->timeInterval.second, searchRange.second));
            }
        }

        // вставка по ключу
        while(lowerInterval != endInterval) {
            resMap[(*lowerInterval).first] = (*lowerInterval).second;
            lowerInterval++;
        }
    } else {
        notFoundIntervals.push_back(
                    std::pair<uint64_t,uint64_t>(searchRange.first, searchRange.second));
    }

    return resMap;
}

FinderData::NotFoundIntervals FinderCash::getLastNotFoundIntervals() {
    return notFoundIntervals;
}
