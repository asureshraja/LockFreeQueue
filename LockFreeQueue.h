#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H
#include<Data.h>
#include<atomic>
class LockFreeQueue
{
    public:
        LockFreeQueue();
        bool enqueue(Data datatoadd);
        Data* dequeue(Data datatoadd);
        virtual ~LockFreeQueue();
    protected:
    private:
        Data buffer[1000];
        int direction;
        int queuesize;
        std::atomic<int> *tail;
        std::atomic<int> *head;
};

#endif // LOCKFREEQUEUE_H
