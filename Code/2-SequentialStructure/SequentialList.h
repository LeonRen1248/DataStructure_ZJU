#ifndef __SEQUENTIAL_LIST_H__
#define __SEQUENTIAL_LIST_H__

#include <ostream>
#include <memory.h>
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

    SequentialList & operator=(const SequentialList &sl);
    element_type operator[](index_type idx);

    void make_empty() { last = -1; }
    // element_type find_kth(index_type k); // 用下标运算符重载代替
    index_type find_first(element_type x);
    index_type find_last(element_type x);
    void insert(index_type idx, element_type x);
    element_type remove(index_type idx);
    len_type get_len() { return last + 1; }

private:
    index_type last = -1;
    element_type *m_data;

    void oops(const char *str);
    bool element_num_check(index_type n);
    void init_sl();

    friend bool operator==(const SequentialList &st1, const SequentialList &st2);
    friend std::ostream & operator<<(std::ostream &os, const SequentialList &sl);
};

inline void SequentialList::init_sl() {
    m_data = new element_type[MAX_ITEMS_NUM];
}

inline SequentialList::SequentialList() {
    init_sl();
}

inline SequentialList::SequentialList(len_type num, element_type value) {
    if (!element_num_check(num)) return;
    init_sl();
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

inline SequentialList & SequentialList::operator=(const SequentialList &sl) {
    if (this == &sl) return *this;
    delete m_data;
    m_data = new element_type[MAX_ITEMS_NUM];
    memcpy(m_data, sl.m_data, (sl.last + 1) * sizeof(element_type));
    // for (index_type i = 0; i <= sl.last; i++) {
    //     m_data[i] = sl.m_data[i];
    // }
    last = sl.last;
    return *this;
}

inline bool operator==(const SequentialList &st1, const SequentialList &st2) {
    if (st1.last != st2.last) return false;
    for (SequentialList::index_type i = 0; i < st1.last; i++) {
        if (st1.m_data[i] != st2.m_data[i]) return false;
    }
    return true;
}

inline SequentialList::element_type SequentialList::operator[](index_type idx) {
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

inline void SequentialList::oops(const char *str) {
    std::cout << str << std::endl;
}

inline bool SequentialList::element_num_check(index_type n) {
    if (n > MAX_ITEMS_NUM) {
        oops("You want to insert too many elements. Try less.");
        return false;
    }
    return true;
}

inline SequentialList::index_type SequentialList::find_first(element_type x) {
    for (index_type i = 0; i <= last; i++) {
        if (x == m_data[i]) return i;
    }
    return -1; // Not found
}

inline SequentialList::index_type SequentialList::find_last(element_type x) {
    for (index_type i = last; i >= 0; i--) {
        if (x == m_data[i]) return i;
    }
    return -1; // Not found
}

inline void SequentialList::insert(index_type idx, element_type x) {
    if (last >= MAX_ITEMS_NUM - 1) {
        oops("This SequentialList is full.");
        return;
    }
    if (idx > last + 1 || idx < 0) {
        oops("Index out of boundary.");
        return;
    }
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