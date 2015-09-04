#ifndef RBTREE_H
#define RBTREE_H

#include "tree.h"

class RBTreeNode;

class RBTree : public Tree {
	// methods
	public:
		void insert(int key);
		//bool find(int key);
		//bool remove(int key);

		void rightRotate(RBTreeNode * node);
		void leftRotate(RBTreeNode * node);
		void balance(RBTreeNode * node);
};

class RBTreeNode : public TreeNode {
	friend class RBTree;
	// enums
	public:
		enum color {RED, BLACK};

	public:
		// methods
		RBTreeNode(RBTreeNode * parent, RBTree * tree, int data);
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr); 
		RBTreeNode * uncle();
		RBTreeNode * grandparent();

		// member variables
		color node_color;

	public:
		RBTreeNode * parent;
		static const Cairo::RefPtr<Cairo::Pattern> red;
		static const Cairo::RefPtr<Cairo::Pattern> black;
		static const Cairo::RefPtr<Cairo::Pattern> white;
};

#endif // R-BTREE_H
