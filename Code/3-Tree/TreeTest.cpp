#include "Tree.h"
#include <iostream>
#include <vector>

using namespace std;

void print_node(Tree::element_type value) {
    cout << value;
}

int main(int argc, char const *argv[]) {
    const char *arr[10] = {"1", "2", "3", "4", "5", "6", "7", "#", "8", "9"};
    Tree tree(arr, 10);
    cout << tree << endl;
    
    return 0;
}
