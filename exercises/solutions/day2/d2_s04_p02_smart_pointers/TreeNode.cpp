#include "TreeNode.hpp"
#include <iostream>

TreeNodePtr TreeNode::createNode(int content, TreeNodePtr left, TreeNodePtr right) {
	TreeNodePtr node(new TreeNode(content, left, right));
	if (left) {
		left->setParent(node);
	}
	if (right) {
		right->setParent(node);
	}
	return node;
}

TreeNode::TreeNode(int content, TreeNodePtr left, TreeNodePtr right):
	leftChild(left), rightChild(right), content(content)
{
	std::cout << "creating " << content << std::endl;
}

TreeNode::~TreeNode() {
	std::cout << "deleting " << content << std::endl;
}

void TreeNode::setParent(const TreeNodePtr& p) {
	parent = p;
}

