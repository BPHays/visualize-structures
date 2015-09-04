#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/rectangle.h>
#include "list.h"
#include "dlist.h"
#include "array.h"
#include "tree.h"
#include "heap.h"
#include "graph.h"
#include "stack.h"
#include "queue.h"
#include "rbtree.h"

class Visualize : public Gtk::DrawingArea {
	public:
		Visualize();
		~Visualize();
		void run(const char * arg);

		// demo methods
		void demo(const char * arg);
		void demo_array();
		void demo_stack();
		void demo_heap();
		void demo_list();
		void demo_dlist();
		void demo_tree();
		void demo_rbtree();
		void demo_graph();

	protected:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void update();
		virtual void update(const char * msg);

	private:
		int width = 500;
		int height = 500;
};

#endif
