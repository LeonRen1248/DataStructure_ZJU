#include "SequentialLinkedList.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    SequentialLinkedList sll1(10, 22);
    cout << sll1 << endl; // { length = 10; data = [ 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, ] }
    
    int arr[12] = {1, 5, 2, 6, 3, 7, 4, 8, 5, 9, };
    SequentialLinkedList sll2(arr, 12);
    cout << sll2 << endl; // { length = 12; data = [ 1, 5, 2, 6, 3, 7, 4, 8, 5, 9, 0, 0, ] }

    SequentialLinkedList sll3(sll2);
    cout << sll3 << endl; // { length = 12; data = [ 1, 5, 2, 6, 3, 7, 4, 8, 5, 9, 0, 0, ] }

    SequentialLinkedList sll4;
    cout << sll4 << endl; // { length = 0; data = [ ] }
    sll4 = sll1;
    cout << sll4 << endl; // { length = 10; data = [ 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, ] }

    sll1.make_empty();
    cout << sll1 << endl; // { length = 0; data = [ ] }

    cout << sll2[6] << endl; // 4

    cout << sll2.find_first(9) << endl; // 9

    sll2.insert(12, 22);
    cout << sll2 << endl; // { length = 13; data = [ 1, 5, 2, 6, 3, 7, 4, 8, 5, 9, 0, 0, 22, ] }

    unsigned int removed_idx = 1;
    cout << "Removed item, which is in the index of " << removed_idx << ", is : " << sll2.remove(1) << endl;
    // Removed item, which is in the index of 1, is : 5
    cout << sll2 << endl; // { length = 12; data = [ 1, 2, 6, 3, 7, 4, 8, 5, 9, 0, 0, 22, ] }
    
    return 0;
}
