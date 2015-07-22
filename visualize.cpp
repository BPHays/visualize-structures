#include "visualize.h"
#include "structure.h"
#include <cairomm/context.h>
#include <stdio.h>
#include <iostream>

//List * list = new List();
Structure * s;

Visualize::Visualize() {
}

Visualize::~Visualize() {
}

void Visualize::run() {
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

	update();

	ListNode * node5 = new ListNode(list, 5);

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

}

void Visualize::update() {
	this->queue_draw();
	std::cout << "blocking" << std::endl;
	getchar();
}

bool Visualize::on_draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	s->draw(cr);
}
