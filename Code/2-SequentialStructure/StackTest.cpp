#include "Stack.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    Stack stk1;
    cout << stk1 << endl;

    Stack stk2(10, 22);
    cout << stk2 << endl;

    int arr[6] = {1, 2, 3, 4, 5, 6};
    Stack stk3(arr, 6);
    cout << stk3 << endl;

    Stack stk4(stk3);
    cout << stk4 << endl;

    Stack stk5 = stk4;
    cout << stk4 << endl;

    stk5.push(222);
    cout << stk5 << endl;

    cout << stk5.top() << endl;

    cout << stk5.pop() << endl;
    cout << stk5 << endl;

    cout << stk1.is_empty() << endl;
    cout << stk5.is_empty() << endl;

    stk5.make_empty();
    cout << stk5 << endl;
    
    return 0;
}
