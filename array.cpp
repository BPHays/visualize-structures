#include "visualize.h"
#include "array.h"
#include <cairomm/context.h>
#include <iostream>

const int Array::field_w = 50;
const int Array::field_h = 20;
const int Array::init_size = 10;

Array::Array() : Array(init_size) {
}

Array::Array(int size) {
	x = 50;
	y = 50;
	this->size = size;
	array = new int[size];
	n = 0;
	horizontal = true;
	if (horizontal) {
		x_increment = field_w;
		y_increment = 0;
	} else {
		x_increment = 0;
		y_increment = field_h;
	}
	// set the colors that will be used to draw the array
	filled = Cairo::SolidPattern::create_rgb(1.0, 1.0, 1.0);
	empty = Cairo::SolidPattern::create_rgb(.5, .5, .5);
	border = Cairo::SolidPattern::create_rgb(0.0, 0.0, 0.0);
	text = Cairo::SolidPattern::create_rgb(0.0, 0.0, 0.0);
}

Array::~Array() {
}

void Array::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	this->cr = cr;
	int x_pos = x;
	int y_pos = y;

	// print array pointing to the array

	// make sure they did not insert too many items
	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	int text_w, text_h;
	int i;
	char * str = new char[10];
	for (int i = 0; i < n && i < size; i++) {
		// print the elements
		sprintf(str, "%d", array[i]);

		// draw the structure of the field
		draw_field(x_pos, y_pos, filled, border);
		// print the value of the element
		draw_element(str, font, x_pos, y_pos, text);

		// increment to the next element
		x_pos += x_increment;
		y_pos += y_increment;
	}

	for (i = n; i < size; i++) {
		// print blank elemetns

		// draw the structure of the field
		draw_field(x_pos, y_pos, empty, border);
		// print the value of the element
		draw_element("", font, x_pos, y_pos, text);

		// increment to the next element
		x_pos += x_increment;
		y_pos += y_increment;
	}
}

void Array::draw_field(int x_pos, int y_pos, Cairo::RefPtr<Cairo::Pattern> & bg, Cairo::RefPtr<Cairo::Pattern> & border) {
	// print the background of the element
	cr->set_source(bg);
	cr->rectangle(x_pos, y_pos, field_w, field_h);
	cr->fill();

	// print the outside of the element
	cr->set_source(border);
	cr->set_line_width(2.0);
	cr->rectangle(x_pos, y_pos, field_w, field_h);
	cr->stroke();
}

void Array::draw_element(const char * data, Pango::FontDescription & font, int x_pos, int y_pos, Cairo::RefPtr<Cairo::Pattern> & text_patt) {
	Glib::RefPtr<Pango::Layout> layout;
	int text_h, text_w;
	layout = create_pango_layout(data);
	layout->set_font_description(font);
	layout->get_pixel_size(text_w, text_h);
	cr->set_source(text_patt);
	cr->move_to(x_pos + (field_w - text_w) / 2, y_pos + (field_h - text_h) / 2);
	layout->show_in_cairo_context(cr);
}
