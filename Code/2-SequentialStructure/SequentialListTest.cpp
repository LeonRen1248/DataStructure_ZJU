#include "SequentialList.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int int_arr[12] = {1, 2, 3, 4, 5, 6, 7};
    SequentialList st(int_arr, 12);
    cout << st << endl;

    SequentialList::element_type value = st.find_kth(5);
    
    cout << st.find_kth(13) << endl;

    cout << st.find_first(7) << endl;

    cout << st.find_first(13) << endl;

    cout << st.find_last(0) << endl;

    st.insert(22, 22);
    st.insert(10, 22);
    cout << st << endl;

    cout << st.get_len() << endl;

    
    return 0;
}
