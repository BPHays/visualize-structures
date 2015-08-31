#include "visualize.h"
#include "structure.h"
#include <cairomm/context.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

//List * list = new List();
Structure * s = NULL;

Visualize::Visualize() {
}

Visualize::~Visualize() {
}

void Visualize::demo(const char * arg) {
	if (!arg) {
		demo_graph();
		std::cout << "Array" << std::endl;
		demo_array();
		std::cout << "Heap" << std::endl;
		demo_heap();	
		std::cout << "Linked List" << std::endl;
		demo_list();
		std::cout << "Double Linked List" << std::endl;
		demo_dlist();
		std::cout << "Tree" << std::endl;
		demo_tree();
	} else if (!strcmp(arg, "array")) {
		std::cout << "Array" << std::endl;
		demo_array();
	} else if (!strcmp(arg, "heap")) {
		std::cout << "Heap" << std::endl;
		demo_heap();	
	} else if (!strcmp(arg, "list")) {
		std::cout << "Linked List" << std::endl;
		demo_list();
	} else if (!strcmp(arg, "dlist")) {
		std::cout << "Double Linked List" << std::endl;
		demo_dlist();
	} else if (!strcmp(arg, "tree")) {
		std::cout << "Tree" << std::endl;
		demo_tree();
	} else {
		std::cout << "Array" << std::endl;
		demo_array();
		std::cout << "Heap" << std::endl;
		demo_heap();	
		std::cout << "Linked List" << std::endl;
		demo_list();
		std::cout << "Double Linked List" << std::endl;
		demo_dlist();
		std::cout << "Tree" << std::endl;
		demo_tree();
	}
}

void Visualize::demo_graph() {
	s = new Graph();

	Graph * g = dynamic_cast <Graph *> (s);
	Vertex * v1 = new Vertex(g, 50, 50);
	Vertex * v2 = new Vertex(g, 300, 50);
	Vertex * v3 = new Vertex(g, 300, 300);
	Vertex * v4 = new Vertex(g, 50, 300);
	Vertex * v5 = new Vertex(g, 175, 175);
	update();
	g->add_edge(0,1);
	g->add_edge(0,3);
	g->add_edge(3,4);
	g->add_edge(4,1);
	g->add_edge(4,2);
	update();
}

void Visualize::demo_array() {
	s = new Array();
	Array * a = dynamic_cast <Array *> (s);
	update();
	a->array[a->n++] = 5;
	update();
	a->array[a->n++] = 7;
	update();
	a->array[a->n++] = 12;
	update();
	s = NULL;
}

void Visualize::demo_heap() {
	s = new Heap(20);
	Heap * h = dynamic_cast <Heap *> (s);
	update();
	h->insert(1);
	update();
	h->insert(5);
	update();
	h->insert(9);
	update();
	h->insert(7);
	update();
	h->insert(3);
	update();
	h->insert(12);
	update();
	h->insert(13);
	update();
	h->insert(9);
	update();
	h->insert(8);
	update();
	h->insert(5);
	update();
	h->insert(2);
	update();
	h->insert(8);
	update();
	h->insert(4);
	update();
	h->insert(20);
	update();
	h->insert(11);
	update();
	h->insert(6);
	update();
	h->insert(9);
	update();
	h->insert(3);
	update();
	h->insert(2);
	update();
	h->insert(1);
	update();
	int n;
	while(h->removeMax(n)) {
		std::cout << n << std::endl;
		update();
	}
	s = NULL;
}

void Visualize::demo_list() {
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
	s = NULL;
}

void Visualize::demo_dlist() {
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

	s = NULL;
}

void Visualize::demo_tree() {
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

	s = NULL;
}

void Visualize::run(const char * arg) {
	demo(arg);
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
	set_size_request(s->sWidth, s->sHeight);
	if (s != NULL) {
		s->draw(cr);
	}
}
