#include "commandExecuter.h"

void CommandExecuter::handler(std::queue<CommandQueueItem>* commandQueue,
                              std::mutex* lock) {
    Finder finder;

    while(1) {

        if(lock->try_lock()) {
            if(!commandQueue->empty()) {
                // получаем указатель на поток вывода логов
                auto outStreamRes = commandQueue->front().getOutStreamToResult();

                // читаем из кэша
                auto res = finder.getRangeFromCash(commandQueue->front().getFindRange());
                auto notFoundCash = finder.getLastNotFoundIntervalsCash();

                // если сразу все нашли, ок
                if(notFoundCash.empty()) {
                    printfResultImediately(outStreamRes, res);
                } else {

                    // иначе читаем из swap
                    res = finder.getRangeFromSwap(notFoundCash);

                    // обновляем кэш
                    finder.updateCash(res);

                    // выводим
                    printfResultAfterSwap(outStreamRes, res);
                }
                commandQueue->pop();
            }
            lock->unlock();
        }

        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

void CommandExecuter::printfResultImediately(std::ostream* outStreamRes,
                                             const FinderData::findResult & finderResult) {
    if(outStreamRes != nullptr) {
        (*outStreamRes) << "handler: " << "all found" << std::endl;
        if(!finderResult.empty()) {
            (*outStreamRes) << "find totalElements=" << finderResult.size() << "\n";
            (*outStreamRes) << "noFound pointers: total="
                            << finderResult.begin()->second.get()->timeInterval.first << ", "
                            << "end="
                            << finderResult.rbegin()->second.get()->timeInterval.second << "]"<< "\n";
        }
    }
}

void CommandExecuter::printfResultAfterSwap(std::ostream* outStreamRes,
                                            const FinderData::findResult & finderResult) {
    if(outStreamRes != nullptr) {
        (*outStreamRes) << "Pending :" << std::endl;
        (*outStreamRes) << "handler: " << "found with swap" << std::endl;
        if(!finderResult.empty()) {
            (*outStreamRes) << "find total blocks=" << finderResult.size() << "\n";
            (*outStreamRes) << "pointers: "
                            << finderResult.begin()->second.get()->timeInterval.first << ", "
                            << "end="
                            << finderResult.rbegin()->second.get()->timeInterval.second << "]"<< "\n";
        }
    }
}
