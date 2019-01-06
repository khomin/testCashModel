#include "commandExecuter.h"

void CommandExecuter::handler(std::queue<CommandQueueItem>* commandQueue,
                              std::mutex* lock) {
    Finder finder;
    for(;;) {

        if(lock->try_lock()) {
            std::this_thread::sleep_for(std::chrono::microseconds(100));

            if(!commandQueue->empty()) {
                // получаем указатель на поток вывода логов
                auto outStreamRes = commandQueue->front().getOutStreamToResult();
                // читаем из кэша
                auto res = finder.getRangeFromCash(commandQueue->front().getFindRange());

                // если сразу все нашли, ок
                if(res.isAllNormal) {
                    printfResultImediately(outStreamRes, res);
                } else { // иначе читаем из swap
                    res = finder.getRangeFromSwap(commandQueue->front().getFindRange());
                    // объядиняем с cash
                    finder.mergeFinderResultWithCash(res);
                    // выводим
                    printfResultAfterSwap(outStreamRes, res);
                }
                commandQueue->pop();
            }
            lock->unlock();
        }
    }
}

void CommandExecuter::printfResultImediately(std::ostream* outStreamRes, const Finder::sFindResult & finderResult) {
    if(outStreamRes != nullptr) {
        (*outStreamRes) << "handler: " << (finderResult.isAllNormal ? "all found" : "found with swap") << std::endl;
        if(!finderResult.findResult.empty()) {
            (*outStreamRes) << "find totalElements=" << finderResult.findResult.size() << "\n";
            (*outStreamRes) << "noFound pointers: total="
                            << finderResult.findResult.begin()->second.get()->timeInterval.first << ", "
                            << "end="
                            << finderResult.findResult.rbegin()->second.get()->timeInterval.second << "]"<< "\n";
        }
    }
}

void CommandExecuter::printfResultAfterSwap(std::ostream* outStreamRes, const Finder::sFindResult & finderResult) {
    if(outStreamRes != nullptr) {
        (*outStreamRes) << "Pending :" << std::endl;
        (*outStreamRes) << "handler: " << (finderResult.isAllNormal ? "all found in cash" : "found with swap") << std::endl;
        if(!finderResult.findResult.empty()) {
            (*outStreamRes) << "find total blocks=" << finderResult.findResult.size() << "\n";
            (*outStreamRes) << "pointers: "
                            << finderResult.findResult.begin()->second.get()->timeInterval.first << ", "
                            << "end="
                            << finderResult.findResult.rbegin()->second.get()->timeInterval.second << "]"<< "\n";
        }
    }
}
