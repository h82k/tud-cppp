/*
 * TreeNode.h
 *
 *  Created on: Aug 15, 2013
 *      Author: jgdo
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <boost/shared_ptr.hpp>

class TreeNode;

// typedef for better reading
typedef boost::shared_ptr<TreeNode> TreeNodePtr;

class TreeNode {
public:
	/** Creates a new tree node and makes it shared */
	static TreeNodePtr createNode(int content, TreeNodePtr left = TreeNodePtr(), TreeNodePtr right = TreeNodePtr());

	/** Tree node destructor **/
	~TreeNode();

private:
	/** Creates a tree node */
	TreeNode(int content, TreeNodePtr left, TreeNodePtr right);

	/** left and right child */
	TreeNodePtr leftChild, rightChild;

	/** node content */
	int content;
};

#endif /* TREENODE_H_ */
