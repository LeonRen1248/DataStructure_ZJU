#ifndef __SELF_TREE_H__
#define __SELF_TREE_H__

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <queue>
#include <ostream>

class Tree {
public:
    using element_type = int;
    
    typedef struct TreeNode {
        element_type item;
        struct TreeNode *left;
        struct TreeNode *right;
        TreeNode(element_type _item) : item(_item), left(nullptr), right(nullptr) { }
        TreeNode() : TreeNode(0) { }
    }TreeNode;

    Tree() : tree(nullptr) { }
    Tree(const char **arr, int n);
    Tree(std::vector<const char *> vec);
    Tree(const Tree &tree);
    ~Tree();

    void pre_order_traversal(void (*fp)(element_type item)) const;
    void in_order_traversal(void (*fp)(element_type item)) const;
    void post_order_traversal(void (*fp)(element_type item)) const;
    void level_order_traversal(void (*fp)(element_type item)) const;

    bool is_empty() const { return !tree; }
    
private:
    void oops(const char *str) const { std::cout << str << std::endl; }
    void delete_tree(TreeNode *tn);
    void pre_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const;
    void in_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const;
    void post_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const;
    void level_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const;

    friend std::ostream & operator<<(std::ostream &os, const Tree &tree);

    TreeNode *tree;
};

/**
 * arr 中是层序的顺序，"#" 表示无此节点（也就是 nullptr）
 */
inline Tree::Tree(const char **arr, int n) : tree(nullptr) {
    if (n <= 0) {
        oops("Index out of boundary.");
        return;
    }
    if (!strcmp(arr[0], "#")) {
        return;
    }
    tree = new TreeNode(atoi(arr[0]));
    std::queue<TreeNode *> node_queue;
    node_queue.push(tree);
    for (int i = 1; i <= (n - 1) / 2; ++i) {
        TreeNode *curr_node = node_queue.front();
        node_queue.pop();
        if (strcmp(arr[i * 2 - 1], "#")) {
            curr_node->left = new TreeNode(atoi(arr[i * 2 - 1]));
            node_queue.push(curr_node->left);
        }
        if (strcmp(arr[i * 2], "#")) {
            curr_node->right = new TreeNode(atoi(arr[i * 2]));
            node_queue.push(curr_node->right);
        }
    }
    if (n % 2) {
        TreeNode *curr_node = node_queue.front();
        if (strcmp(arr[n - 1], "#")) {
            curr_node->left = new TreeNode(atoi(arr[n - 1]));
        }
    }
}

inline void Tree::pre_order_traversal(void (*fp)(element_type item)) const {
    pre_order_traversal(tree, fp);
}

inline void Tree::pre_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const {
    if (!tn) { return; }
    fp(tn->item);
    pre_order_traversal(tn->left, fp);
    pre_order_traversal(tn->right, fp);
}

inline Tree::~Tree() {
    delete_tree(tree);
}

inline void Tree::delete_tree(TreeNode *tn) {
    if (!tn) return;
    delete_tree(tn->left);
    delete_tree(tn->right);
    delete tn;
}

void print_value(Tree::element_type value) {
    std::cout << value << ", ";
}

/**
 * 按照先序顺序打印成 [x, y, z, ..., ] 形式
 */
inline std::ostream & operator<<(std::ostream &os, const Tree &tree) {
    os << "[ ";
    tree.pre_order_traversal(print_value);
    os << "]";
}

#endif