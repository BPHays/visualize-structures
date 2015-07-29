
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

void List::newNode(ListNode * node) {
	nodes[currentNodes++] = node;
}

void List::removeFromArray(ListNode * node) {
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
	/*
	ListNode * n = head;
	int xTmp = list_x;
	int yTmp = list_y;
	while (n != NULL) {
		xTmp += ListNode::padding;
		n->x = xTmp;
		n->y = yTmp;
		n = n->next;
	}
	*/

	// mark the array as unprinted
	for (int i = 0; i < currentNodes; i++) {
		nodes[i]->printed = false;
	}

	// print the head of the list
	draw_labels(cr);
	/*
	cr->set_source_rgb(0.0, 0.0, 0.0);
	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	Glib::RefPtr<Pango::Layout> layout = create_pango_layout("head");
	layout->set_font_description(font);
	int text_w, text_h;
	layout->get_pixel_size(text_w, text_h);
	cr->move_to(list_x, list_y);
	layout->show_in_cairo_context(cr);
	if (head != NULL) {
		draw_arrow(cr, list_x + text_w + 10, list_y + text_h / 2, head->x - 10, head->y + ListNode::field_h);
	} else {
		draw_null_arrow(cr, list_x + text_w + 10, list_y + text_h / 2);
	}
	*/

	//  print the nodes in the list
	draw_connected(cr);
	/*
	n = head;
	while (n != NULL) {
		n->draw(cr);
		n->printed = true;
		if (n->next != NULL) {
			draw_arrow(cr, n->x + ListNode::field_w - 10, n->y + (3 * ListNode::field_h) / 2, n->next->x - 10, n->next->y + ListNode::field_h);
		} else  {
			draw_null_arrow(cr, n->x + ListNode::field_w - 10, n->y + (3 * ListNode::field_h) / 2);
		}
		n = n->next;
	}
	*/

	// print nodes disconnected from the list
	draw_disconnected(cr);
	/*
	xTmp = out_x;
	yTmp = out_y;
	for (int i = 0; i < currentNodes; i++) {
		if (!nodes[i]->printed) {
			nodes[i]->y = yTmp;
			nodes[i]->x = xTmp;
			nodes[i]->draw(cr);		
			if (nodes[i]->next != NULL) {
				draw_arrow(cr, nodes[i]->x + ListNode::field_w - 10, nodes[i]->y + (3 * ListNode::field_h) / 2, nodes[i]->next->x - 10, nodes[i]->next->y + ListNode::field_h);
			} else  {
				draw_null_arrow(cr, nodes[i]->x + ListNode::field_w - 10, nodes[i]->y + (3 * ListNode::field_h) / 2);
			}
			xTmp = 2 * ListNode::padding;
		}
	}
	*/
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

	//std::cout << "m=" << m << ", theta=" << theta << ", "

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
	cr->set_source_rgb(0.0, 0.0, 0.0);
	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	Glib::RefPtr<Pango::Layout> layout = create_pango_layout("head");
	layout->set_font_description(font);
	int text_w, text_h;
	layout->get_pixel_size(text_w, text_h);
	cr->move_to(list_x, list_y);
	layout->show_in_cairo_context(cr);
	if (head != NULL) {
		draw_arrow_helper(cr, list_x + text_w + 10, list_y + text_h / 2, head->x - 10, head->y + ListNode::field_h);
	} else {
		draw_null_arrow(cr, list_x + text_w + 10, list_y + text_h / 2, true);
	}
}

// draw nodes which are fully attached to the list
void List::draw_connected(const Cairo::RefPtr<Cairo::Context> & cr) {
		ListNode * n = head;
	while (n != NULL) {
		n->draw(cr);
		n->printed = true;
		draw_arrows(cr, n);
		/*
		if (n->next != NULL) {
			draw_arrow(cr, n->x + ListNode::field_w - 10, n->y + (3 * ListNode::field_h) / 2, n->next->x - 10, n->next->y + ListNode::field_h);
		} else  {
			draw_null_arrow(cr, n->x + ListNode::field_w - 10, n->y + (3 * ListNode::field_h) / 2);
		}
		*/
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
			/*
			if (nodes[i]->next != NULL) {
				draw_arrow(cr, nodes[i]->x + ListNode::field_w - 10, nodes[i]->y + (3 * ListNode::field_h) / 2, nodes[i]->next->x - 10, nodes[i]->next->y + ListNode::field_h);
			} else  {
				draw_null_arrow(cr, nodes[i]->x + ListNode::field_w - 10, nodes[i]->y + (3 * ListNode::field_h) / 2);
			}
			*/
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
	list->newNode(this);
	this->numFields = 2;
}

ListNode::~ListNode() {
	list->removeFromArray(this);
}

void ListNode::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	cr->set_source_rgb(1.0, 1.0, 1.0);
	draw_node(cr, x, y);
	cr->set_source_rgb(0.0, 0.0, 0.0);
	draw_text(cr, x, y);
}

void ListNode::draw_text(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y) {
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

void ListNode::draw_node(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y) {
	cr->rectangle(x, y, field_w, field_h * numFields);
	cr->fill();

	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->set_line_width(2.0);
	for (int i = 0; i < numFields; i++) {
		cr->rectangle(x, y + (i * field_h), field_w, field_h);
		cr->stroke();
	}
}
