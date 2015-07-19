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

	ListNode node(50, 50);

	node.draw(cr);
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
	cr->move_to(x, y);

	layout->show_in_cairo_context(cr);
}

void ListNode::draw_node(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y) {
	cr->translate(x, y);
	cr->rectangle(0, 0, 100, 100);
	cr->fill();
}

ListNode::ListNode(int x, int y) {
	this->x = x;
	this->y = y;
	this->next = NULL;
}

ListNode::~ListNode() {
}
