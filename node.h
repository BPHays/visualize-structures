#ifndef NODE_H
#define NODE_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

class Node : public Gtk::Widget {
	// methods
	public:
		Node();
		// draw the node
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr)=0;
		// draw the frame of the node
		virtual void draw_node()=0;
		// add values to the node
		virtual void draw_text()=0;

	// member variables
	public:
		// object used for drawing the node
		Cairo::RefPtr<Cairo::Context> cr;
		// if the node has been printed
		bool printed;
		// the position of the node
		int x;
		int y;
	protected:
		// the colors of the different parts of the node
		Cairo::RefPtr<Cairo::Pattern> bg_color;
		Cairo::RefPtr<Cairo::Pattern> outline_color;
		Cairo::RefPtr<Cairo::Pattern> txt_color;

};

#endif // NODE_H
