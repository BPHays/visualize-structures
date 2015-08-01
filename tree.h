
class TreeNode;

class Tree : Gtk::Widget, public Structure {
	// methods
	public:
		Tree();
		~Tree();
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		void newNode(TreeNode * node);
		void removeFromArray(ListNode * node)
	private:

	// member variables
	public:
	private:
}


class TreeNode {
	friend class Tree;
}
