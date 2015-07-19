#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <gtkmm/drawingarea.h>

class Visualize : public Gtk::DrawingArea {
	public:
		Visualize();
		~Visualize();
	
	protected:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> & cr);
};

class ListNode : public Gtk::Widget {
	public:
		ListNode(int x, int y);
		~ListNode();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_text(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y);
		virtual void draw_node(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y);

	private:
		int x;
		int y;
		ListNode * next;
};

#endif
