#include "visualize.h"
#include "array.h"
#include <cairomm/context.h>
#include <iostream>

const int Array::field_w = 50;
const int Array::field_h = 20;
const int Array::init_size = 10;

Array::Array() {
	x = 50;
	y = 50;
	size = init_size;
	array = new int[size];
	n = 0;
	horizontal = true;
}

Array::Array(int size) {
	x = 50;
	y = 50;
	this->size = size;
	array = new int[size];
	n = 0;
	horizontal = true;
}

Array::~Array() {
}

void Array::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	// set up variables to increment while printing
	int x_pos = x;
	int y_pos = y;
	int * coord;
	int x_increment;
	int y_increment;
	if (horizontal) {
		x_increment = field_w;
		y_increment = 0;
	} else {
		x_increment = 0;
		y_increment = field_h;
	}

	// print array pointing to the array

	// make sure they did not insert too many items
	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	Glib::RefPtr<Pango::Layout> layout;
	int text_w, text_h;
	int i;
	char * str = new char[10];
	for (int i = 0; i < n && i < size; i++) {
		// print the elements
		//*coord += *increment
		sprintf(str, "%d", array[i]);

		// print the background of the element
		cr->set_source_rgb(1.0, 1.0, 1.0);
		cr->rectangle(x_pos, y_pos, field_w, field_h);
		cr->fill();

		// print the outside of the element
		cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->set_line_width(2.0);
		cr->rectangle(x_pos, y_pos, field_w, field_h);
		cr->stroke();

		// print the value of the element
		layout = create_pango_layout(str);
		layout->set_font_description(font);
		layout->get_pixel_size(text_w, text_h);
		cr->move_to(x_pos + (field_w - text_w) / 2, y + (field_h - text_h) / 2);
		layout->show_in_cairo_context(cr);

		// increment to the next element
		x_pos += x_increment;
		y_pos += y_increment;
	}

	for (i = n; i < size; i++) {
		// print blank elemetns
		//*coord += *increment

		// print the background of the element
		cr->set_source_rgb(0.5, 0.5, 0.5);
		cr->rectangle(x_pos, y_pos, field_w, field_h);
		cr->fill();

		// print the outside of the element
		cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->set_line_width(2.0);
		cr->rectangle(x_pos, y_pos, field_w, field_h);
		cr->stroke();
		
		// print the value of the element
		layout = create_pango_layout("");
		layout->set_font_description(font);
		layout->get_pixel_size(text_w, text_h);
		cr->move_to(x_pos + (field_w - text_w) / 2, y + (field_h - text_h) / 2);
		layout->show_in_cairo_context(cr);


		// increment to the next element
		x_pos += x_increment;
		y_pos += y_increment;
	}
}
