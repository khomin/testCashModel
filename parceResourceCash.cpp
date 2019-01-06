#include "parceResourceCash.h"
#include <fstream>

ParceResourceCash::ParceResourceCash(std::string path) {
    loadResource(path);
}

bool ParceResourceCash::loadResource(std::string path) {
    bool res = false;
    std::string value;
    std::ifstream file;
    file.open(path);

    // если файл открыт
    if(file.is_open()) {
        while(!file.eof()) {
            std::getline(file, value);

            // считаная страка не пуста
            if(!value.empty()) {
                // разбираем ее и получаем блок
                auto block = getBlock(value);
                // TODO:
                // проверка валидности,
                if((block.timeInterval.first != 0) && (block.timeInterval.second != 0)) {
                    // TODO: избежать затирания chrArray
                    // TODO: пока только с одним значением для одного времени
                    auto lowRange = list.lower_bound(block.timeInterval.first);
                    auto upRange = list.upper_bound(block.timeInterval.first);
                    if(lowRange != list.end() && upRange != list.end()) {

                    } else {
                        list[block.timeInterval.first] = block;
                    }
                } else {
                    std::cout << "loadResource: invalid block!\n";
                }
            }
        }
        file.close();
    }
    return res;
}

BlockItem ParceResourceCash::getBlock(std::string lineBlock) {
    BlockItem block;
    uint64_t timestamp = 0;
    float fvalue = 0;
    if(std::sscanf(lineBlock.c_str(), "%li,%f", &timestamp, &fvalue) == 2) {
        block.lastUsageTimestamp = 0;
        block.timeInterval.first = timestamp;
        block.timeInterval.second = timestamp;
        block.chrArray.push_back(std::pair<uint64_t, float>(timestamp, fvalue));
    }
    return block;
}

std::map<uint64_t,BlockItem> ParceResourceCash::getList() {
    return list;
}
