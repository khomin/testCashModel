#ifndef COMMANDEXECUTER_H
#define COMMANDEXECUTER_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include <commandQueueItem.h>
#include <finder.h>

class CommandExecuter {
public:
    static void handler(std::queue<CommandQueueItem>* commandQueue,
                        std::mutex* lock);
    static void printfResult(std::ostream* outStreamRes, Finder::sFindResult & finderResult);
};

#endif // COMMANDEXECUTER_H
