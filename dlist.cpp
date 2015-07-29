#include "visualize.h"
#include "dlist.h"
#include <cairomm/context.h>
#include <iostream>

#define ARROW_OFFSET 10

DList::DList() {
	tail = NULL;
}

DList::~DList() {
}

void DList::arrange_nodes() {
	DListNode * n = dynamic_cast <DListNode *> (head);
	int xTmp = list_x;
	int yTmp = list_y;
	while (n != NULL) {
		// check that if the node has neighbors that they point to n correctly
		if ((!n->next || !n->next->prev || n->next->prev == n) && (!n->prev || !n->prev->next || n->prev->next == n)) {
			xTmp += ListNode::padding;
			n->x = xTmp;
			n->y = yTmp;
			n = dynamic_cast <DListNode *> (n->next);
		}
	}
}

void DList::draw_connected(const Cairo::RefPtr<Cairo::Context> & cr) {
	DListNode * n = dynamic_cast <DListNode *> (head);
	while (n != NULL) {
		// check that if the node has neighbors that they point to n correctly
		if ((!n->next || !n->next->prev || n->next->prev == n) && (!n->prev || !n->prev->next || n->prev->next == n)) {
			// print the body of the node
			n->draw(cr);
			n->printed = true;

			draw_arrows(cr, n);
			/*
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
			*/
			n = dynamic_cast <DListNode *> (n->next);
		}
	}
}

void DList::draw_arrows(const Cairo::RefPtr<Cairo::Context> & cr, DListNode * node) {
	// add the previous arrow
	if (node->prev != NULL) {
		draw_arrow_helper(cr, node->x + ARROW_OFFSET, node->y + (5 * ListNode::field_h) / 2, node->prev->x + ARROW_OFFSET + ListNode::field_w, node->prev->y + (5 * ListNode::field_h) / 2);
	} else {
		draw_null_arrow(cr, node->x + ARROW_OFFSET, node->y + (5 * ListNode::field_h) / 2);
	}

	// add the next arrow
	if (node->next != NULL) {
		draw_arrow_helper(cr, node->x + ListNode::field_w - ARROW_OFFSET, node->y + (3 * ListNode::field_h) / 2, node->next->x - ARROW_OFFSET, node->next->y + (3 * ListNode::field_h) / 2);
	} else {
		draw_null_arrow(cr, node->x + ListNode::field_w - ARROW_OFFSET, node->y + (3 * ListNode::field_h) / 2);
	}
}

DListNode::DListNode(List * dlist, int data) : ListNode(dlist, data) {
	this->prev = NULL;
	this->numFields = 3;
}

DListNode::~DListNode() {
}
