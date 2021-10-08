#include "SequentialLinkedList.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    SequentialLinkedList sll1(10, 22);
    cout << sll1 << endl;
    
    int arr[12] = {1, 5, 2, 6, 3, 7, 4, 8, 5, 9, };
    SequentialLinkedList sll2(arr, 12);
    cout << sll2 << endl;

    SequentialLinkedList sll3(sll2);
    cout << sll3 << endl;

    SequentialLinkedList sll4;
    cout << sll4 << endl;
    sll4 = sll1;
    cout << sll4 << endl;

    sll1.make_empty();
    cout << sll1 << endl;

    cout << sll2.find_kth(6) << endl;

    cout << sll2.find_first(9) << endl;

    sll2.insert(12, 22);
    cout << sll2 << endl;

    unsigned int removed_idx = 1;
    cout << "Removed item, which is in the index of " << removed_idx << ", is : " << sll2.remove(1) << endl;
    cout << sll2 << endl;
    
    return 0;
}
