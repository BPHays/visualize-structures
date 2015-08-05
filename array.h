#ifndef ARRAY_H
#define ARRAY_H

#include <gtkmm/drawingarea.h>
#include <cairomm/pattern.h>
#include "structure.h"

class Array : Gtk::Widget, public Structure {
	public:
		Array();
		Array(int size);
		~Array();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_field(int x_pos, int y_pos, Cairo::RefPtr<Cairo::Pattern> & bg, Cairo::RefPtr<Cairo::Pattern> & border);
		virtual void draw_element(const char * data, Pango::FontDescription & font, int x_pos, int y_pos, Cairo::RefPtr<Cairo::Pattern> & text_patt);

	public:
		int * array;
		int size;
		int n;
	protected:
		bool horizontal;
		int x_increment;
		int y_increment;
		Cairo::RefPtr<Cairo::Pattern> empty;
		Cairo::RefPtr<Cairo::Pattern> filled;
		Cairo::RefPtr<Cairo::Pattern> border;
		Cairo::RefPtr<Cairo::Pattern> text;
		static const int field_w;
		static const int field_h;
		static const int init_size;
};

#endif // ARRAY_H
