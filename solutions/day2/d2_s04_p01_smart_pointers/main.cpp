#include "TreeNode.hpp"
#include <iostream>

int main() {
	TreeNodePtr node = TreeNode::createNode(1, TreeNode::createNode(2), TreeNode::createNode(3));
	std::cout << "node created" << std::endl;
	
	node = TreeNode::createNode(4, TreeNode::createNode(5), TreeNode::createNode(6));
	std::cout << "exiting program" << std::endl;
}
