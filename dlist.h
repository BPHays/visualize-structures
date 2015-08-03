
#ifndef DLIST_H
#define DLIST_H

#include <gtkmm/drawingarea.h>
#include "list.h"

class DListNode;

class DList : public List {
	friend class List;
	public:
		DList();
		~DList();
//		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
	private:
		virtual void arrange_nodes();
		virtual void draw_connections(DListNode * node);
		virtual void draw_connected();
		virtual void draw_disconnected();
		virtual void draw_labels();

	public:
		ListNode * tail;
	private:
		int tail_x;
		int tail_y;
};

class DListNode : public ListNode {
friend class DList;
	public :
		DListNode(List * dlist, int data);
		~DListNode();

	public:
		DListNode * next;
		DListNode * prev;
};

#endif // DLIST_H
