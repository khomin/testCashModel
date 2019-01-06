#ifndef FINDER_H
#define FINDER_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include <blockitem.h>
#include <finderCash.h>

class Finder {
public:
    typedef struct {
        std::map<uint64_t, std::shared_ptr<BlockItem>> findResult;
        bool isAllNormal;
    }sFindResult;

    sFindResult getRangeFromCash(const std::pair<uint64_t,uint64_t> & range);
    sFindResult getRangeFromSwap(const std::pair<uint64_t,uint64_t> & range);
    std::vector<uint64_t>& getNotFoundItems();
    std::map<uint64_t, std::shared_ptr<BlockItem>> getFindResult();
    void mergeFinderResultWithCash(Finder::sFindResult & findResult);
private:
    finderCash cashFind;
    std::map<uint64_t, std::shared_ptr<BlockItem>> findResult;
    std::vector<uint64_t> notFoundItems;
};

#endif // FINDER_H
