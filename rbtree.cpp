
#include "visualize.h"
#include "rbtree.h"
#include <cairomm/context.h>
#include <iostream>

// initialize constants
const Cairo::RefPtr<Cairo::Pattern> RBTreeNode::red = Cairo::SolidPattern::create_rgb(1.0, 0.0, 0.0);
const Cairo::RefPtr<Cairo::Pattern> RBTreeNode::black = Cairo::SolidPattern::create_rgb(0.0, 0.0, 0.0); 
const Cairo::RefPtr<Cairo::Pattern> RBTreeNode::white = Cairo::SolidPattern::create_rgb(1.0, 1.0, 1.0);

/*
 * insert a node into the red black tree and rebalance if necessary
 */
void RBTree::insert(int key) {
	// insert the node into the tree
	RBTreeNode * node = static_cast<RBTreeNode *> (root);
	RBTreeNode * parent = NULL;
	int cmp;
	while (node != NULL) {
		if (key > node->data) {
			parent = node;
			node = static_cast<RBTreeNode *> (node->right);
		} else if (key < node->data) {
			parent = node;
			node = static_cast<RBTreeNode *> (node->left);
		} else {
			// node already inserted
			return;
		}
	}
	// reached the bottom of the tree
	RBTreeNode * newNode = new RBTreeNode(parent, this, key);

	// insert the node into the linked list
	if (parent == NULL) {
		root = newNode;
	} else {
		// find which side to insert the new node on
		if (newNode->data > parent->data) {
			parent->right = newNode;
		} else {
			parent->left = newNode;
		}
	}

	// make sure that the tree is balanced
	balance(newNode);
}

/*
 * delete a node from the tree and rebalance if necesary
 */
/*
void RBTree::remove(int key) {
	
}
*/

/*
 * rotate the node so that it becomes the right child of its left child
 */
void RBTree::rightRotate(RBTreeNode * node) {
	RBTreeNode *beta, *pivot;
	beta = static_cast<RBTreeNode *> (node->left->right);
	pivot = static_cast<RBTreeNode *> (node->left);

	// rotate the node
	pivot->right = node;
	node->left = beta;

	// if beta is not null then update it's parent pointer
	if (beta) {
		beta->parent = node;
	}

	// if the node that has been rotated was the root then update the root
	// and make sure that the node is black. otherwise make sure that the
	// node above is pointing to the pivot node
	if (root == node) {
		root = pivot;
		pivot->node_color = RBTreeNode::BLACK;
	} else {
		if (node == node->parent->right) {
			node->parent->right = pivot;
		} else {
			node->parent->left = pivot;
		}
	}

	// update the parent poiniters
	pivot->parent = node->parent;
	node->parent = pivot;
}

/*
 * rotate the node so that it becomes the left child of its right child
 */
void RBTree::leftRotate(RBTreeNode * node) {
	RBTreeNode *beta, *pivot;
	beta = static_cast<RBTreeNode *> (node->right->left);
	pivot = static_cast<RBTreeNode *> (node->right);

	// rotate the node
	pivot->left = node;
	node->right = beta;

	// if beta is not null then update it's parent pointer
	if (beta) {
		beta->parent = node;
	}

	// if the node that has been rotated was the root then update the root
	// and make sure that the node is black. otherwise make sure that the
	// node above is pointing to the pivot node
	if (root == node) {
		root = pivot;
		pivot->node_color = RBTreeNode::BLACK;
	} else {
		if (node == node->parent->right) {
			node->parent->right = pivot;
		} else {
			node->parent->left = pivot;
		}
	}

	// update the parent poiniters
	pivot->parent = node->parent;
	node->parent = pivot;
}

/*
 * make sure that the tree is balanced. If not fix it through recoloring or rotating nodes
 */
void RBTree::balance(RBTreeNode * node) {
	// make sure that the tree satisfies the red black properties
	if (node == root) {
		// make sure that the root node is black
		node->node_color = RBTreeNode::BLACK;
	} else if (node->parent->node_color == RBTreeNode::BLACK) {
		// the node's parent is black so the insertion does not violate
		// an properties of the red black tree
		return;
	} else if (node->uncle() != NULL && node->uncle()->node_color == RBTreeNode::RED) {
		// if both the children of the grandparent are red color them black and color the
		// grandparen red, which will have no effect on black height of the nodes, but
		// may violate the rb properties for the grandparent
		node->parent->node_color = RBTreeNode::BLACK;
		node->uncle()->node_color = RBTreeNode::BLACK;
		node->grandparent()->node_color = RBTreeNode::RED;

		// make sure the tree from the grandparent onwards is balanced
		balance(node->grandparent());
	} else {
		// the node's parent is red and the uncle is black

		// update the parent and grandparents nodes to the apropriate colors
		node->parent->node_color = RBTreeNode::BLACK;
		node->grandparent()->node_color = RBTreeNode::RED;
		if (node->parent == node->grandparent()->left) {
			if (node == static_cast<RBTreeNode *> (node->parent->right)) {
				// if there is a left right pattern between the grandparent and the node
				// change it so that the it is a left left pattern and continue to the next
				// step
				leftRotate(node->parent);
			}
			if (node == static_cast<RBTreeNode *> (node->parent->left)) {
				// if there is a left left pattern between the grandparent and the node
				// rotate the grandparent
				rightRotate(node->grandparent());
			}
		} else {
			// the node is the grandparent's right child
			// this is the same as the previous case but with the directions reversed
			if (node == static_cast<RBTreeNode *> (node->parent->left)) {
				rightRotate(node->parent);
			}
			if (node == static_cast<RBTreeNode *> (node->parent->right)) {
				leftRotate(node->grandparent());
			}
		}
	}
}

/*
 * create a new red node that is a child of parent
 */
RBTreeNode::RBTreeNode(RBTreeNode * parent, RBTree * tree, int data) : TreeNode(tree, data){
	node_color = RED;
	this->tree = tree;
	this->parent = parent;
	right = NULL;
	left = NULL;
}

/*
 * get the current node's grandparent
 */
RBTreeNode * RBTreeNode::grandparent() {
	return static_cast<RBTreeNode *> (parent->parent);
}

/*
 * get the current node's uncle which is the grandparents child which is not
 * the current node's parent
 */
RBTreeNode * RBTreeNode::uncle() {
	return this == parent->left ? static_cast<RBTreeNode *> (parent->parent->right) : static_cast<RBTreeNode *> (parent->parent->left);
}

void RBTreeNode::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	if (node_color == RED) {
		bg_color = red;
		txt_color = black;
	} else if (node_color == BLACK) {
		bg_color = black;
		txt_color = white;
	}
	TreeNode::draw(cr);
}
