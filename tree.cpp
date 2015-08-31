
#include "visualize.h"
#include "tree.h"
#include <cairomm/context.h>
#include <iostream>
#include <stack>
#include <math.h>

Tree::Tree() {
	x = 50;
	y = 50;
	root = NULL;
	nodes = new std::set<Node *>;
	labels = new std::set<Node *>;
}

Tree::~Tree() {
}

void Tree::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	this->cr = cr;

	// set the position of each of the nodes in the tree
	arrange_nodes();

	// set all nodes as not printed
	std::set<Node *>::iterator it;
	for (it = nodes->begin(); it != nodes->end(); ++it) {
		(*it)->printed = false;
	}

	// draw the nodes
	draw_labels();
	draw_connected();
	draw_disconnected();
}

void Tree::arrange_nodes() {
	// the width of the base of the tree is 2^(h-1)
	int baseNodes = (int) pow(2, get_height() - 1);
	w = baseNodes * TreeNode::w + (baseNodes - 1) * TreeNode::padding;
	sWidth = w;
	arrange_nodes_helper(root, 1, 0, 1);
}

void Tree::arrange_nodes_helper(TreeNode * n, int level, int pos, int numInLevel) {
	if (!n) return;
	n->y = level * TreeNode::h + (level - 1) * TreeNode::padding;
	n->x = w / (numInLevel * 2) + pos * w / numInLevel;
	arrange_nodes_helper(n->left, level + 1, 2 * pos, numInLevel * 2);
	arrange_nodes_helper(n->right, level + 1, 2 * pos + 1, numInLevel * 2);
}

void Tree::draw_connected() {
	// handle the case where the tree is empty
	if (root == NULL) return;

	// draw the nodes iteratively
	std::stack<TreeNode *> s;
	s.push(root);
	TreeNode * n;
	while (!s.empty()){
		n = s.top();
		s.pop();
		draw_connections(n);
		n->draw(cr);
		n->printed = true;
		if (n->left != NULL) s.push(n->left);
		if (n->right != NULL) s.push(n->right);
	}
}

void Tree::draw_disconnected() {
	int yTmp = y + h * (TreeNode::h + TreeNode::padding);
	int xTmp = x;
	std::set<Node *>::iterator it;
	for (it = nodes->begin(); it != nodes->end(); ++it) {
		if (!(*it)->printed) {
			(*it)->y = yTmp;
			(*it)->x = xTmp;
			(*it)->draw(cr);
			draw_connections(*it);
			xTmp += 2 * ListNode::padding;
		}
	}
}

void Tree::draw_labels() {
	// TODO update position to better fit the tree
	draw_label_helper(root, "root", w / 2, y - 50, BOTTOM);
}

void Tree::draw_label_helper(Node * label, const char * text, int x, int y, LabelArrowPos labelPos) {
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
		draw_connection_helper(x + text_w / 2, y + text_h , label->x + TreeNode::w / 2, label->y + 10, NEITHER);
	}
}

int Tree::get_height() {
	h = get_height_helper(root);
	// TODO add more precise value here
	sHeight = h * 100;
	return h;
}

void Tree::draw_connections(Node * node) {
	TreeNode * tNode = dynamic_cast <TreeNode *>  (node);
	if (tNode->right) {
		draw_connection_helper( tNode->x + TreeNode::w / 2, tNode->y + TreeNode::h / 2, tNode->right->x + TreeNode::w / 2, tNode->right->y + TreeNode::h / 2, NEITHER);
	}
	if (tNode->left) {
		draw_connection_helper( tNode->x + TreeNode::w / 2, tNode->y + TreeNode::h / 2, tNode->left->x + TreeNode::w / 2, tNode->left->y + TreeNode::h / 2, NEITHER);
	}
}

int Tree::get_height_helper(TreeNode * n) {
	// check if the node is null
	if (n) {
		int l = get_height_helper(n->left);
		int r = get_height_helper(n->right);
		if (l > r) {
			return l + 1;
		} else {
			return r + 1;
		}
	} else {
		return 0;
	}
}

const int TreeNode::w = 50;
const int TreeNode::h = 30;
const int TreeNode::padding = 50;

TreeNode::TreeNode(Tree * tree, int data) {
	left = NULL;
	right = NULL;
	this->tree = tree;
	tree->startTrackNode(this);
	printed = false;
	this->data = data;
}

void TreeNode::draw(const Cairo::RefPtr<Cairo::Context> & cr) {
	this->cr = cr;
	cr->set_source_rgb(1.0, 1.0, 1.0);
	draw_node();
	cr->set_source_rgb(0.0, 0.0, 0.0);
	draw_text();
}

void TreeNode::draw_node() {
//	cr->rectangle(x, y, w, h);
	cr->save();
	cr->translate(x + w / 2, y + h / 2);
	cr->scale(w / 2, h / 2);
	cr->arc(0, 0, 1, 0, 2 * M_PI);
	cr->fill();
	cr->restore();
	cr->save();

	cr->set_line_width(2.0);
	cr->translate(x + w / 2, y + h / 2);
	cr->scale(w / 2, h / 2);
	cr->arc(0, 0, 1, 0, 2 * M_PI);
	cr->restore();
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->stroke();
}
void TreeNode::draw_text() {
	cr->save();
	char * str = new char[10];
	sprintf(str, "%d", data);

	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);
	Glib::RefPtr<Pango::Layout> layout = create_pango_layout(str);
	layout->set_font_description(font);
	int text_w, text_h;
	layout->get_pixel_size(text_w, text_h);
	cr->move_to(x + (w - text_w) / 2, y + (h - text_h) / 2);
	layout->show_in_cairo_context(cr);
	cr->restore();
}
