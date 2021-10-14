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
        explicit TreeNode(element_type _item) : item(_item), left(nullptr), right(nullptr) { }
        TreeNode() : TreeNode(0) { }
    }TreeNode;

    Tree() : tree(nullptr) { }
    Tree(const char **arr, int n);
    explicit Tree(std::vector<const char *> vec);
    Tree(const Tree &tree);
    ~Tree();

    Tree & operator=(const Tree &t);

    void pre_order_traversal(void (*fp)(element_type item)) const;
    void in_order_traversal(void (*fp)(element_type item)) const;
    void post_order_traversal(void (*fp)(element_type item)) const;
    void level_order_traversal(void (*fp)(element_type item)) const;

    bool is_empty() const { return !tree; }
    
private:
    void oops(const char *str) const { std::cout << str << std::endl; }
    void delete_tree(TreeNode *tn);
    TreeNode * copy_tree(TreeNode *tn);
    
    void pre_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const;
    void in_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const;
    void post_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const;

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
    if (!(n % 2)) {
        TreeNode *curr_node = node_queue.front();
        if (strcmp(arr[n - 1], "#")) {
            curr_node->left = new TreeNode(atoi(arr[n - 1]));
        }
    }
}

inline Tree::Tree(std::vector<const char *> vec) {
    if (vec.size() <= 0) {
        oops("Index out of boundary.");
        return;
    }
    if (!strcmp(vec.at(0), "#")) {
        return;
    }
    tree = new TreeNode(atoi(vec.at(0)));
    std::queue<TreeNode *> node_queue;
    node_queue.push(tree);
    for (int i = 1; i <= (vec.size() - 1) / 2; ++i) {
        TreeNode *curr_node = node_queue.front();
        node_queue.pop();
        const char *tmp = vec.at(i * 2 - 1);
        if (strcmp(vec.at(i * 2 - 1), "#")) {
            curr_node->left = new TreeNode(atoi(vec.at(i * 2 - 1)));
            node_queue.push(curr_node->left);
        }
        if (strcmp(vec.at(i * 2), "#")) {
            curr_node->right = new TreeNode(atoi(vec.at(i * 2)));
            node_queue.push(curr_node->right);
        }
    }
    if (!(vec.size() % 2)) {
        TreeNode *curr_node = node_queue.front();
        if (strcmp(vec.at(vec.size() - 1), "#")) {
            curr_node->left = new TreeNode(atoi(vec.at(vec.size() - 1)));
        }
    }
}

inline Tree::TreeNode *Tree::copy_tree(TreeNode *tn) {
    if (!tn) return nullptr;
    TreeNode *tree_left = copy_tree(tn->left);
    TreeNode *tree_right = copy_tree(tn->right);
    TreeNode *root = new TreeNode(tn->item);
    root->left = tree_left;
    root->right = tree_right;
    return root;
}

inline Tree::Tree(const Tree &t) {
    tree = copy_tree(t.tree);
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

inline void Tree::in_order_traversal(void (*fp)(element_type item)) const {
    in_order_traversal(tree, fp);
}

inline void Tree::in_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const {
    if (!tn) { return; }
    in_order_traversal(tn->left, fp);
    fp(tn->item);
    in_order_traversal(tn->right, fp);
}

inline void Tree::post_order_traversal(void (*fp)(element_type item)) const {
    post_order_traversal(tree, fp);
}

inline void Tree::post_order_traversal(TreeNode *tn, void (*fp)(element_type item)) const {
    if (!tn) { return; }
    post_order_traversal(tn->left, fp);
    post_order_traversal(tn->right, fp);
    fp(tn->item);
}

inline void Tree::level_order_traversal(void (*fp)(element_type item)) const {
    std::queue<TreeNode *> node_queue;
    node_queue.push(tree);
    TreeNode *node;
    while (!node_queue.empty()) {
        node = node_queue.front();
        node_queue.pop();
        fp(node->item);
        if (node->left) {
            node_queue.push(node->left);
        }
        if (node->right) {
            node_queue.push(node->right);
        }
    }
}

inline void Tree::delete_tree(TreeNode *tn) {
    if (!tn) return;
    delete_tree(tn->left);
    delete_tree(tn->right);
    delete tn;
}

inline Tree::~Tree() {
    delete_tree(tree);
}

inline Tree & Tree::operator=(const Tree &t) {
    delete_tree(tree);
    tree = nullptr;
    tree = copy_tree(t.tree);
    return *this;
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