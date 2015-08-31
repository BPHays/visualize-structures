#include "node.h"

Node::Node() {
	bg_color = Cairo::SolidPattern::create_rgb(1.0, 1.0, 1.0);
	outline_color = Cairo::SolidPattern::create_rgb(0.0, 0.0, 0.0);
	txt_color = Cairo::SolidPattern::create_rgb(0.0, 0.0, 0.0);
}
