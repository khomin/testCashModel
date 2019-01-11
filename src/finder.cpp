#include "include/finder.h"
#include <algorithm>

FinderData::resultCashValues Finder::getRangeFromCash(const std::pair<uint64_t,uint64_t> & range) {
    FinderData::resultCashValues res;
    cash.clearLastNotFound();
    // сдесь берем целые блоки
    // надо забрать из них только нужные записи
    auto findCashResult = cash.findRange(range);

    std::for_each(findCashResult.begin(), findCashResult.end(), [&](const std::pair<uint64_t,std::shared_ptr<BlockItem>> block) {
        for(auto tvalue: block.second.get()->chrArray) {
            if(tvalue.first >= range.first && tvalue.first <= range.second) {
                res.insert(std::pair<uint64_t, float> (tvalue.first, tvalue.second));
            }
        }
    });
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

FinderData::resultCashValues Finder::mergeResultUpdateCash(const FinderData::resultCashValues & lastResult,
                                                           const FinderData::findResult & update) {
    auto result = lastResult;
    cash.insertCashValues(update);
    std::for_each(update.begin(), update.end(), [&](const std::pair<uint64_t,std::shared_ptr<BlockItem>> block) {
        for(auto tvalue: block.second.get()->chrArray) {
            result.insert(std::pair<uint64_t, float> (tvalue.first, tvalue.second));
        }
    });
    return result;
}
