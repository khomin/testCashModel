#ifndef PARCERESOURCECASH_H
#define PARCERESOURCECASH_H

#include <iostream>
#include <map>
#include "blockitem.h"
#include "finderData.h"

class ParceResourceCash
{
public:
    ParceResourceCash();
    bool loadResource(const std::string path,
                      const FinderData::NotFoundIntervals & searchIntervals);
    std::map<uint64_t,std::shared_ptr<BlockItem>> getLoadResult();
private:
    const int maximumElementInBlock = 5;
    void buildBlockList(std::vector<std::pair<uint64_t,float>> & dataToCreateBlocks);
    std::pair<uint64_t,float> getRecordData(std::string lineRecord);
    std::map<uint64_t,std::shared_ptr<BlockItem>> list;
};

#endif // PARCERESOURCECASH_H
