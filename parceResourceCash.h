#ifndef PARCERESOURCECASH_H
#define PARCERESOURCECASH_H

#include <iostream>
#include <map>
#include "blockitem.h"

class ParceResourceCash
{
public:
    explicit ParceResourceCash(std::string path);
    bool loadResource(std::string path);
    std::map<uint64_t,std::shared_ptr<BlockItem>> getLists();
private:
    const int maximumElementInBlock = 5;
    void buildBlockList(std::vector<std::pair<uint64_t,float>> & dataToCreateBlocks);
    std::pair<uint64_t,float> getRecordData(std::string lineRecord);
    std::map<uint64_t,std::shared_ptr<BlockItem>> list;
};

#endif // PARCERESOURCECASH_H
