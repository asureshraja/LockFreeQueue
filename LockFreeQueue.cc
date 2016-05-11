#include "LockFreeQueue.h"

LockFreeQueue::LockFreeQueue()
{
        this->queuesize=1000;
        this->direction=1;
        this->head=new std::atomic<int>(0);
        this->tail=new std::atomic<int>(-1);
    //ctor
}
Data* LockFreeQueue::dequeue(Data datatoadd)
{
  int old_head_val=0;
    int new_head_val=0;
    Data ret_val;
    do{
        //recursive force swap
        old_head_val=head->load(std::memory_order_relaxed);
        new_head_val=old_head_val+1;
        ret_val=buffer[old_head_val];
        // printf("%d %d\n",old_head_val,tail );
        if (new_head_val-1>=this->queuesize) {
            new_head_val=0;
            direction=1;
        }
        if (direction==1) {
            if (old_head_val>=tail->load(std::memory_order_relaxed)) {
                return nullptr;
            }
        }

    }while (!head->compare_exchange_weak(old_head_val, new_head_val));

    return &ret_val;
}
bool LockFreeQueue::enqueue(Data datatoadd){
 int old_tail_val=0;
    int new_tail_val=0;
    do{
    //recursive force swap
        old_tail_val=tail->load(std::memory_order_relaxed);
        new_tail_val=old_tail_val+1;
        if (new_tail_val>=this->queuesize) {
            new_tail_val=0;
            direction=-1;
        }
        if (direction==1) {
            if (new_tail_val>=this->queuesize) {
                return false;
            }
        }else{
            if (new_tail_val>=head->load(std::memory_order_relaxed)) {
                return false;
            }
        }
    }while (!tail->compare_exchange_weak(old_tail_val, new_tail_val));

    buffer[new_tail_val]=datatoadd;
    return true;
}
LockFreeQueue::~LockFreeQueue()
{
    //dtor
}
