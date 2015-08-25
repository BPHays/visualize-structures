
#include "visualize.h"
#include <cairomm/context.h>
#include <iostream>

Graph::Graph(){
	x = 50;
	y = 50;
	nodes = new std::set<Node *>;
	labels = new std::set<Node *>;
	directed = false;
	aMatrix = new bool*[100];
	for (int i = 0; i < 100; i++) {
		aMatrix[i] = new bool[100]();
	}
	vertices = new Vertex*[100];
	currentNodes = 0;
}

//Graph::~Graph(){
//}

void Graph::startTrackNode(Node * node) {
	nodes->insert(node);
}

void Graph::stopTrackNode(Node * node) {
	nodes->erase(node);
}

void Graph::startTrackLabel(Node * label) {
	labels->insert(label);
}

void Graph::stopTrackLabel(Node * label) {
	labels->erase(label);
}

void Graph::add_edge(int start, int stop) {
	aMatrix[start][stop] = true;
	if (!directed) {
		aMatrix[stop][start] = true;
	}
}

void Graph::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	this->cr = cr;

	// set all nodes as not printed
	std::set<Node *>::iterator it;
	for (it = nodes->begin(); it != nodes->end(); ++it) {
		(*it)->printed = false;
	}

	// draw the connections between the nodes
	Vertex * start;
	Vertex * stop;
	for (int i = 1; i < currentNodes; i++) {
		for (int j = 0; j < i; j++) {
			if (aMatrix[i][j]) {
				start = vertices[i];
				stop = vertices[j];
				draw_connection_helper(start->x + Vertex::r / 2, start->y + Vertex::r / 2, stop->x + Vertex::r / 2, stop->y + Vertex::r / 2, NEITHER);
			}
		}
	}

	// draw the nodes in the graph
	draw_connected();
}

void Graph::draw_connected() {
	std::set<Node *>::iterator it;
	for (it = nodes->begin(); it != nodes->end(); ++it) {
		if (!(*it)->printed) {
			(*it)->draw(cr);
		}
	}
}

void Graph::draw_disconnected() {}

void Graph::draw_labels() {}

void Graph::draw_label_helper(Node * label, const char * text, int x, int y, Graph::LabelArrowPos labelPos){}

void Graph::draw_connections(Node * node) {
	// TODO add implementation to connect the nodes
	// TODO make implementation handle the case where the graph is directed/indirected
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

const int Vertex::r = 30;

Vertex::Vertex(){}

Vertex::Vertex(Graph * graph, int x, int y) {
	this->x = x;
	this->xVal = x;
	this->y = y;
	this->yVal = y;
	this->graph = graph;
	graph->startTrackNode(this);
	this->printed = false;
	// store which node was just created and update the counter
	this->aList = graph->aMatrix[graph->currentNodes];
	graph->vertices[graph->currentNodes] = this;
	this->index = graph->currentNodes++;
}

void Vertex::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	this->cr = cr;
	draw_node();
	draw_text();
}

void Vertex::draw_node() {
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->save();
	cr->translate(x + r / 2, y + r / 2);
	cr->scale(r / 2, r / 2);
	cr->arc(0, 0, 1, 0, 2 * M_PI);
	cr->fill();
	cr->restore();
	cr->save();

	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->set_line_width(2.0);
	cr->translate(x + r / 2, y + r / 2);
	cr->scale(r / 2, r / 2);
	cr->arc(0, 0, 1, 0, 2 * M_PI);
	cr->restore();
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->stroke();
}

void Vertex::draw_text() {
	//TODO add text implementation
}
