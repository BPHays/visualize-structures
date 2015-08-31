#ifndef QUEUE_H
#define QUEUE_H

#include "array.h"

class Queue : public Array {
	// methods
	public:
		Queue();
		Queue(int size);
		~Queue();
		void enqueue(int x);
		int dequeue();
		bool isEmpty();
	
	// member variables
	public:
		int first;
};

#endif // QUEUE_H
