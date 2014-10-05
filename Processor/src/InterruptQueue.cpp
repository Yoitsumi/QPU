#include "InterruptQueue.h"


InterruptQueue::InterruptQueue() : start(0), end(0)
{
}


InterruptQueue::~InterruptQueue()
{
}

int InterruptQueue::elements(){
	if (start == end){
		return 0;
	} else if (start < end) {
		return end - start;
	} else {
		return (QUEUE_SIZE - start) + end;
	}
}

bool InterruptQueue::available(){
	return elements() >  0;
}

uint InterruptQueue::pop(){
	if (elements() <= 0)
		return 0;
	uint ret = queue[start];
	start++;
	if (start >= QUEUE_SIZE)
		start -= QUEUE_SIZE;
	return ret;
}

void InterruptQueue::push(uint val){
	queue[end] = val;
	end++;
	if (end >= QUEUE_SIZE)
		end -= QUEUE_SIZE;
}