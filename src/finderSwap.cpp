#include "include/finderSwap.h"

FinderData::findResult FinderSwap::findRange(const FinderData::NotFoundIntervals & intervals) {
    // fill the cache from the file
    ParceResourceCash parceResourceCash;
    parceResourceCash.loadResource("/media/khomin/D/PROJECTs/Qt/cashQt/log.csv", intervals);
    return parceResourceCash.getLoadResult();
}
