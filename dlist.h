
#ifndef DLIST_H
#define DLIST_H

#include "list.h"

/*
	class DListNode;

	class DList : public List {
		public:
			DList();
			~DList();
			virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		private:

		public:
			ListNode * tail;
	};
	*/

	class DListNode : public ListNode {
		public :
			DListNode(List * dlist, int data);
			~DListNode();

		public:
			ListNode * prev;
	};

#endif // DLIST_H
