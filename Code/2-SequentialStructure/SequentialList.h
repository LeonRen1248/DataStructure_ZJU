#ifndef __SEQUENTIAL_LIST_H__
#define __SEQUENTIAL_LIST_H__

#include <ostream>
// 这个头文件没用到，我之前说错了，memcpy定义在<cstring>中
// #include <memory.h>
#include <cstring>

#define MAX_ITEMS_NUM 1000

// template <typename T>
class SequentialList {
public:
    using element_type = int; // typedef int element_type;
    using index_type = int;
    using len_type = unsigned int;
    
    SequentialList();
    SequentialList(len_type num, element_type value);
    SequentialList(element_type *arr, len_type n);
    SequentialList(const SequentialList &sl);
    ~SequentialList();

    SequentialList & operator=(SequentialList sl);
    // element_type operator[](index_type idx) const;

    /**
     * 对于operator[]的设计应该对const的和非const的分开设计
     * const的operator[]返回的值也应该是const类型，否则这个const也没意义了
     * 后文对应要改
     * 
     * operator[]也应该返回引用类型，否则就是返回的一个副本，无法完成list[0] = 1这样的赋值操作
     */
    element_type & operator[](index_type idx) {
        // 在Effective C++中学到的写法，避免了重复，后面只需要详细定义对于const的operator[]就可以
        return const_cast<element_type&>(static_cast<const SequentialList *>(this)->operator[](idx));
    }
    const element_type & operator[](index_type idx) const;

    void make_empty() { last = -1; }
    // element_type find_kth(index_type k); // 用下标运算符重载代替
    index_type find_first(element_type x) const;
    index_type find_last(element_type x) const;
    void insert(index_type idx, element_type x);
    element_type remove(index_type idx);
    len_type get_len() const { return last + 1; }

private:
    index_type last = -1;
    element_type *m_data;

    void oops(const char *str) const;
    bool element_num_check(index_type n) const;
    void init_sl();
    /** 
     * 这是没有问题，我注释一下我的疑惑和找到的解答
     * 本来我以为init_sl()不是const函数，那么创建const对象时是不是就没法调用了，
     * 然后我去实验了一下，发现能调用，const对象的构造函数也是能够调用non-const成员函数的，
     * 然后在C++ Primer P235查到了这样一句话：当我们创建类的一个const对象时，直到构造函数完成初始化过程，对象才能真正取得其”常量“属性。
     * 所以const对象的构造函数也能够调用non-const成员函数。
     */

    void swap(SequentialList &rhs) {
        using std::swap;
        swap(m_data, rhs.m_data);
        swap(last, rhs.last);
    }

    friend bool operator==(const SequentialList &st1, const SequentialList &st2);
    friend std::ostream & operator<<(std::ostream &os, const SequentialList &sl);
};

inline void SequentialList::init_sl() {
    m_data = new element_type[MAX_ITEMS_NUM];
}

inline SequentialList::SequentialList() {
    init_sl();
}

/**
 * 这里如果大小检查不符合要求，只是输出了信息，但是仍然会执行结束，就是也创建了对象。
 * 这样会产生几个问题：
 * 1. 如果在用户程序里（即调用这个类的程序），创建的对象不符合要求，
 * 但是创建对象之后的代码仍然会继续执行，就会产生问题
 * 这里我能想到的解决方法是：
 *   1）如果不符合要求，抛出异常，在用户程序里检测这个异常
 *   2）用assert或者static_assert，不符合要求就提示退出
 *   3）不管对象大小的检测，让用户程序自己保证
 * 
 * 2. 大小检测不合格后，对象仍然创造了，但是m_data成员未初始化，其值是内置类型，所以值是未定义的
 * 这样当析构函数被调用的话，delete的就是一个乱指针。
 * 我能想到的解决方法：
 *   如果未初始成功，将其设置为nullptr，析构的时候判断一下。
 */
inline SequentialList::SequentialList(len_type num, element_type value) {
    if (!element_num_check(num)) return;
    init_sl();
    // 用memset()代替循环赋值，https://en.cppreference.com/w/cpp/string/byte/memset
    for (index_type i = 0; i < num; i++) {
        m_data[i] = value;
    }
    last = num - 1;
}

inline SequentialList::SequentialList(element_type *arr, len_type n) {
    if (!element_num_check(n)) return;
    init_sl();
    memcpy(m_data, arr, n * sizeof(element_type));
    // for (index_type i = 0; i < n; i++) {
    //     m_data[i] = arr[i];
    // }
    last = n - 1;
}

inline SequentialList::SequentialList(const SequentialList &sl) {
    init_sl();
    memcpy(m_data, sl.m_data, (sl.last + 1) * sizeof(element_type));
    // for (index_type i = 0; i <= sl.last; i++) {
    //     m_data[i] = sl.m_data[i];
    // }
    last = sl.last;
}

inline SequentialList::~SequentialList() {
    delete[] m_data;
}

// inline SequentialList & SequentialList::operator=(const SequentialList &sl) {
//     if (this == &sl) return *this;
//     delete m_data;
//     m_data = new element_type[MAX_ITEMS_NUM];
//     memcpy(m_data, sl.m_data, (sl.last + 1) * sizeof(element_type));
//     // for (index_type i = 0; i <= sl.last; i++) {
//     //     m_data[i] = sl.m_data[i];
//     // }
//     last = sl.last;
//     return *this;
// }

/**
 * 拷贝赋值有一种很优秀的写法
 * 参数不用引用，直接赋值一份，然后与*this进行swap
 * 这样自然而然就解决了自赋值的情况
 * 同时也简化了这个函数的实现，也方便维护，例如如果需要加一些成员变量，这个函数都不需要再修改
 */
inline SequentialList & SequentialList::operator=(SequentialList sl) {
    swap(sl);
    return *this;
}

inline bool operator==(const SequentialList &st1, const SequentialList &st2) {
    if (st1.last != st2.last) return false;
    // 循环终止条件是不是应该有等号
    for (SequentialList::index_type i = 0; i < st1.last; i++) {
        if (st1.m_data[i] != st2.m_data[i]) return false;
    }
    return true;
}

/**
 * 这个函数对于下标错误这个问题也需要重新解决，这里的方法是输出提示信息，然后返回-1，
 * 但是element_type本身就是有符号的，-1本来也有有可能是一个合法的值，
 * 这个类的用户无法判断是拿到了合法的值还说一个下标错误
 * 可用的解决方法与构造函数那里类似
 */
inline SequentialList::element_type SequentialList::operator[](index_type idx) const {
    if (idx > last || idx < 0) {
        oops("Index out of boundary.");
        return -1;
    }
    return m_data[idx];
}

inline std::ostream & operator<<(std::ostream &os, const SequentialList &sl) {
    os << "[ ";
    for (SequentialList::index_type i = 0; i <= sl.last; i++) {
        os << sl.m_data[i] << ", ";
    }
    os << "]";
    return os;
}

#include <iostream>

inline void SequentialList::oops(const char *str) const {
    std::cout << str << std::endl;
}

inline bool SequentialList::element_num_check(index_type n) const {
    if (n > MAX_ITEMS_NUM) {
        oops("You want to insert too many elements. Try less.");
        return false;
    }
    return true;
}

inline SequentialList::index_type SequentialList::find_first(element_type x) const {
    for (index_type i = 0; i <= last; i++) {
        if (x == m_data[i]) return i;
    }
    return -1; // Not found
}

inline SequentialList::index_type SequentialList::find_last(element_type x) const {
    for (index_type i = last; i >= 0; i--) {
        if (x == m_data[i]) return i;
    }
    return -1; // Not found
}

inline void SequentialList::insert(index_type idx, element_type x) {
    // 我觉得这里先检测插入坐标是否合理，再判断目前类是否满了更合理一些
    if (last >= MAX_ITEMS_NUM - 1) {
        oops("This SequentialList is full.");
        return;
    }
    if (idx > last + 1 || idx < 0) {
        oops("Index out of boundary.");
        return;
    }
    // 我觉得这个循环判定条件还应该有等号
    for (index_type i = last; i > idx; i--) {
        m_data[i + 1] = m_data[i];
    }
    m_data[idx] = x;
    ++last;
}

inline SequentialList::element_type SequentialList::remove(index_type idx) {
    if (idx > last || idx < 0) {
        oops("Index out of boundary.");
        return 0;
    }
    element_type ret_value = m_data[idx];
    for (index_type i = idx; i < last; i++) {
        m_data[i] = m_data[i + 1];
    }
    --last;
    return ret_value;
}


#endif