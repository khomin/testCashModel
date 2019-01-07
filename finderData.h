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

    typedef struct {
        std::map<uint64_t, std::shared_ptr<BlockItem>> findResult;
        NotFoundIntervals notFoundIntervals;
        bool isAllNormal;
    }sFindResult;
};

#endif // FinderData_H