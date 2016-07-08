#include <iostream>
#include <thread>
#include "LockFreeQueue.h"
thpool::LockFreeQueue<int> *lfq;
void add(){
	for (int i=0;i<20;i++){
		std::cout<<i<<std::endl;
		std::cout<<"adding "<<i<<std::endl;
		
		lfq->enqueue(i);
	}	
}
void rem(){
	for (int i=0;i<20;i++){
		int t=lfq->dequeue();
		std::cout<<"dequeueing "<<t<<std::endl;
	}	
}
int main(int argc, char** argv)
{
lfq = new thpool::LockFreeQueue<int> ;	
	std::thread first(add);
    std::thread second(rem);
	first.join();
	second.join();
//		add();
//		rem();
    return 0;
}
