#ifndef FinderData_H
#define FinderData_H

#include <map>
#include <memory>
#include "blockitem.h"

class FinderData
{
public:
    FinderData();

    typedef std::vector<std::pair<uint64_t,uint64_t>> NotFoundIntervals;
    typedef std::map<uint64_t, std::shared_ptr<BlockItem>> findResult;

};

#endif // FinderData_H
