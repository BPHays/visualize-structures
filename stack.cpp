#include "stack.h"

Stack::Stack() {
}

Stack::Stack(int size) : Array(size) {
}

Stack::~Stack() {}

void Stack::push(int x) {
	// check if resize needed
	if (n >= size) {
		size *= 2;
		array = (int *) realloc(array, size);
	}
	array[n++] = x;
}

int Stack::pop() {
	return array[--n];
}

int Stack::peek() {
	return array[n - 1];
}

bool Stack::isEmpty() {
	return !n;
}
