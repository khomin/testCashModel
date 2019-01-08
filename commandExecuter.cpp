#include "commandExecuter.h"
#include <algorithm>

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
                    auto resAdvanced = finder.getRangeFromSwap(notFoundCash);

                    res.insert(resAdvanced.begin(), resAdvanced.end());

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
            (*outStreamRes) << "pointers: total="
                            << finderResult.begin()->second.get()->timeInterval.first << ", "
                            << "end="
                            << finderResult.rbegin()->second.get()->timeInterval.second << "]"<< "\n";
            (*outStreamRes) << "values: " << "\n";
            std::for_each(finderResult.begin(), finderResult.end(), [&](const std::pair<uint64_t,std::shared_ptr<BlockItem>> block) {
                for(auto i: block.second.get()->chrArray) {
                    (*outStreamRes) << "data=" << i.first << " value=" << i.second << std::endl;
                }
            });
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
            std::for_each(finderResult.begin(), finderResult.end(), [&](const std::pair<uint64_t,std::shared_ptr<BlockItem>> block) {
                for(auto i: block.second.get()->chrArray) {
                    (*outStreamRes) << "data=" << i.first << " value=" << i.second << std::endl;
                }
            });
        }
    }
}
