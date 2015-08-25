#ifndef GRAPH_H
#define GRAPH_H

#include "structure.h"
#include "node.h"
#include <gtkmm/drawingarea.h>
#include <set>

class Vertex;

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
		Graph();
		//~Graph();
		// draw the structure
		//virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr)=0;

		// track all of the new nodes that are added
		virtual void startTrackNode(Node * node);

		// stop tracking the node when you delete it
		virtual void stopTrackNode(Node * node);

		// track pointers to have them drawn
		virtual void startTrackLabel(Node * label);
		virtual void stopTrackLabel(Node * label);

		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);

		// draw the nodes which are "connected" to the data structure
		// i.e .nodes in the linked list
		virtual void draw_connected();

		// draw nodes which are "outside" of the data structure
		// i.e. nodes which are not part of the linked list but have not been deleted yet
		virtual void draw_disconnected();

		// draw labels on nodes
		virtual void draw_labels();
		virtual void draw_label_helper(Node * label, const char * text, int x, int y, LabelArrowPos labelPos);

		// add connections between the nodes on the graph
		virtual void draw_connections(Node * node);
		virtual void draw_connection_helper(int start_x, int start_y, int end_x, int end_y, Graph::ConnType);

		// add an edge between two verticies
		virtual void add_edge(int start, int stop);

	// memeber variables
	public:
		// the list of nodes associated with the grah
		std::set<Node *> * nodes;
		// the current number of nodes associated with the graph
		int currentNodes;
		// the list of labels that the user wants to print
		std::set<Node *> * labels;
		// the starting point for the graph

		// the adjacency matrix of the graph
		bool ** aMatrix;

		// the array of vertecies
		Vertex ** vertices;

		// whether the graph is a directed or an indircted graph
		bool directed;
};

class Vertex : public Node {
	friend class Graph;
	// methods
	public :
		Vertex(Graph * graph, int x, int y);
		Vertex();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_node();
		virtual void draw_text();

	// member variables
	public :
		// the value of the position in the graph
		int xVal;
		int yVal;
		// the position of the vertex in the adjacency list
		int index;
		// the adjacency list of the vertex
		bool * aList;
		// the graph the vertex belongs to 
		Graph * graph;
	protected:
		// the radius of the vertex
		static const int r;
};

#endif // GRAPH_H
