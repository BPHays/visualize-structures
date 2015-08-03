#ifndef GRAPH_H
#define GRAPH_H

#include "structure.h"
#include "node.h"
#include <gtkmm/drawingarea.h>

class Graph : public Gtk::Widget, public Structure {

	// enums
	public:
		// which directions the arrows point
		enum ConnType {
			FORWARD,
			REVERSE,
			BOTH,
			NEITHER
		};

		enum LabelArrowPos {
			TOP,
			BOTTOM,
			RIGHT,
			LEFT
		};

	// methods
	public:
		//Graph();
		//~Graph();
		// draw the structure
		//virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr)=0;

		// track all of the new nodes that are added
		// TODO rename as "startTrackNode"?
		virtual void startTrackNode(Node * node);

		// stop tracking the node when you delete it
		// TODO rename as "stopTrackNode"?
		virtual void stopTrackNode(Node * node);

		// draw the nodes which are "connected" to the data structure
		// i.e .nodes in the linked list
		virtual void draw_connected()=0;

		// draw nodes which are "outside" of the data structure
		// i.e. nodes which are not part of the linked list but have not been deleted yet
		virtual void draw_disconnected()=0;

		// draw labels on nodes
		virtual void draw_labels()=0;
		virtual void draw_label_helper(Node * label, const char * text, int x, int y, LabelArrowPos labelPos)=0;

		// add connections between the nodes on the graph
		virtual void draw_connections(Node * node)=0;
		virtual void draw_connection_helper(int start_x, int start_y, int end_x, int end_y, Graph::ConnType);

	// memeber variables
	public:
		// the list of nodes associated with the grah
		Node ** nodes;
		// the current number of nodes associated with the graph
		int currentNodes;
		// the list of labels that the user wants to print
		Node ** labels;
		// the starting point for the graph
		int x;
		int y;
};

#endif // GRAPH_H
