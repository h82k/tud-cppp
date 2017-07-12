#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include <memory>
class TreeNode;

/**
 * typedef for better readability
 */
typedef std::shared_ptr<TreeNode> TreeNodePtr;
/**
 * typedef for better readability
 */
typedef std::weak_ptr<TreeNode> TreeNodeWeakPtr;

/**
 * @name TreeNode
 * @author cppp
 * @brief class to define a node of a binary tree
 */
class TreeNode {
public:
    /**
     * @name TreeNode
     * @author cppp
     * @param content the content of the node
     * @param left shared pointer to the left child
     * @param right shared pointer to the right child
     * using the private constructor of treenode and sets the parent of the left/right node if possible using weak pointers
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
    /**
     * @name setParent(const TreeNodePtr& p);
     * @author cppp
     * @brief sets the parent using the given const treenodepointer ref
     * @param p ref to the treenode which will be used as parent
     */
	void setParent(const TreeNodePtr& p);						// set parent of this node
	TreeNodePtr leftChild, rightChild;							// left and right child
	TreeNodeWeakPtr parent;										// parent node
	int content;												// node content
};

#endif /* TREENODE_HPP_ */
