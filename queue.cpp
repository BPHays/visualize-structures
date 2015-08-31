#include "queue.h"

Queue::Queue() {
	first = 0;
}

Queue::Queue(int size) : Array(size) {
	first = 0;
}

Queue::~Queue() {
}

void Queue::enqueue(int x) {
	// check if resize needed
	if (n >= size) {
		n %= size;
	}
	array[n++] = x;
}

int Queue::dequeue() {
	return array[first++];
}

bool Queue::isEmpty() {
	return n == first;
}
