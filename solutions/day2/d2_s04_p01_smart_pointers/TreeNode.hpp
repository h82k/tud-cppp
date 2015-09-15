// Author: jgdo, created on: Aug 15, 2013

#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include <memory>
class TreeNode;

// typedef for better readability
typedef std::shared_ptr<TreeNode> TreeNodePtr;

class TreeNode {
public:
	/** create a new tree node and make it shared */
	static TreeNodePtr createNode(int content, TreeNodePtr left = TreeNodePtr(), TreeNodePtr right = TreeNodePtr());
	~TreeNode();
private:
	TreeNode(int content, TreeNodePtr left, TreeNodePtr right);	// create a tree node
	TreeNodePtr leftChild, rightChild;							// left and right child
	int content;												// node content
};

#endif /* TREENODE_HPP_ */
