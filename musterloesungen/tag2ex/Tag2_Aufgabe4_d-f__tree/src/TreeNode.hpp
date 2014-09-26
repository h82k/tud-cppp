/*
 * TreeNode.hpp
 *
 *  Created on: Aug 15, 2013
 *      Author: jgdo
 */

#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

class TreeNode;

// typedef for better reading
typedef boost::shared_ptr<TreeNode> TreeNodePtr;
typedef boost::weak_ptr<TreeNode> TreeNodeWeakPtr;

class TreeNode {
public:
	/** Creates a new tree node and makes it shared */
	static TreeNodePtr createNode(int content, TreeNodePtr left = TreeNodePtr(), TreeNodePtr right = TreeNodePtr());

	/** Tree node destructor **/
	~TreeNode();

private:
	/** Creates a tree node */
	TreeNode(int content, TreeNodePtr left, TreeNodePtr right);
	
	/** Set parent of this node */
	void setParent(const TreeNodePtr& p);

	/** left and right child */
	TreeNodePtr leftChild, rightChild;
	
	/** parent node */
	TreeNodeWeakPtr parent;

	/** node content */
	int content;
};

#endif /* TREENODE_HPP_ */
