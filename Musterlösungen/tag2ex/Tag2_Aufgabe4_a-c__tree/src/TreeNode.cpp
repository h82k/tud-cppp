/*
 * TreeNode.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: jgdo
 */

#include "TreeNode.h"

#include <iostream>
using namespace std;

TreeNodePtr TreeNode::createNode(int content, TreeNodePtr left, TreeNodePtr right) {
	return TreeNodePtr(new TreeNode(content, left, right));
}

TreeNode::TreeNode(int content, TreeNodePtr left, TreeNodePtr right) :
		leftChild(left), rightChild(right), content(content) {
	cout << "creating " << content << endl;
}

TreeNode::~TreeNode() {
	cout << "deleting " << content << endl;
}

