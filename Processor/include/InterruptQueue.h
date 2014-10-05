#pragma once

typedef unsigned int uint;

class InterruptQueue {
public:
	InterruptQueue();
	~InterruptQueue();

	static const int QUEUE_SIZE = 255;

	int elements();
	bool available();

	void push(uint);
	uint pop();

private:
	uint queue[QUEUE_SIZE];
	uint start, end;
};

