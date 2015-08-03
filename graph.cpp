
#include "graph.h"

//Graph::Graph(){
//}

//Graph::~Graph(){
//}

void Graph::startTrackNode(Node * node) {
	//nodes[currentNodes++] = node;
	nodes->insert(node);
}

void Graph::stopTrackNode(Node * node) {
	/*
	for (int i = 0; i < currentNodes; i++) {
		if (nodes[i] == node) {
			for (int j = i; j < currentNodes - 1; j++) {
				nodes[j] = nodes[j + 1];
			}
			break;
		}
	}
	currentNodes--;
	*/
	nodes->erase(node);
}

void Graph::startTrackLabel(Node * label) {
	labels->insert(label);
}

void Graph::stopTrackLabel(Node * label) {
	labels->erase(label);
}

void Graph::draw_connection_helper(int start_x, int start_y, int end_x, int end_y, Graph::ConnType type) {

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
	switch (type) {
		case FORWARD:
			cr->line_to(end_x + hyp * cos(theta + angle), end_y + hyp * sin(theta + angle));
			cr->line_to(end_x + hyp * cos(theta - angle), end_y + hyp * sin(theta - angle));
			cr->line_to(end_x, end_y);
			break;
	}

	cr->stroke();
}

/*
void Graph::draw_label_helper(Node * label, const char * text, int x, int y, LabelArrowPos arrowPos) {
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
*/
