
#ifndef LIST_H
#define LIST_H

#include <gtkmm/drawingarea.h>
#include "node.h"
#include "graph.h"

class ListNode;

/*
 * A list which automatically tracks created nodes
 */
class List : public Graph {
// Gtk::Widget, public Structure {

	/*
	public:
		enum LabelArrowPos {
			TOP,
			BOTTOM,
			RIGHT,
			LEFT
		};
		*/

	public:
		List();
		~List();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		// keep track of the nodes that are associated with the list
		//void newNode(ListNode * node);
		//void removeFromArray(ListNode * node);
		/*
		virtual void startTrackNode(Node * node);
		virtual void stopTrackNode(Node * node);
		*/
	protected:
		virtual void arrange_nodes();
		// TODO update to use draw connections
		virtual void draw_connections(Node * node);
//		virtual void draw_connection_helper(int start_x, int start_y, int end_x, int end_y, Graph::ConnType);
		virtual void draw_null_arrow(int start_x, int start_y, bool right);
		virtual void draw_connected();
		virtual void draw_disconnected();
		virtual void draw_labels();
		virtual void draw_label_helper(Node * label, const char * text, int x, int y, LabelArrowPos labelPos);

	public:
		ListNode * head;
	protected:
//		int list_x;
//		int list_y;
		int out_x;
		int out_y;
//		Node ** nodes;
//		int currentNodes;
		static const int nodes_size;
};

class ListNode : public Node {
	friend class List;
	public:
		ListNode();
		ListNode(List * list);
		ListNode(List * list, int data);
		ListNode(List * list, int x, int y);
		~ListNode();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_text();
		virtual void draw_node();
		/*
		virtual void draw_text(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y);
		virtual void draw_node(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y);
		*/

	public:
		ListNode * next;
		int data;
		/* part of node.h
		bool printed;
		int x;
		int y;
		*/
		static const int padding;
	protected:
		int numFields;
		static const int field_w;
		static const int field_h;
		/* part of node.h
		Cairo::RefPtr<Cairo::Context> cr;
		*/
		List * list;
};

#endif
