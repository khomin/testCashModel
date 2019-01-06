#include "commandQueueItem.h"

CommandQueueItem::CommandQueueItem () {
    this->isValid = false;
    this->outStream = nullptr;
}

bool CommandQueueItem::setCommand(std::string &command)  {
    isValid = true;
    return isValid;
}

void CommandQueueItem::setOutResultStream(std::ostream* outStream) {
    this->outStream = outStream;
}

bool CommandQueueItem::getIsValid() {
    return isValid;
}

std::pair<uint64_t,uint64_t> CommandQueueItem::getFindRange() const {
    return findRange;
}

std::ostream* CommandQueueItem::getOutStreamToResult() {
    return outStream;
}

void CommandQueueItem::flush() {
    isValid = false;
}
