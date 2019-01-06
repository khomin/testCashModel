#include "commandExecuter.h"

void CommandExecuter::handler(std::queue<CommandQueueItem>* commandQueue,
                              std::mutex* lock) {
    Finder finder;
    for(;;) {
        if(lock->try_lock()) {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            if(!commandQueue->empty()) {
                auto outStreamRes = commandQueue->front().getOutStreamToResult();
                auto find = finder.getRangeFromCash(commandQueue->front().getFindRange());
                if(find.isAllNormal) {
                    printfResult(outStreamRes, find);
                } else {
                    auto rangeResult = finder.getRangeFromSwap(commandQueue->front().getFindRange());
                    printfResult(outStreamRes, rangeResult);
                }
                commandQueue->pop();
            }
            lock->unlock();
        }
    }
}

void CommandExecuter::printfResult(std::ostream* outStreamRes, Finder::sFindResult & finderResult) {
    if(outStreamRes != nullptr) {
        (*outStreamRes) << "handler: " << (finderResult.isAllNormal ? "all found" : "found bit") << std::endl;
        if(!finderResult.findResult.empty()) {
            (*outStreamRes) << "find totalElements=" << finderResult.findResult.size() << "\n";
            (*outStreamRes) << "noFound pointers: total="
                            << finderResult.findResult.begin()->second.timeInterval.first << ", "
                            << "end="
                            << finderResult.findResult.begin()->second.timeInterval.second << "]"<< "\n";
        }
    }
}
