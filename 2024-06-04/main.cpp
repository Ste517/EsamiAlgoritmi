#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

struct NodeLabel {
	int val;
	int odd;
	int even;
	int level;
	bool operator>(int other) { return this->val > other; }
	explicit NodeLabel(int val) : val(val),odd(0),even(0),level(0) {}
};

struct Node {
	Node* left;
	Node* right;
	NodeLabel val;
	Node() : left(NULL) , right(NULL) , val(0) {}
	explicit Node(NodeLabel val) : left(NULL) , right(NULL) , val(val) {}
};

void addBST(int val, Node* &tree) {
	if (tree == NULL) {
		tree = new Node(NodeLabel(val));
		return;
	}
	if (tree->val > val) {
		addBST(val, tree->left);
	} else {
		addBST(val, tree->right);
	}
}

void deleteBST(Node* &tree) {
	if (tree == NULL) return;
	deleteBST(tree->left);
	deleteBST(tree->right);
	delete tree;
}

int odd(Node* tree) {
	if (tree == NULL) return 0;
	tree->val.odd = (tree->val.val%2) + odd(tree->left) + odd(tree->right);
	return tree->val.odd;
}

int even(Node* tree) {
	if (tree == NULL) return 0;
	tree->val.even = ((tree->val.val+1)%2) + even(tree->left) + even(tree->right);
	return tree->val.even;
}

void level(Node* tree, int lev) {
	if (tree == NULL) return;
	tree->val.level = lev;
	level(tree->left, lev + 1);
	level(tree->right, lev + 1);
}

inline int nDsx(const Node* tree) {
	return (tree->left == NULL) ? 0 : tree->left->val.odd;
}

inline int nPdx(const Node* tree) {
	return (tree->right == NULL) ? 0 : tree->right->val.even;
}

void validNodes(std::vector<int>& nodes, Node* tree) {
	if (tree == NULL) return;
	validNodes(nodes, tree->left);
	validNodes(nodes, tree->right);
	int diff = abs(nPdx(tree)-nDsx(tree));
	if (diff <= tree->val.level) nodes.push_back(tree->val.val);
}

int main() {
	Node* tree = NULL;
	std::vector<int> nodes;
	size_t n,k;
	int temp;
	std::cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		std::cin >> temp;
		addBST(temp, tree);
	}
	odd(tree);
	even(tree);
	level(tree,0);
	validNodes(nodes, tree);
	std::sort(nodes.begin(), nodes.end());
	k = k < nodes.size() ? k : nodes.size();
	for (size_t i = 0; i < k; ++i) {
		std::cout << nodes[i] << std::endl;
	}
	deleteBST(tree);
	return 0;
}
