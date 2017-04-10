#include <memory>
class TreeNode;

typedef std::shared_ptr<TreeNode> TreeNodePtr;	// typedef for better readability

class TreeNode {
public:
	/** create a new tree node and make it shared */
	static TreeNodePtr createNode(int content, TreeNodePtr left = TreeNodePtr(), TreeNodePtr right = TreeNodePtr());
	~TreeNode();
private:
	TreeNode(int content, TreeNodePtr left, TreeNodePtr right);	// create a tree node
	TreeNodePtr leftChild, rightChild;									// left and right child
	int content;																// node content
};

