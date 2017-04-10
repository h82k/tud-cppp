#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include <memory>
class TreeNode;

/**
 * typedef for better readability
 */
typedef std::shared_ptr<TreeNode> TreeNodePtr;

/**
 * @name TreeNode
 * @author cppp
 * @brief class to define a node of a binary tree
 */
class TreeNode {
public:
    /**
     * @name createNode(int content, TreeNodePtr left = TreeNodePtr(), TreeNodePtr right = TreeNodePtr());
     * @author cppp
     * @brief used to create a static treenode using smart pointers and the private treenode constructor
     * @param content the content of the node
     * @param left shared pointer to the left child
     * @param right shared pointer to the right child
     * @sa TreeNode(int content, TreeNodePtr left, TreeNodePtr right);
     */
	static TreeNodePtr createNode(int content, TreeNodePtr left = TreeNodePtr(), TreeNodePtr right = TreeNodePtr());
    /**
     * @name ~TreeNode();
     * @author cppp
     * @brief destructor of the treenode object
     */
	~TreeNode();
private:
    /**
     * @name TreeNode(int content, TreeNodePtr left, TreeNodePtr right);
     * @author cppp
     * @brief constructor of a treenode object
     */
	TreeNode(int content, TreeNodePtr left, TreeNodePtr right);	// create a tree node
	TreeNodePtr leftChild, rightChild;							// left and right child
	int content;												// node content
};

#endif /* TREENODE_HPP_ */
