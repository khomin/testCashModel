#include "include/commandExecuter.h"
#include <algorithm>

void CommandExecuter::handler(std::queue<CommandQueueItem>* commandQueue,
                              std::mutex* lock) {
    Finder finder;

    while(1) {

        if(lock->try_lock()) {
            if(!commandQueue->empty()) {
                // get pointer to log output stream
                auto outStreamRes = commandQueue->front().getOutStreamToResult();

                // read from the cache
                auto resultCash = finder.getRangeFromCash(commandQueue->front().getFindRange());
                auto notFoundCash = finder.getLastNotFoundIntervalsCash();

                // if everyone found it right away, ok
                if(notFoundCash.empty()) {
                    printfResultImediately(outStreamRes, resultCash);
                } else {

                    // otherwise read from swap
                    auto resAdvanced = finder.getRangeFromSwap(notFoundCash);

                    // cash update
                    resultCash = finder.mergeResultUpdateCash(resultCash, resAdvanced);

                    // output
                    printfResultAfterSwap(outStreamRes, resultCash);
                }
                commandQueue->pop();
            }
            lock->unlock();
        }

        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

void CommandExecuter::printfResultImediately(std::ostream* outStreamRes,
                                             const FinderData::resultCashValues & finderResult) {
    if(outStreamRes != nullptr) {
        (*outStreamRes) << "handler: " << "all found" << std::endl;
        if(!finderResult.empty()) {
            (*outStreamRes) << "find totalElements=" << finderResult.size() << "\n";
            (*outStreamRes) << "pointers: total="
                            << finderResult.begin()->first << ", "
                            << "end="
                            << finderResult.rbegin()->second << "]"<< "\n";
            (*outStreamRes) << "values: " << "\n";
            std::for_each(finderResult.begin(), finderResult.end(), [&](std::pair<const uint64_t, const float> value) {
                (*outStreamRes) << "date=" << value.first << " value=" << value.second << std::endl;
            });
        }
    }
}

void CommandExecuter::printfResultAfterSwap(std::ostream* outStreamRes,
                                            const FinderData::resultCashValues & finderResult) {
    if(outStreamRes != nullptr) {
        (*outStreamRes) << "Pending :" << std::endl;
        (*outStreamRes) << "handler: " << "found with swap" << std::endl;
        if(!finderResult.empty()) {
            (*outStreamRes) << "find total blocks=" << finderResult.size() << "\n";
            (*outStreamRes) << "pointers: "
                            << finderResult.begin()->second << ", "
                            << "end="
                            << finderResult.rbegin()->second << "]" << "\n";
            std::for_each(finderResult.begin(), finderResult.end(), [&](std::pair<const uint64_t, const float> value) {
                (*outStreamRes) << "date=" << value.first << " value=" << value.second << std::endl;
            });
        }
    }
}
