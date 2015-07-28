#include "visualize.h"
#include <cairomm/context.h>
#include <iostream>

#define ARROW_OFFSET 10

DList::DList() {
	tail = NULL;
}

DList::~DList() {
}

void DList::arrange_nodes() {
	DListNode n = head;
	int xTmp = list_x;
	int yTmp = list_y;
	while (n != NULL) {
		// check that if the node has neighbors that they point to n correctly
		if ((!n->next || !n->next->prev || n->next->prev == n) && (!n->prev || !n->prev->next || n->prev->next == n))
			xTmp += ListNode::padding;
			n->x = xTmp;
			n->y = yTmp;
			n = n->next;
		}
	}
}

void DList::draw_connected(const Cairo::RefPtr<Cairo::Context> & cr) {
	DListNode n = head;
	while (n != NULL) {
		// check that if the node has neighbors that they point to n correctly
		if ((!n->next || !n->next->prev || n->next->prev == n) && (!n->prev || !n->prev->next || n->prev->next == n))
			// print the body of the node
			n->draw(cr);
			n->printed = true;

			// add the previous arrow
			if (n->prev != NULL) {
				draw_arow(cr, n->x + ARROW_OFSET, n->y (5 * ListNode::field_h) / 2, n->prev->x + ARROW_OFSET, n->prev->y + ListNode::field_h)
			} else {
				draw_null_arrow(cr, n->x + ARROW_OFSET, n->y (5 * ListNode::field_h) / 2);
			}

			// add the next arrow
			if (n->next != NULL) {
				draw_arow(cr, n->x + ListNode::field_w - ARROW_OFSET, n->y (3 * ListNode::field_h) / 2, n->next->x + ListNode::field_w - ARROW_OFSET, n->next->y + ListNode::field_h)
			} else {
				draw_null_arrow(cr, n->x + ListNode::field_w - ARROW_OFSET, n->y (3 * ListNode::field_h) / 2);
			}
			n = n->next;
		}
	}
}

DListNode::DListNode(List * dlist, int data) : ListNode(dlist, data) {
	this->prev = NULL;
	this->numFields = 3;
}

DListNode::~DListNode() {
}
