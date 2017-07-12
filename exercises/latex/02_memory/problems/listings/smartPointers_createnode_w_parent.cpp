TreeNodePtr TreeNode::createNode(int content, TreeNodePtr left, TreeNodePtr right) {
	TreeNodePtr node(new TreeNode(content, left, right));
	if (left) {
		left-> ... ; // set parent node
	}
	if (right) {
		right-> ... ; // set parent node
	}
	return node;
}
