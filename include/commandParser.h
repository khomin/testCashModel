#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>
#include <include/commandQueueItem.h>
#include <include/commandExecuter.h>

using namespace std;

class CommandParser {
public:
    CommandParser();
    void execute();
private:
    string command;
    CommandQueueItem commandItem;
    std::mutex queueLock;
    std::queue<CommandQueueItem> queue;
};

#endif // COMMANDPARSER_H
