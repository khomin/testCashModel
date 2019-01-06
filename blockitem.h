#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include <list>

class BlockItem {
public:
    BlockItem();
    int getItemsCount();
    std::pair<uint64_t,uint64_t> timeInterval; //Интервал времени
    std::list<std::pair<uint64_t, float>> chrArray; // Набор архивных значений, выбранных из архива за данный интервал.
    uint64_t lastUsageTimestamp; // Время последнего обращения к данному блоку данных (может и
};

#endif // BLOCKITEM_H
