#ifndef HEAP_H
#define HEAP_H

#include <gtkmm/drawingarea.h>
#include "array.h"

class Heap : public Array {
	public:
		Heap();
		Heap(int size);
		~Heap();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);	
		virtual void draw_node(int x_pos, int y_pos, Cairo::RefPtr<Cairo::Pattern> & bg, Cairo::RefPtr<Cairo::Pattern> & border);

	public:
	protected:
	Cairo::RefPtr<Cairo::Pattern> filled_other;
	Cairo::RefPtr<Cairo::Pattern> empty_other;
	static const int node_h;
	static const int node_w;
	static const int node_padding;
};

#endif // HEAP_H
