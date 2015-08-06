#include "visualize.h"
#include "structure.h"
#include <cairomm/context.h>
#include <stdio.h>
#include <iostream>

//List * list = new List();
Structure * s = NULL;

Visualize::Visualize() {
}

Visualize::~Visualize() {
}

void Visualize::run() {

	/*
	s = new Tree();
	Tree * t = dynamic_cast <Tree *> (s);
	TreeNode * node = new TreeNode(t, 0);
	t->root = node;
	update("added root");
	TreeNode * node1 = new TreeNode(t, 0);
	node->right = node1;
	update("added node");
	TreeNode * node2 = new TreeNode(t, 0);
	node1->right = node2;
	update("added node");
	TreeNode * node3 = new TreeNode(t, 0);
	node->left = node3;
	update("added node");
	TreeNode * node4 = new TreeNode(t, 0);
	node2->left = node4;
	update("added node");
	TreeNode * node5 = new TreeNode(t, 0);
	node4->left = node5;
	update("added node");
	TreeNode * node6 = new TreeNode(t, 0);
	node4->right = node6;
	update("added node");

	TreeNode * node7 = new TreeNode(t, 1);
	update("added disconn");
	*/

	s = new Heap(32);
	Heap * h = dynamic_cast <Heap *> (s);
	update();
	h->array[h->n++] = 5;
	update();
	h->array[h->n++] = 7;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();
	h->array[h->n++] = 12;
	update();


	/*
	s = new Array();
	Array * a = dynamic_cast <Array *> (s);
	update();
	a->array[a->n++] = 5;
	update();
	a->array[a->n++] = 7;
	update();
	a->array[a->n++] = 12;
	update();
	*/

	/*
	s = new List();
	List * list = dynamic_cast <List *> (s);
	ListNode * node = new ListNode(list, 0);
	ListNode * node1 = new ListNode(list, 1);
	ListNode * node2 = new ListNode(list, 2);
	ListNode * node3 = new ListNode(list, 3);
	ListNode * node4 = new ListNode(list, 4);

	list->head = node;
	node->next = node1;
	node1->next = node2;
	node2->next = node3;

	update();

	delete node4;

	update("delet node4");

	ListNode * node5 = new ListNode(list, 5);
	list->startTrackLabel(node5);

	update("add node5");

	node5->next = node2;

	update("connect to next node");

	node1->next = node5;
	list->startTrackLabel(node1);

	update("connect from previous");

	node->next = node5;

	update("remove node1");

	node1->next = NULL;

	update("set next to null");

	delete node1;

	update("remove node1");
	*/

	/*
	s = new DList();
	DList * list = dynamic_cast <DList *> (s);
	DListNode * node = new DListNode(list, 0);

	list->head = node;
	update();
	list->tail = node;

	update();	
	
	DListNode * node1 = new DListNode(list, 1);
	DListNode * node2 = new DListNode(list, 2);
	DListNode * node3 = new DListNode(list, 3);


	node->next = node1;
	node1->prev = node;
	list->tail = node1;

	update();

	node1->next = node2;
	node2->prev = node1;
	list->tail = node2;

	update();

	node2->next = node3;
	node3->prev = node2;
	list->tail = node3;

	update();

	node1->next = node3;
	node3->prev = node1;

	update();
	*/

	/*
	delete node4;

	update();

	DListNode * node5 = new DListNode(list, 5);

	update();

	node5->next = node2;

	update();

	node1->next = node5;

	update();

	node->next = node5;

	update();

	node1->next = NULL;

	update();

	delete node1;

	update();
	*/
}

void Visualize::update() {
	update("blocking");
}

void Visualize::update(const char * msg) {
	this->queue_draw();
	std::cout << msg << std::endl;
	getchar();
}

bool Visualize::on_draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	if (s != NULL) {
		s->draw(cr);
	}
}
