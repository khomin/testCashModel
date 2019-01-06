#include "parceResourceCash.h"
#include <fstream>
#include <memory>

ParceResourceCash::ParceResourceCash(std::string path) {
    loadResource(path);
}

bool ParceResourceCash::loadResource(std::string path) {
    bool res = false;
    std::ifstream file;
    std::vector<std::pair<uint64_t,float>> dataToCreateBlocks;
    file.open(path);

    // если файл открыт
    if(file.is_open()) {
        while(!file.eof()) {
            std::string value;
            std::getline(file, value);

            // считаная страка не пуста
            if(!value.empty()) {
                // сперва агрегируются данные по записям
                // складывается в вектор dataToCreateBlocks
                // после выхода из цикла разбора файла
                // из него создаются блоки
                auto data = getRecordData(value);
                if(data.first != 0) {
                    dataToCreateBlocks.push_back(data);
                }
            }
        }
        file.close();
    }

    // строим блоки
    buildBlockList(dataToCreateBlocks);

    return res;
}

void ParceResourceCash::buildBlockList(std::vector<std::pair<uint64_t,float>> & dataToCreateBlocks) {
    if(!dataToCreateBlocks.empty()) {
        std::shared_ptr<BlockItem> block;
        block = std::make_shared<BlockItem>();

        for(auto buildProperty: dataToCreateBlocks) {
            // если блок пустой
            // выставляем firts
            if(block->getItemsCount() == 0) {
                block->timeInterval.first = buildProperty.first;
            }

            block->chrArray.push_back(std::pair<uint64_t,float>(buildProperty.first, buildProperty.second));

            // сдвигаем конец диапазона
            // из последних его данных
            block->timeInterval.second = block->chrArray.back().first;

            // если в блок больше не помещается элемент
            if(block->getItemsCount() > maximumElementInBlock) {
                // тогда заканчиваем его
                list.insert(std::pair<uint64_t, std::shared_ptr<BlockItem>>(block->timeInterval.first, block));
                // и создаем следующий
                block = std::make_shared<BlockItem>();
            }
        }
        // если не вставили последний (по > maximumElementInBlock)
        // тогда добавляем здесь
        if(block->getItemsCount() != 0) {
            list.insert(std::pair<uint64_t, std::shared_ptr<BlockItem>>(block->timeInterval.first, block));
        }
    }
}

std::pair<uint64_t,float> ParceResourceCash::getRecordData(std::string lineRecord) {
    std::pair<uint64_t,float> res(0, 0);
    uint64_t timestamp = 0;
    float fvalue = 0;
    if(std::sscanf(lineRecord.c_str(), "%li,%f", &timestamp, &fvalue) == 2) {
        res.first = timestamp;
        res.second = fvalue;
    }
    return res;
}

std::map<uint64_t,std::shared_ptr<BlockItem>> ParceResourceCash::getLists() {
    return list;
}
