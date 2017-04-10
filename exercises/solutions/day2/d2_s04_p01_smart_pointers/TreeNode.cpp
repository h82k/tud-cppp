/*
 * TreeNode.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: jgdo
 */

#include "TreeNode.hpp"
#include <iostream>

TreeNodePtr TreeNode::createNode(int content, TreeNodePtr left, TreeNodePtr right) {
	return TreeNodePtr(new TreeNode(content, left, right));
}

TreeNode::TreeNode(int content, TreeNodePtr left, TreeNodePtr right):
	leftChild(left), rightChild(right), content(content)
{
	std::cout << "creating " << content << std::endl;
}

TreeNode::~TreeNode() {
	std::cout << "deleting " << content << std::endl;
}

