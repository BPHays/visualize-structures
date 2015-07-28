#include "visualize.h"
#include <cairomm/context.h>
#include <iostream>

DList::DList() {
	tail = NULL;
}

DList::~DList() {
}

DListNode::DListNode(List * dlist, int data) : ListNode(dlist, data) {
	this->prev = NULL;
	this->numFields = 3;
}

DListNode::~DListNode() {
}
