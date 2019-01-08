#include "finderSwap.h"

FinderData::findResult FinderSwap::findRange(const FinderData::NotFoundIntervals & intervals) {
    // заполняем кэш из файла
    ParceResourceCash parceResourceCash;
    parceResourceCash.loadResource("/media/khomin/D/PROJECTs/Qt/cashQt/log.csv", intervals);
    return parceResourceCash.getLoadResult();
}
