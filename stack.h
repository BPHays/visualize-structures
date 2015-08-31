#ifndef STACK_H
#define STACK_H

#include "array.h"

class Stack : public Array {
	// methods
	public:
		Stack();
		Stack(int size);
		~Stack();
		void push(int x);
		int pop();
		int peek();
		bool isEmpty();
};

#endif // ARRAY_H
