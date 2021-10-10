#include <iostream>
#include <vector>

using namespace std;

typedef int item_type;

int sequential_search(vector<item_type> list, item_type item) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == item) return i;
    }
    return -1; // Not Found
}

int binary_search(vector<item_type> sorted_list, item_type item) {
    int left = 0, right = sorted_list.size() - 1;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (item == sorted_list[middle]) return middle;
        else if (item < sorted_list[middle]) right = middle - 1;
        else left = middle + 1;
    }
    return -1;
}

int main(int argc, char const *argv[]) {
    vector<item_type> list{5, 7, 8, 9, 12};
    item_type item = 5;
    cout << binary_search(list, item) << endl;
    
    return 0;
}
