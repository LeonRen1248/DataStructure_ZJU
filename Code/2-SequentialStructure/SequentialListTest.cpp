#include "SequentialList.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int int_arr[12] = {1, 2, 3, 4, 5, 6, 7};
    SequentialList st(int_arr, 12);
    cout << st << endl; // [ 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, ]

    SequentialList::element_type value = st[5];
    cout << value << endl; // 6
    
    cout << st[13] << endl;
    // Index out of boundary.
    // -1

    cout << st.find_first(7) << endl; // 6

    cout << st.find_first(13) << endl; // -1

    cout << st.find_last(0) << endl; // 11

    st.insert(22, 22); // Index out of boundary.
    cout << st << endl; // [ 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, ]
    st.insert(10, 22);
    cout << st << endl; // [ 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 22, 0, 0, ]

    cout << st.get_len() << endl; // 13

    unsigned int removed_idx = 10;
    cout << "Removed item, which is in the index of " << removed_idx
        << ", is " << st.remove(removed_idx) << endl;
    // Removed item, which is in the index of 10, is 22
    cout << st << endl; // [ 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, ]
    
    return 0;
}
