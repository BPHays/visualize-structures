#include "visualize.h"
#include <cairomm/context.h>

Visualize::Visualize() {
}

Visualize::~Visualize() {
}

bool Visualize::on_draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	List * list = new List();
	//ListNode node(list);
	ListNode node(list, 100, 50);
	ListNode node1(list, 200, 50);
	ListNode node2(list, 300, 100);
	ListNode node3(list, 400, 30);
	ListNode * node4 = new ListNode(list, 500, 200);

	list->head = &node;
	node.next = &node1;
	node1.next = &node2;
	node2.next = &node3;

	//list->draw(cr);

	delete node4;

	list->draw(cr);
}

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
	ListNode * n = head;
	int xTmp = list_x;
	int yTmp = list_y;
	while (n != NULL) {
		xTmp += ListNode::padding;
		n->x = xTmp;
		n->y = yTmp;
		n = n->next;
	}

	// mark the array as unprinted
	for (int i = 0; i < currentNodes; i++) {
		nodes[i]->printed = false;
	}

	// print the head of the list
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

	//  print the nodes in the list
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

	// print nodes disconnected from the list
	xTmp = out_x;
	yTmp = out_y;
	for (int i = 0; i < currentNodes; i++) {
		if (!nodes[i]->printed) {
			nodes[i]->y = yTmp;
			nodes[i]->x = xTmp;
			nodes[i]->draw(cr);
			xTmp = 2 * ListNode::padding;
		}
	}

}

void List::draw_arrow(const Cairo::RefPtr<Cairo::Context> & cr, int start_x, int start_y, int end_x, int end_y) {
	cr->set_line_width(2.0);
	cr->move_to(start_x, start_y);
	cr->line_to(end_x, end_y);
	cr->stroke();
}

void List::draw_null_arrow(const Cairo::RefPtr<Cairo::Context> & cr, int start_x, int start_y) {
	// draw the body of the arrow
	cr->set_line_width(2.0);
	cr->move_to(start_x, start_y);
	cr->line_to(start_x + 35, start_y);
	cr->line_to(start_x + 35, start_y + 10);
	cr->stroke();

	// draw the horizontal lines
	cr->move_to(start_x + 25, start_y + 10);
	cr->line_to(start_x + 45, start_y + 10);
	cr->stroke();

	cr->move_to(start_x + 30, start_y + 15);
	cr->line_to(start_x + 40, start_y + 15);
	cr->stroke();

	cr->move_to(start_x + 34, start_y + 20);
	cr->line_to(start_x + 36, start_y + 20);
	cr->stroke();
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

ListNode::ListNode(List * list, int x, int y) {
	this->x = x;
	this->y = y;
	this->next = NULL;
	this->printed = false;
	this->list = list;
	list->newNode(this);
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
	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	Glib::RefPtr<Pango::Layout> layout = create_pango_layout("test");
	layout->set_font_description(font);
	int text_w, text_h;
	layout->get_pixel_size(text_w, text_h);
	cr->move_to(x + (field_w - text_w) / 2, y + (field_h - text_h) / 2);
	layout->show_in_cairo_context(cr);
}

void ListNode::draw_node(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y) {
	cr->rectangle(x, y, field_w, field_h * 2);
	cr->fill();

	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->set_line_width(2.0);
	cr->rectangle(x, y, field_w, field_h);
	cr->stroke();
	cr->rectangle(x, y + field_h, field_w, field_h);
	cr->stroke();
}