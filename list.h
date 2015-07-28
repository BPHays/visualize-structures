
#ifndef LIST_H
#define LIST_H

#include <gtkmm/drawingarea.h>
#include "structure.h"

class ListNode;

/*
 * A list which automatically tracks created nodes
 */
class List : Gtk::Widget, public Structure {
	friend class DList;
	public:
		List();
		~List();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		void newNode(ListNode * node);
		void removeFromArray(ListNode * node);
	private:
		virtual void draw_arrow(const Cairo::RefPtr<Cairo::Context> & cr, int start_x, int start_y, int end_x, int end_y);
		virtual void draw_null_arrow(const Cairo::RefPtr<Cairo::Context> & cr, int start_x, int start_y);

	public:
		ListNode * head;
	private:
		int list_x;
		int list_y;
		int out_x;
		int out_y;
		ListNode ** nodes;
		int currentNodes;
		static const int nodes_size;
};

class ListNode : public Gtk::Widget {
	friend class List;
	public:
		ListNode();
		ListNode(List * list);
		ListNode(List * list, int data);
		ListNode(List * list, int x, int y);
		~ListNode();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_text(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y);
		virtual void draw_node(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y);

	public:
		ListNode * next;
		int data;
	protected:
		int numFields;
	private:
		static const int field_w;
		static const int field_h;
		static const int padding;
		List * list;
		bool printed;
		int x;
		int y;
};

#endif
