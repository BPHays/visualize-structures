#include "heap.h"
#include <gtkmm/drawingarea.h>
#include <cairomm/pattern.h>
#include <cairomm/context.h>

const int Heap::node_h = 30;
const int Heap::node_w = 50;
const int Heap::node_padding = 10;

Heap::Heap() : Heap(init_size) {
}

Heap::Heap(int size) : Array(size) {
	filled_other = Cairo::SolidPattern::create_rgb(0.9, 0.9, 0.9);
	empty_other = Cairo::SolidPattern::create_rgb(0.4, 0.4, 0.4);
	empty_text = Cairo::SolidPattern::create_rgb(1.0, 1.0, 1.0);
}

Heap::~Heap() {
}

void Heap::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	this->cr = cr;
	int x_pos = x;
	int y_pos = y;
	int width;
	for (width = 1; width * 2 <= n; width *= 2);
	width *= (node_w + node_padding);

	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	int tree_x;
	int tree_y;
	int i;
	int iLevel = 0;
	int nextLevel = 1;
	int levelNum = 0;
	bool levelFlag = true;
	char * str = new char[10];
	// print the elements with values
	for (i = 0; i < n && i < size; i++) {
		sprintf(str, "%d", array[i]);

		// draw the fields in the array
		if (levelFlag) {
			draw_field(x_pos, y_pos, filled, border);
		} else {
			draw_field(x_pos, y_pos, filled_other, border);
		}
		draw_element(str, font, x_pos, y_pos, text);

		// draw the tree
		tree_x = x + width / (nextLevel * 2) + (iLevel * width) / nextLevel;
		tree_y = y + (node_h + node_padding) * (3 + levelNum);
		draw_node(tree_x, tree_y, filled, border);
		draw_element(str, font, tree_x, tree_y, text);

		// update the tree level
		iLevel++;
		if (iLevel == nextLevel) {
			iLevel = 0;
			levelNum++;
			nextLevel *= 2;
			levelFlag = !levelFlag;
		}

		// increment the array's positions
		x_pos += x_increment;
		y_pos += y_increment;
	}

	// print the empty elements
	for (; i < size; i++) {
		sprintf(str, "%d", array[i]);

		if (levelFlag) {
			draw_field(x_pos, y_pos, empty, border);
		} else {
			draw_field(x_pos, y_pos, empty_other, border);
		}

		draw_element(str, font, x_pos, y_pos, empty_text);
		iLevel++;
		if (iLevel == nextLevel) {
			iLevel = 0;
			nextLevel *= 2;
			levelFlag = !levelFlag;
		}

		x_pos += x_increment;
		y_pos += y_increment;
	}
}

void Heap::draw_node(int x_pos, int y_pos, Cairo::RefPtr<Cairo::Pattern> & bg, Cairo::RefPtr<Cairo::Pattern> & border) {
	cr->save();
	cr->translate(x_pos + node_w / 2, y_pos + node_h / 2);
	cr->scale(node_w / 2, node_h / 2);
	cr->arc(0, 0, 1, 0, 2 * M_PI);
	cr->set_source(bg);
	cr->fill();
	cr->restore();
	cr->save();

	cr->set_line_width(2.0);
	cr->translate(x_pos + node_w / 2, y_pos + node_h / 2);
	cr->scale(node_w / 2, node_h / 2);
	cr->arc(0, 0, 1, 0, 2 * M_PI);
	cr->restore();
	cr->set_source(border);
	cr->stroke();
}

inline int Heap::parent(int i) {
	return (i - 1) / 2;
}

inline int Heap::right(int i) {
	return i * 2 + 2;
}

inline int Heap::left(int i) {
	return i * 2 + 1;
}

void Heap::insert(int data) {
	// resize the array if full
	if (n == size) {
		size *= 2;
		array = (int *) realloc(array, size);
	}

	// insert the element into the heap
	array[n] = data;

	// make sure the heap is valid
	int i = n;
	int tmp;
	while (array[i] > array[parent(i)]) {
		tmp = array[i];
		array[i] = array[parent(i)];
		array[parent(i)] = tmp;
		i = parent(i);
	}

	// move n to the next slot in the array
	n++;
}

bool Heap::removeMax(int & data) {
	// check that the heap is not empty
	if (n == 0) return false;

	// store the first element and replace it with the last
	int tmp;
	data = array[0];
	tmp = array[0];
	array[0] = array[n - 1];
	array[n - 1] = tmp;
	n--;

	// make sure the heap is valid
	int i = 0;
	int l = left(i);
	int r = right(i);
	int maxChild;
	while (l < n) {
		// find the largest child
		if (r < n && array[r] > array[l]) {
			maxChild = r;
		} else {
			maxChild = l;
		}

		// if the largest child is larger than the current node swap
		if (array[i] < array[maxChild]) {
			tmp = array[i];
			array[i] = array[maxChild];
			array[maxChild] = tmp;
		} else {
			break;
		}

		// iterate to the next element in the heap
		i = maxChild;
		l = left(i);
		r = right(i);
	}

	return true;
}
