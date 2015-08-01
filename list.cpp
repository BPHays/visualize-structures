
#include "visualize.h"
#include <cairomm/context.h>
#include <iostream>


const int List::nodes_size = 100;

List::List() {
	list_x = 50;
	list_y = 50;
	out_x = list_x;
	out_y = list_y + 100;
	head = NULL;
	nodes = new ListNode*[nodes_size];
	currentNodes = 0;
}

List::~List() {
}

void List::startTrackNode(ListNode * node) {
	nodes[currentNodes++] = node;
}

void List::stopTrackNode(ListNode * node) {
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

void List::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	// update the positions of the list
	arrange_nodes();

	// mark the array as unprinted
	for (int i = 0; i < currentNodes; i++) {
		nodes[i]->printed = false;
	}

	// print the head of the list
	draw_labels(cr);

	//  print the nodes in the list
	draw_connected(cr);

	// print nodes disconnected from the list
	draw_disconnected(cr);
}

// place the nodes that are part of the list in a single 
// horizontal line
void List::arrange_nodes() {
	ListNode * n = head;
	int xTmp = list_x;
	int yTmp = list_y;
	while (n != NULL) {
		xTmp += ListNode::padding;
		n->x = xTmp;
		n->y = yTmp;
		n = n->next;
	}
}

// draw the arrows from a specific node
void List::draw_arrows(const Cairo::RefPtr<Cairo::Context> & cr, ListNode * node) {
	std::cout << "other test" << std::endl;
	if (node->next != NULL) {
		draw_arrow_helper(cr, node->x + ListNode::field_w - 10, node->y + (3 * ListNode::field_h) / 2, node->next->x - 10, node->next->y + ListNode::field_h);
	} else  {
		draw_null_arrow(cr, node->x + ListNode::field_w - 10, node->y + (3 * ListNode::field_h) / 2, true);
	}

}

void List::draw_arrow_helper(const Cairo::RefPtr<Cairo::Context> & cr, int start_x, int start_y, int end_x, int end_y) {

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

void List::draw_null_arrow(const Cairo::RefPtr<Cairo::Context> & cr, int start_x, int start_y, bool right) {
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
void List::draw_labels(const Cairo::RefPtr<Cairo::Context> & cr) {
	draw_label_helper(cr, head, "head", list_x, list_y, RIGHT);
}

void List::draw_label_helper(const Cairo::RefPtr<Cairo::Context> & cr, ListNode * label, const char * text, int x, int y, LabelArrowPos arrowPos) {
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
		draw_arrow_helper(cr, x + text_w + 10, y + text_h / 2, label->x - 10, label->y + ListNode::field_h);
		} else {
		draw_arrow_helper(cr, x - 10, y + text_h / 2, label->x + ListNode::field_w + 10, label->y + ListNode::field_h);
		}
	} else {
		if (arrowPos == RIGHT) {
			draw_null_arrow(cr, x + text_w + 10, y + text_h / 2, true);
		} else {
			draw_null_arrow(cr, x - 10, y + text_h / 2, false);
		}
	}
}

// draw nodes which are fully attached to the list
void List::draw_connected(const Cairo::RefPtr<Cairo::Context> & cr) {
		ListNode * n = head;
	while (n != NULL) {
		n->draw(cr);
		n->printed = true;
		draw_arrows(cr, n);
		n = n->next;
	}
}

// draw nodes which may point to the list but are no fully attached to it
void List::draw_disconnected(const Cairo::RefPtr<Cairo::Context> & cr) {
	int xTmp = out_x;
	int yTmp = out_y;
	for (int i = 0; i < currentNodes; i++) {
		if (!nodes[i]->printed) {
			nodes[i]->y = yTmp;
			nodes[i]->x = xTmp;
			nodes[i]->draw(cr);		
			draw_arrows(cr, nodes[i]);
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
	list->newNode(this);
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
