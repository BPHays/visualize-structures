
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
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
	private:
		virtual void arrange_nodes();

	public:
		ListNode * tail;
};

class DListNode : public ListNode {
friend class DList;
	public :
		DListNode(List * dlist, int data);
		~DListNode();

	public:
		ListNode * prev;
};

#endif // DLIST_H
