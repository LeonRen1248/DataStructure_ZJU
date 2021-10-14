#include "Tree.h"
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void print_node(Tree::element_type value) {
    cout << value << ", ";
}

int main(int argc, char const *argv[]) {
    const char *arr[10] = {"1", "2", "3", "4", "5", "6", "7", "#", "8", "9", };
    Tree tree(arr, 10);
    cout << tree << endl; // [ 1, 2, 4, 8, 5, 9, 3, 6, 7, ]

    vector<const char *> vec{"5", "6", "7", "#", "8", "9", "1", "2", "3", "4", };
    Tree tree2(vec);
    cout << tree2 << endl; // [ 5, 6, 8, 2, 3, 7, 9, 4, 1, ]

    Tree tree4 = tree2; // 此处是调用构造函数 Tree(const Tree &tree);
    cout << tree4 << endl; // [ 5, 6, 8, 2, 3, 7, 9, 4, 1, ]

    Tree tree3(tree2);
    cout << tree3 << endl; // [ 5, 6, 8, 2, 3, 7, 9, 4, 1, ]

    tree3 = tree;
    cout << tree3 << endl; // [ 1, 2, 4, 8, 5, 9, 3, 6, 7, ]

    tree3.pre_order_traversal(print_node); cout << endl;
    tree3.in_order_traversal(print_node); cout << endl;
    tree3.post_order_traversal(print_node); cout << endl;
    
    return 0;
}
