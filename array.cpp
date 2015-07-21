#include "visualize.h"
#include <cairomm/context.h>

const int Array::field_w = 50;
const int Array::field_h = 20;
const int init_size = 10;

Array::Array() {
	x = 50;
	y = 50;
	size = init_size;
	n = 0;
	horizontal = true;
}

Array::Array(int size) {
	x = 50;
	y = 50;
	this->size = size;
	n = 0;
	horizontal = true;
}

Array::~Array() {
}

void draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	// set up variables to increment while printing
	int * coord;
	int * increment;
	if (horizontal)
		coord = &x;
		increment = &field_w;
	} else {
		coord = &y;
		increment = &field_h;
	}

	// print array pointing to the array

	// make sure they did not insert too many items
	for (int i = 0; i < n && i < size; i++) {
		// print the elements
		//*coord += *increment
	}

	for (int i = n; i < size; i++) {
		// print blank elemetns
		//*coord += *increment
	}
}
