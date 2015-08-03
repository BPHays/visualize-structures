#ifndef NODE_H
#define NODE_H

class Node : public Gtk::Widget {
	// methods
	public:
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
};

#endif // NODE_H
