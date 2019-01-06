#include "finder.h"

Finder::sFindResult Finder::getRangeFromCash(const std::pair<uint64_t,uint64_t> & range) {
    sFindResult res;
    // первым делом
    // поиск в cash
    auto find = cash.findRange(range);
    uint64_t curItem = range.first;
    while(curItem != range.second) {
        auto i = find.find(curItem);
        if(i == find.end()) {
            notFoundItems.push_back(curItem);
        }
    }
    notFoundItems.empty() ? res.isAllNormal = true : res.isAllNormal = false;
    res.findResult = find;
    return res;
}

Finder::sFindResult Finder::getRangeFromSwap(const std::pair<uint64_t,uint64_t> & range) {
    sFindResult res;
    // в notFoundItems то, что хотели найти но не нашли в cash
    // значит надо искать в swap
    // если не пуст, тогда начинаем
    if(!notFoundItems.empty()) {
        // получаем map из swap
        auto tfind = swap.findRange(range);
        // склеиваем findResult с tfind
        // т.е смотрим в списке, notFoundItems (что не нашли в  cash)
        // потом ищем конкретный элемент в результате swap
        // если найден, добавить в основной результат и удалить из notFoundItems
        for(auto it=notFoundItems.begin(); it!=notFoundItems.end(); it++) {
            auto i = tfind.find(*it);
            if(i != tfind.end()) {
                findResult.insert(std::pair<uint64_t, BlockItem>((*i).first, (*i).second));
            }
        }
        // удаляем из списка notFoundItem, т.к. их нашли

        for(auto nofountIt=notFoundItems.begin(); nofountIt!=notFoundItems.end(); nofountIt++) {
            auto res = findResult.find(*nofountIt);
            if(res != findResult.end()) {
                notFoundItems.erase(nofountIt);
                nofountIt = notFoundItems.begin();
            }
        }
    }

    notFoundItems.empty() ? res.isAllNormal = true : res.isAllNormal = false;
    res.findResult = findResult;
    return res;
}

std::map<uint64_t, BlockItem> Finder::getFindResult() {
    return findResult;
}

std::vector<uint64_t>& Finder::getNotFoundItems() {
    return notFoundItems;
}
