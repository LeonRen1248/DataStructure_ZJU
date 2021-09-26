#include <iostream>
#include <vector>

#define HAVE_MAIN // If you want to delete main function, just comment this line.

using namespace std;


// ==================================================

// O(N^3)
int MaxSubseqSum1(const vector<int> &intList) {
    int N = intList.size();
    if (N == 0) return 0;
    // 课件上的代码，下面这一句变量 maxSum 初始化的时候有问题
    // 如果初始化为0，则当数组元素全为负数的时候，会产生0的答案（错误）
    // 应该初始化为 intList[0]
    int maxSum = intList[0], thisSum = 0;
    for (int startIdx = 0; startIdx < N; startIdx++) {
        for (int endIdx = startIdx; endIdx < N; endIdx++) {
            thisSum = 0;
            for (int i = startIdx; i <= endIdx; i++) {
                thisSum += intList[i];
            }
            maxSum = (maxSum < thisSum) ? thisSum : maxSum;
        }
    }
    return maxSum;
}

// ==================================================

// O(N^2)
int MaxSubseqSum2(const vector<int> &intList) {
    int N = intList.size();
    if (N == 0) return 0;
    // 课件上的代码，下面这一句变量 maxSum 初始化的时候有问题
    // 如果初始化为0，则当数组元素全为负数的时候，会产生0的答案（错误）
    // 应该初始化为 intList[0]
    int maxSum = intList[0], thisSum = 0;
    for (int i = 0; i < N; i++) {
        thisSum = 0;
        for (int j = i; j < N; j++) {
            thisSum += intList[j];
            maxSum = (maxSum < thisSum) ? thisSum : maxSum;
        }
    }
    return maxSum;
}

// ==================================================

// A help-function of algorithm 3.
int MaxSubseqSum3(const vector<int> &intList, int left, int right) {
    if (left == right) return intList[left];
    int middle = (left + right) / 2;
    int maxLeft = MaxSubseqSum3(intList, left, middle);
    int maxRight = MaxSubseqSum3(intList, middle + 1, right);
    int thisSum = 0, maxMiddle = 0;
    for (int i = middle; i >= left; i--) {
        thisSum += intList[i];
        maxMiddle = (maxMiddle < thisSum) ? thisSum : maxMiddle;
    }
    thisSum = maxMiddle;
    for (int i = middle + 1; i <= right; i++) {
        thisSum += intList[i];
        maxMiddle = (maxMiddle < thisSum) ? thisSum : maxMiddle;
    }
    maxLeft = (maxLeft < maxRight) ? maxRight : maxLeft;
    return (maxLeft < maxMiddle) ? maxMiddle : maxLeft;
}

// O(N x log(N))
int MaxSubseqSum3(const vector<int> &intList) {
    return MaxSubseqSum3(intList, 0, intList.size() - 1);
}

// ==================================================

// Online Process, O(N)（参考LeetCode上面的介绍，课件上面的代码并不完全正确）
int MaxSubseqSum4(const vector<int> &intList) {
    int N = intList.size();
    if (N == 0) return 0;
    // 课件上的代码，下面这一句变量 maxSum 初始化的时候有问题
    // 如果初始化为0，则当数组元素全为负数的时候，会产生0的答案（错误）
    // 应该初始化为 intList[0]
    int thisSum = 0, maxSum = intList[0];
    for (int i = 0; i < N; i++) {
        thisSum += intList[i];
        if (thisSum > maxSum) maxSum = thisSum;
        else if (thisSum < 0) thisSum = 0;
    }
    return maxSum;
}


// ==================== Main ====================
#ifdef HAVE_MAIN

int main(int argc, char const *argv[]) {
    vector<int> intList{4, -3, 5, -2, -1, 2, 6, -2};
    int maxValue = MaxSubseqSum1(intList);
    cout << maxValue << endl;
    maxValue = MaxSubseqSum2(intList);
    cout << maxValue << endl;
    maxValue = MaxSubseqSum3(intList);
    cout << maxValue << endl;
    maxValue = MaxSubseqSum4(intList);
    cout << maxValue << endl;

    intList = {-5};
    maxValue = MaxSubseqSum1(intList);
    cout << maxValue << endl;
    maxValue = MaxSubseqSum2(intList);
    cout << maxValue << endl;
    maxValue = MaxSubseqSum3(intList);
    cout << maxValue << endl;
    maxValue = MaxSubseqSum4(intList);
    cout << maxValue << endl;
    
    return 0;
}

#endif
// ==================== Main ====================