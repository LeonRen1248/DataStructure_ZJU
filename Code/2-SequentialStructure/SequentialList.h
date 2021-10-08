#ifndef __SEQUENTIAL_LIST_H__
#define __SEQUENTIAL_LIST_H__

#include <ostream>

#define MAX_ITEMS_NUM 100

class SequentialList {
public:
    typedef int element_type;
    
    SequentialList();
    SequentialList(int num, element_type value);
    SequentialList(element_type *arr, int n);
    SequentialList(const SequentialList &st);
    ~SequentialList();

    SequentialList & operator=(const SequentialList &st);

    void make_empty() { last = -1; }
    element_type find_kth(int k);
    int find_first(element_type x);
    int find_last(element_type x);
    void insert(int idx, element_type x);
    int get_len() { return last + 1; }

private:
    int last = -1;
    element_type *m_data;

    void oops(const char *str);
    bool element_num_check(int n);

    friend bool operator==(const SequentialList &st1, const SequentialList &st2);
    friend std::ostream & operator<<(std::ostream &os, const SequentialList &st);
};

inline SequentialList::SequentialList() {
    m_data = new element_type[MAX_ITEMS_NUM];
}

inline SequentialList::SequentialList(int num, int value) {
    if (!element_num_check(num)) return;
    // SequentialList();
    m_data = new element_type[MAX_ITEMS_NUM];
    // TODO: 用指针代替下标操作
    // element_type *item = m_data, *item_last = m_data + num;
    for (int i = 0; i < num; i++) {
        m_data[i] = value;
    }
    last = num - 1;
}

inline SequentialList::SequentialList(int *arr, int n) {
    if (!element_num_check(n)) return;
    // SequentialList();
    m_data = new element_type[MAX_ITEMS_NUM];
    for (int i = 0; i < n; i++) {
        m_data[i] = arr[i];
    }
    last = n - 1;
}

inline SequentialList::SequentialList(const SequentialList &st) {
    // SequentialList();
    m_data = new element_type[MAX_ITEMS_NUM];
    for (int i = 0; i <= st.last; i++) {
        m_data[i] = st.m_data[i];
    }
    last = st.last;
}

inline SequentialList::~SequentialList() {
    delete[] m_data;
}

inline SequentialList & SequentialList::operator=(const SequentialList &st) {
    m_data = new element_type[MAX_ITEMS_NUM];
    last = st.last;
    for (int i = 0; i <= last; i++) {
        m_data[i] = st.m_data[i];
    }
    return *this;
}

inline bool operator==(const SequentialList &st1, const SequentialList &st2) {
    if (st1.last != st2.last) return false;
    for (int i = 0; i < st1.last; i++) {
        if (st1.m_data[i] != st2.m_data[i]) return false;
    }
    return true;
}


inline std::ostream & operator<<(std::ostream &os, const SequentialList &st) {
    os << "[ ";
    for (int i = 0; i <= st.last; i++) {
        os << st.m_data[i] << ", ";
    }
    os << "]";
    return os;
}

#include <iostream>

inline void SequentialList::oops(const char *str) {
    std::cout << str << std::endl;
}

inline bool SequentialList::element_num_check(int n) {
    if (n > MAX_ITEMS_NUM) {
        oops("You want to insert too many elements. Try less.");
        return false;
    }
    return true;
}

inline SequentialList::element_type SequentialList::find_kth(int k) {
    if (k > last) {
        oops("Index out of boundary.");
        return 0;
    }
    return m_data[k];
}

inline int SequentialList::find_first(element_type x) {
    for (int i = 0; i <= last; i++) {
        if (x == m_data[i]) return i;
    }
    return -1; // Not found
}

inline int SequentialList::find_last(element_type x) {
    for (int i = last; i >= 0; i--) {
        if (x == m_data[i]) return i;
    }
    return -1; // Not found
}

inline void SequentialList::insert(int idx, element_type x) {
    if (last >= MAX_ITEMS_NUM - 1) {
        oops("This SequentialList is full.");
        return;
    }
    if (idx > last + 1) {
        oops("Index out of boundary.");
        return;
    }
    for (int i = last; i > idx; i--) {
        m_data[i + 1] = m_data[i];
    }
    m_data[idx] = x;
    last++;
}


#endif