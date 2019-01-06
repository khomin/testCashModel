#include "commandParser.h"

CommandParser::CommandParser() {
    std::thread threadQueue(&CommandExecuter::handler,
                            &queue, &queueLock);
    threadQueue.detach();
}

void CommandParser::execute() {
    while(1) {
        std::getline(cin, command);

        if(commandItem.setCommand(command)) {
            cout << "command input: " << command<< std::endl;

            commandItem.setOutResultStream(&std::cout);

            queueLock.lock();
            queue.push(commandItem);
            queueLock.unlock();
        } else {
            cout << "ivalid input: " << command<< std::endl;
        }
        commandItem.flush();
    }
}
