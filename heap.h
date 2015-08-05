#ifndef HEAP_H
#define HEAP_H

#include <gtkmm/drawingarea.h>
#include "structure.h"

class Array : Gtk::Widget, public Structure {
	public:
		Heap();
		Heap(int size);
		~Heap();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
	
	public:
	protected:
};

#endif // HEAP_H
