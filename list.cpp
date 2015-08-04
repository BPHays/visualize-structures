
#include "visualize.h"
#include <cairomm/context.h>
#include <iostream>

List::List() {
	x = 50;
	y = 50;
	out_x = x;
	out_y = y + 100;
	head = NULL;
//	nodes = new Node*[nodes_size];
	nodes = new std::set<Node *>;
	labels = new std::set<Node *>;
	currentNodes = 0;
}

List::~List() {
}

/*
void List::startTrackNode(Node * node) {
	nodes[currentNodes++] = node;
}

void List::stopTrackNode(Node * node) {
	for (int i = 0; i < currentNodes; i++) {
		if (nodes[i] == node) {
			for (int j = i; j < currentNodes - 1; j++) {
				nodes[j] = nodes[j + 1];
			}
			break;
		}
	}
	currentNodes--;
}

*/

void List::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	this->cr = cr;
	// update the positions of the list
	arrange_nodes();

	// mark the array as unprinted
	/*
	for (int i = 0; i < currentNodes; i++) {
		nodes[i]->printed = false;
	}
	*/
	std::set<Node *>::iterator it;
	for (it = nodes->begin(); it != nodes->end(); ++it) {
		(*it)->printed = false;
	}

	// print the head of the list
	draw_labels();

	//  print the nodes in the list
	draw_connected();

	// print nodes disconnected from the list
	draw_disconnected();
}

// place the nodes that are part of the list in a single 
// horizontal line
void List::arrange_nodes() {
	ListNode * n = head;
	int xTmp = x;
	int yTmp = y;
	while (n != NULL) {
		xTmp += ListNode::padding;
		n->x = xTmp;
		n->y = yTmp;
		n = n->next;
	}
}

// draw the arrows from a specific node
void List::draw_connections(Node * node) {
	ListNode * lNode = dynamic_cast <ListNode *> (node);
	if (lNode->next != NULL) {
		draw_connection_helper(lNode->x + ListNode::field_w - 10, lNode->y + (3 * ListNode::field_h) / 2, lNode->next->x - 10, lNode->next->y + ListNode::field_h, FORWARD);
	} else  {
		draw_null_arrow(lNode->x + ListNode::field_w - 10, node->y + (3 * ListNode::field_h) / 2, true);
	}

}

/*
void List::draw_connection_helper(int start_x, int start_y, int end_x, int end_y, Graph::ConnType type) {

	double m = (end_y - start_y) / (double ) (end_x - start_x);	
	double theta = atan(m);
	int hyp = 5;
	double angle;
	if (end_x > start_x) {
		angle = 5.0 * 3.14159 / 6.0;
	} else {
		angle = 3.14159 / 6.0;
	}
	cr->set_line_width(2.0);
	// arrow body
	cr->move_to(start_x, start_y);
	cr->line_to(end_x, end_y);
	// arrow head
	cr->line_to(end_x + hyp * cos(theta + angle), end_y + hyp * sin(theta + angle));
	cr->line_to(end_x + hyp * cos(theta - angle), end_y + hyp * sin(theta - angle));
	cr->line_to(end_x, end_y);

	cr->stroke();
}
*/

void List::draw_null_arrow(int start_x, int start_y, bool right) {
	int dir = right ? 1 : -1;
	// draw the body of the arrow
	cr->set_line_width(2.0);
	cr->move_to(start_x, start_y);
	cr->line_to(start_x + (35 * dir), start_y);
	cr->line_to(start_x + (35 * dir), start_y + 10);
	cr->stroke();

	// draw the horizontal lines
	cr->move_to(start_x + (25 * dir), start_y + 10);
	cr->line_to(start_x + (45 * dir), start_y + 10);
	cr->stroke();

	cr->move_to(start_x + (30 * dir), start_y + 15);
	cr->line_to(start_x + (40 * dir), start_y + 15);
	cr->stroke();

	cr->move_to(start_x + (34 * dir), start_y + 20);
	cr->line_to(start_x + (36 * dir), start_y + 20);
	cr->stroke();
}

// draw labels and connect them to the structure with arrows
void List::draw_labels() {
	draw_label_helper(head, "head", x, y, RIGHT);
	int xTmp = x;
	std::set<Node *>::iterator it;
	for (it = labels->begin(); it != labels->end(); ++it) {
		draw_label_helper(*it, "l", xTmp, y - 50, RIGHT);
		xTmp += 100;
	}
}

void List::draw_label_helper(Node * label, const char * text, int x, int y, LabelArrowPos arrowPos) {
	cr->set_source_rgb(0.0, 0.0, 0.0);
	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	Glib::RefPtr<Pango::Layout> layout = create_pango_layout(text);
	layout->set_font_description(font);
	int text_w, text_h;
	layout->get_pixel_size(text_w, text_h);
	cr->move_to(x, y);
	layout->show_in_cairo_context(cr);
	if (label != NULL) {
		if (arrowPos == RIGHT) {
		draw_connection_helper(x + text_w + 10, y + text_h / 2, label->x - 10, label->y + ListNode::field_h, FORWARD);
		} else {
		draw_connection_helper(x - 10, y + text_h / 2, label->x + ListNode::field_w + 10, label->y + ListNode::field_h, FORWARD);
		}
	} else {
		if (arrowPos == RIGHT) {
			draw_null_arrow(x + text_w + 10, y + text_h / 2, true);
		} else {
			draw_null_arrow(x - 10, y + text_h / 2, false);
		}
	}
}

// draw nodes which are fully attached to the list
void List::draw_connected() {
		ListNode * n = head;
	while (n != NULL) {
		n->draw(cr);
		n->printed = true;
		draw_connections(n);
		n = n->next;
	}
}

// draw nodes which may point to the list but are no fully attached to it
void List::draw_disconnected() {
	int xTmp = out_x;
	int yTmp = out_y;
	/*
	for (int i = 0; i < currentNodes; i++) {
		if (!nodes[i]->printed) {
			nodes[i]->y = yTmp;
			nodes[i]->x = xTmp;
			nodes[i]->draw(cr);
			draw_connections(dynamic_cast <ListNode *> (nodes[i]));
			xTmp += 2 * ListNode::padding;
		}
	}
	*/
	std::set<Node *>::iterator it;
	for (it = nodes->begin(); it != nodes->end(); ++it) {
		if (!(*it)->printed) {
			(*it)->y = yTmp;
			(*it)->x = xTmp;
			(*it)->draw(cr);
			//draw_connections(dynamic_cast <ListNode *> (*it));
			draw_connections(*it);
			xTmp += 2 * ListNode::padding;
		}
	}
}

const int ListNode::field_w = 50;
const int ListNode::field_h = 20;
const int ListNode::padding = 100;

ListNode::ListNode() {
}

ListNode::ListNode(List * list) {
	this->next = NULL;
	this->printed = false;
	this->list = list;
	list->startTrackNode(this);
}

ListNode::ListNode(List * list, int data) {
	this->data = data;
	this->next = NULL;
	this->printed = false;
	this->list = list;
	list->startTrackNode(this);
	this->numFields = 2;
}

ListNode::~ListNode() {
	list->stopTrackNode(this);
}

void ListNode::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	this->cr = cr;
	cr->set_source_rgb(1.0, 1.0, 1.0);
	draw_node();
	cr->set_source_rgb(0.0, 0.0, 0.0);
	draw_text();
}

void ListNode::draw_text() {
	char * str = new char[10];
	sprintf(str, "%d", data);

	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	Glib::RefPtr<Pango::Layout> layout = create_pango_layout(str);
	layout->set_font_description(font);
	int text_w, text_h;
	layout->get_pixel_size(text_w, text_h);
	cr->move_to(x + (field_w - text_w) / 2, y + (field_h - text_h) / 2);
	layout->show_in_cairo_context(cr);
}

void ListNode::draw_node() {
	cr->rectangle(x, y, field_w, field_h * numFields);
	cr->fill();

	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->set_line_width(2.0);
	for (int i = 0; i < numFields; i++) {
		cr->rectangle(x, y + (i * field_h), field_w, field_h);
		cr->stroke();
	}
}
