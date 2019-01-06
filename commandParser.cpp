#include "commandParser.h"

CommandParser::CommandParser() {
    std::thread threadQueue(&CommandExecuter::handler,
                            &queue, &queueLock);
    threadQueue.detach();
}

void CommandParser::execute() {
    while(cin >> command) {
        cout << "command input: " << command<< std::endl;

        if(commandItem.setCommand(command)) {
            commandItem.setOutResultStream(&std::cout);
            queueLock.lock();
            queue.push(commandItem);
            queueLock.unlock();
        }
        commandItem.flush();
    }
}
