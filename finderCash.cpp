#include "finderCash.h"

void FinderCash::insertCashValues(
        std::map<uint64_t, std::shared_ptr<BlockItem>> searchRange) {
    cash.insert(searchRange.begin(), searchRange.end());
}

FinderData::findResult FinderCash::findRange(const std::pair<uint64_t,uint64_t> & searchRange) {
    FinderData::findResult resMap;
    auto lowerInterval = cash.lower_bound(searchRange.first);
    auto endInterval = cash.upper_bound(searchRange.second);

    notFoundIntervals.clear();

    if(endInterval == cash.end()) {
        for(auto tend = cash.rbegin(); tend!=cash.rend(); tend++) {
            if((*tend).second.get()->timeInterval.second <= searchRange.second) {
                endInterval = (--tend.base());
                break;
            }
        }
    }

    if((lowerInterval != cash.end()) && (endInterval != cash.end())) {
        // заносим в notFoundIntervals сколько не нашли слева
        if((*lowerInterval).second.get()->timeInterval.first > searchRange.first) {
            notFoundIntervals.push_back(
                        std::pair<uint64_t,uint64_t>(searchRange.first, (*lowerInterval).second.get()->timeInterval.first));
        }
        // заносим в notFoundIntervals сколько не нашли справа
        if((*endInterval).second.get()->timeInterval.first > searchRange.first) {
            notFoundIntervals.push_back(
                        std::pair<uint64_t,uint64_t>((*endInterval).second.get()->timeInterval.second, searchRange.second));
        }
        // копируем найденное в возврат
        // если только один элемент найден, инсерт не может вставить с двумя одинаковыми итераторами
        // вставка по ключу
        if(lowerInterval == endInterval) {
            resMap[(*lowerInterval).first] = (*endInterval).second;
        } else {
            resMap.insert(lowerInterval, endInterval);
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
