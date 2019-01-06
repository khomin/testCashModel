#include "finder.h"
#include "parceResourceCash.h"

Finder::sFindResult Finder::getRangeFromCash(const std::pair<uint64_t,uint64_t> & range) {
    sFindResult res;
    // первым делом
    // поиск в cash
    auto find = cashFind.findRange(range);

    for(uint64_t curItem = range.first; curItem!=range.second; curItem++) {
        // если уже кэшировали
        if(!find.empty()) {
            auto i = find.find(curItem);
            if(i == find.end()) {
                notFoundItems.push_back(curItem);
            }
        } else { // иначе еще не кэшиваровали, т.е. ничего нет
            notFoundItems.push_back(curItem);
        }
    }
    notFoundItems.empty() ? res.isAllNormal = true : res.isAllNormal = false;
    res.findResult = find;
    return res;
}

Finder::sFindResult Finder::getRangeFromSwap(const std::pair<uint64_t,uint64_t> & range) {
    sFindResult res;
    // заполняем кэш из файла
    ParceResourceCash parceResourceCash("/media/khomin/D/PROJECTs/Qt/cashQt/log.csv");
    res.findResult = parceResourceCash.getLists();
    // возврат результат
    notFoundItems.empty() ? res.isAllNormal = true : res.isAllNormal = false;

    return res;
}

void Finder::mergeFinderResultWithCash(Finder::sFindResult & res) {
    // склеиваем
    cashFind.insertCashValues(res.findResult);

    // далее смотрим в списке, notFoundItems (что не нашли в  cash)
    // потом ищем конкретный элемент в результате swap
    // если найден, добавить в основной результат и удалить из notFoundItems
    for(auto it=notFoundItems.begin(); it!=notFoundItems.end(); it++) {
        auto i = res.findResult.find(*it);
        if(i != res.findResult.end()) {
            findResult.insert(std::pair<uint64_t, std::shared_ptr<BlockItem>>((*i).first, (*i).second));
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

std::map<uint64_t, std::shared_ptr<BlockItem>> Finder::getFindResult() {
    return findResult;
}

std::vector<uint64_t>& Finder::getNotFoundItems() {
    return notFoundItems;
}
