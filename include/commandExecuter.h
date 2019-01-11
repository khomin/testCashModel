#ifndef COMMANDEXECUTER_H
#define COMMANDEXECUTER_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include <include/commandQueueItem.h>
#include <include/finder.h>

class CommandExecuter {
public:
    static void handler(std::queue<CommandQueueItem>* commandQueue,
                        std::mutex* lock);
    static void printfResultImediately(std::ostream* outStreamRes,
                                       const FinderData::resultCashValues & finderResult);
    static void printfResultAfterSwap(std::ostream* outStreamRes,
                                      const FinderData::resultCashValues & finderResult);
};

#endif // COMMANDEXECUTER_H
