
#ifndef LIST_H
#define LIST_H

#include <gtkmm/drawingarea.h>
#include "structure.h"

class ListNode;

/*
 * A list which automatically tracks created nodes
 */
class List : Gtk::Widget, public Structure {
	friend class DList;

	public:
		enum LabelArrowPos {
			TOP,
			BOTTOM,
			RIGHT,
			LEFT
		};

	public:
		List();
		~List();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		// keep track of the nodes that are associated with the list
		//void newNode(ListNode * node);
		//void removeFromArray(ListNode * node);
		void startTrackNode(ListNode * node);
		void stopTrackNode(ListNode * node);
	private:
		virtual void arrange_nodes();
		virtual void draw_arrows(const Cairo::RefPtr<Cairo::Context> & cr, ListNode * node);
		virtual void draw_arrow_helper(const Cairo::RefPtr<Cairo::Context> & cr, int start_x, int start_y, int end_x, int end_y);
		virtual void draw_null_arrow(const Cairo::RefPtr<Cairo::Context> & cr, int start_x, int start_y, bool right);
		virtual void draw_connected(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_disconnected(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_labels(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_label_helper(const Cairo::RefPtr<Cairo::Context> & cr, ListNode * label, const char * text, int x, int y, LabelArrowPos labelPos);

	public:
		ListNode * head;
	private:
		int list_x;
		int list_y;
		int out_x;
		int out_y;
		ListNode ** nodes;
		int currentNodes;
		static const int nodes_size;
};

class ListNode : public Gtk::Widget {
	friend class List;
	public:
		ListNode();
		ListNode(List * list);
		ListNode(List * list, int data);
		ListNode(List * list, int x, int y);
		~ListNode();
		/*
		 * in node.h
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_text(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y);
		virtual void draw_node(const Cairo::RefPtr<Cairo::Context> & cr, int x, int y);
		*/

	public:
		ListNode * next;
		int data;
		/*
		 * in node.h
		bool printed;
		int x;
		int y;
		*/
		static const int padding;
	protected:
		int numFields;
		static const int field_w;
		static const int field_h;
		List * list;
};

#endif
