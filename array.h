#ifndef ARRAY_H
#define ARRAY_H

#include <gtkmm/drawingarea.h>
#include "structure.h"

class Array : Gtk::Widget, public Structure {
	public:
		Array();
		Array(int size);
		~Array();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);

	public:
		int * array;
		int size;
		int n;
	private:
		bool horizontal;
		static const int field_w;
		static const int field_h;
		static const int init_size;
};

#endif // ARRAY_H
