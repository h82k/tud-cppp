/*
 * TreeNode.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: jgdo
 */

#include "TreeNode.hpp"

#include <iostream>
using namespace std;

TreeNodePtr TreeNode::createNode(int content, TreeNodePtr left, TreeNodePtr right) {
	TreeNodePtr node(new TreeNode(content, left, right));
	if (left)
		left->setParent(node);
	if (right)
		right->setParent(node);
	return node;
}

TreeNode::TreeNode(int content, TreeNodePtr left, TreeNodePtr right) :
		leftChild(left), rightChild(right), content(content) {
	cout << "creating " << content << endl;
}

TreeNode::~TreeNode() {
	cout << "deleting " << content << endl;
}

void TreeNode::setParent(const TreeNodePtr& p) {
	parent = p;
}

