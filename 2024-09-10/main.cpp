#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

struct ABR {
    ABR* left;
    ABR* right;
    int label;
    int leaves;
    ABR() : left(NULL) , right(NULL) , label(0) {}
    ABR(int label) : left(NULL) , right(NULL) , label(label) {}
    bool isLeaf() {
        return (left == NULL && right == NULL);
    }
    ~ABR() {
        delete left;
        delete right;
    }
};

void addNode(int label, ABR* &tree) {
    if (tree == NULL) {
        tree = new ABR(label);
        return;
    }
    if (label > tree->label) addNode(label,tree->right);
    else addNode(label,tree->left);
}

int refresh(ABR* tree) {
    if (tree == NULL) return 0;
    if (tree->isLeaf()) {
        tree->leaves = 1;
        return 1;
    }
    tree->leaves = refresh(tree->left) + refresh(tree->right);
    return tree->leaves;
}

void validNodes(std::vector<std::pair<int,int>>& nodes, const ABR* tree, int level) {
    if (tree == NULL) return;
    if (tree->leaves % 2 == 0) nodes.push_back({level, tree->label});
    validNodes(nodes,tree->left,level+1);
    validNodes(nodes,tree->right,level+1);
}

bool comparePair(const std::pair<int,int>& p1,const std::pair<int,int>& p2) {
    if (p1.first == p2.first) {
        return p1.second > p2.second;
    }
    return p1.first > p2.first;
}

int main() {
    ABR* tree = NULL;
    size_t N, K;
    int val;
    std::vector<std::pair<int,int>> nodes;
    std::cin >> N >> K;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> val;
        addNode(val, tree);
    }
    refresh(tree);
    validNodes(nodes,tree,0);
    std::sort(nodes.begin(),nodes.end(),comparePair);

    for (size_t i = 0; i < K && i < nodes.size(); ++i) {
        std::cout << nodes[i].second << std::endl;
    }
    return 0;
}
