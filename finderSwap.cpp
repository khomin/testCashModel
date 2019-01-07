#include "finderSwap.h"

FinderData::sFindResult FinderSwap::findRange(const FinderData::NotFoundIntervals & intervals) {
    FinderData::sFindResult res;
    // заполняем кэш из файла
    ParceResourceCash parceResourceCash;
    parceResourceCash.loadResource("/media/khomin/D/PROJECTs/Qt/cashQt/log.csv", intervals);
    res.findResult = parceResourceCash.getLoadResult();
    return res;
}
