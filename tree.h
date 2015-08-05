#ifndef TREE_H
#define TREE_H

#include "graph.h"
#include "node.h"

class TreeNode;

class Tree : public Graph {
	// methods
	public:
		Tree();
		~Tree();
	protected:
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_connections(Node * node);
		virtual void draw_connected();
		virtual void draw_disconnected();
		virtual void draw_labels();
		virtual void draw_label_helper(Node * label, const char * text, int x, int y, LabelArrowPos labelPos);
		int get_height();
		int get_height_helper(TreeNode * n);
		virtual void arrange_nodes();
		virtual void arrange_nodes_helper(TreeNode * n, int level, int pos, int numInLevel);

	// member variables
	public:
		TreeNode * root;
	protected:
		int w;
		int h;

};

class TreeNode : public Node {
	friend class Tree;

	// methods
	public:
		TreeNode(Tree * tree, int data);
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		virtual void draw_text();
		virtual void draw_node();

	// member variables
	public:
		int data;
		TreeNode * left;
		TreeNode * right;
		static const int padding;
	protected:
		static const int w;
		static const int h;
		Tree * tree;
};

#endif // TREE_H
