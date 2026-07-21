#define HASH_A 1000
#define HASH_B 2000
#define HASH_P 999149

#include <iostream>
#include <string>
#include <vector>

class HashTable {
	struct Node {
		std::string stringa;
		Node* left;
		Node* right;
		size_t max;
		size_t intero;
		Node(const std::string& stringa, const size_t intero) : stringa(stringa) , intero(intero) , max(0) , left(NULL) , right(NULL) {}
	};
	static size_t updateMax(Node* &tree) {
		if (tree == NULL) return 0;
		size_t max = tree->stringa.length();
		size_t max_l = updateMax(tree->left);
		size_t max_r = updateMax(tree->right);
		if (max_l > max) max = max_l;
		if (max_r > max) max = max_r;
		tree->max = max;
		return max;	
	}
	static void addNode(const std::string& stringa, const size_t intero, Node* &tree) {
		if (tree == NULL) {
			tree = new Node(stringa,intero);
			return;
		}
		if (intero > tree->intero) {
			addNode(stringa,intero,tree->right);
		} else {
			addNode(stringa,intero,tree->left);
		}
	}
	static void deleteTree(Node* &tree) {
		if (tree == NULL) return;
		deleteTree(tree->left);
		deleteTree(tree->right);
		delete tree;
	}
	static inline size_t Max(const Node* tree) {
		return (tree == NULL ? 0 : tree->max);
	}
	static size_t validNodes(const Node* tree, int level) {
		if (tree == NULL) return 0;
		size_t max_sx = Max(tree->left);
		size_t max_dx = Max(tree->right);
		return (((max_sx > max_dx ? max_sx - max_dx : max_dx - max_sx) <= level) ? 1 : 0) + validNodes(tree->left,level+1) + validNodes(tree->right,level+1);
	}
	const size_t K;
	const size_t M;
	std::vector<Node*> table;
	inline size_t hash_fun(size_t I) {
		return (((HASH_A * I) + HASH_B) % HASH_P) % M;
	}
public:
	HashTable(const size_t M, const size_t K) : M(M) , K(K) {
		table.resize(M);
	}
	void addElement(const std::string& stringa, const size_t intero) {
		addNode(stringa,intero,table[hash_fun(intero)]);
	}
	void reload() {
		for (size_t i = 0; i < table.size(); ++i) {
			updateMax(table[i]);
		}
	}
	friend std::ostream& operator<<(std::ostream& os, HashTable& ht);
	~HashTable() {
		for (size_t i = 0; i < table.size(); ++i) {
			deleteTree(table[i]);
		}
	}
};

std::ostream& operator<<(std::ostream& os, HashTable& ht) {
	ht.reload();
	for (size_t i = 0; i < ht.table.size(); ++i) {
		if (ht.validNodes(ht.table[i], 0) >= ht.K) os << i <<   std::endl;
	}
	return os;
}

int main() {
	size_t N,K,M;
	std::cin >> N >> K >> M;
	HashTable hash(M,K);
	for (size_t i = 0; i < N; ++i) {
		std::string ss;
		size_t intero;
		std::cin >> intero >> ss;
		hash.addElement(ss,intero);
	}
	std::cout << hash;
}
