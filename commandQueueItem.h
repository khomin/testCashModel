#ifndef COMMANDQUEUEITEM_H
#define COMMANDQUEUEITEM_H

#include "iostream"
#include <queue>
#include <thread>
#include <mutex>

class CommandQueueItem {
public:
    CommandQueueItem();
    bool setCommand(std::string &command);
    void setOutResultStream(std::ostream* outStream);
    bool getIsValid();
    std::pair<uint64_t,uint64_t> getFindRange() const;
    std::ostream* getOutStreamToResult();
    void flush();
private:
    bool isValid;
    std::ostream* outStream;
    std::pair<uint64_t, uint64_t> findRange;
};


#endif // COMMANDQUEUEITEM_H
