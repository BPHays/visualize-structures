#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <gtkmm/drawingarea.h>
#include "list.h"
#include "dlist.h"
#include "array.h"
#include "tree.h"
#include "heap.h"

class Visualize : public Gtk::DrawingArea {
	public:
		Visualize();
		~Visualize();
		void run(const char * arg);

		// demo methods
		void demo(const char * arg);
		void demo_array();
		void demo_heap();
		void demo_list();
		void demo_dlist();
		void demo_tree();

	protected:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void update();
		virtual void update(const char * msg);
};

#endif
