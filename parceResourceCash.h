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
    std::map<uint64_t,BlockItem> getList();
private:
    BlockItem getBlock(std::string lineBlock);

    std::map<uint64_t,BlockItem> list;
};

#endif // PARCERESOURCECASH_H
