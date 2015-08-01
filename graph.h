#ifndef GRAPH_H
#define GRAPH_H

#include "structure.h"
class Graph : Gtk::Widget, public Structure {

	// enums
	public:
		// which directions the arrows point
		enum ConnType {
			FORWARD,
			REVERSE,
			BOTH,
			NEITHER
		}

	// methods
	public:
		// draw the structure
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);

		// track all of the new nodes that are added
		// TODO rename as "startTrackNode"?
		virtual void startTrackNode(Node * node);

		// stop tracking the node when you delete it
		// TODO rename as "stopTrackNode"?
		virtual void stopTrackNode(Node * node);

		// draw the nodes which are "connected" to the data structure
		// i.e .nodes in the linked list
		virtual void draw_connected(const Cairo::RefPtr<Cairo::Context> & cr);

		// draw nodes which are "outside" of the data structure
		// i.e. nodes which are not part of the linked list but have not been deleted yet
		virtual void draw_disconnected(const Cairo::RefPtr<Cairo::Context> & cr);

		// draw labels on nodes
		virtual void draw_labels(const Cairo::RefPtr<Cairo::Context> & cr);

		// add connections between the nodes on the graph
		virtual void draw_connections(const Cairo::RefPtr<Cairo::Context> & cr, ConnType type);

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
}

#endif // GRAPH_H
