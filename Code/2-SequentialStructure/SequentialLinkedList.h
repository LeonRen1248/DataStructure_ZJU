#ifndef __SEQUENTIAL_LINKED_LIST_H__
#define __SEQUENTIAL_LINKED_LIST_H__

#include <ostream>

class SequentialLinkedList {
public:
    using element_type = int;
    using index_type = int;
    using len_type = unsigned int;

    typedef struct SLLNode {
        element_type data;
        struct SLLNode *next;
        SLLNode() : data(0), next(nullptr) { }
        explicit SLLNode(element_type _data) : data(_data), next(nullptr) { }
    }SLLNode;

    SequentialLinkedList() : m_len(0), m_list(new SLLNode(0)) { }
    SequentialLinkedList(len_type num, element_type value);
    SequentialLinkedList(const SequentialLinkedList &sll);
    SequentialLinkedList(element_type *arr, len_type num);
    ~SequentialLinkedList();

    SequentialLinkedList & operator=(const SequentialLinkedList &sll);
    element_type operator[](index_type idx);

    void make_empty();
    // element_type operator[](index_type k);
    index_type find_first(element_type x);
    void insert(index_type idx, element_type x);
    element_type remove(index_type idx);
    len_type get_len() { return m_len; }

private:
    len_type m_len;
    SLLNode *m_list; // 附加头节点的链表结构

    void free_list(SLLNode *sll);
    void oops(const char *str);

    friend std::ostream & operator<<(std::ostream &os, const SequentialLinkedList &sll);
};

inline SequentialLinkedList::SequentialLinkedList(len_type num, element_type value)
        : m_len(num), m_list(new SLLNode(0)) {
    SLLNode *p = m_list, *node;
    for (index_type i = 0; i < num; i++) {
        node = new SLLNode(value);
        p->next = node;
        p = p->next;
    }
}

inline SequentialLinkedList::SequentialLinkedList(const SequentialLinkedList &sll)
        : m_len(sll.m_len), m_list(new SLLNode(0)) {
    SLLNode *add_node = m_list, *node;
    for (SLLNode *p = sll.m_list->next; p != nullptr; p = p->next) {
        node = new SLLNode(p->data);
        add_node->next = node;
        add_node = add_node->next;
    }
}

inline SequentialLinkedList::SequentialLinkedList(element_type *arr, len_type num)
        : m_len(num), m_list(new SLLNode(0)) {
    SLLNode *p = m_list, *node;
    for (index_type i = 0; i < num; i++) {
        node = new SLLNode(arr[i]);
        p->next = node;
        p = p->next;
    }
}

inline SequentialLinkedList::~SequentialLinkedList() {
    free_list(m_list);
}

inline SequentialLinkedList & SequentialLinkedList::operator=(const SequentialLinkedList &sll) {
    if (this == &sll) return *this;
    free_list(m_list->next);
    m_len = sll.m_len;
    SLLNode *add_node = m_list, *node;
    for (SLLNode *p = sll.m_list->next; p != nullptr; p = p->next) {
        node = new SLLNode(p->data);
        add_node->next = node;
        add_node = add_node->next;
    }
    return *this;
}

inline std::ostream & operator<<(std::ostream &os, const SequentialLinkedList &sll) {
    os << "{ length = " << sll.m_len << "; data = [ ";
    for (auto node = sll.m_list->next; node != nullptr; node = node->next) {
        os << node->data << ", ";
    }
    os << "] }";
    return os;
}

inline void SequentialLinkedList::make_empty() {
    SLLNode *node = m_list->next;
    m_list->next = nullptr;
    m_len = 0;
    free_list(node);
}

inline SequentialLinkedList::element_type SequentialLinkedList::operator[](index_type idx) {
    if (idx >= m_len || idx < 0) {
        oops("ERROR: Index out of boundary.");
        return -1;
    }
    SLLNode *p = m_list->next;
    for (index_type i = 0; i < idx; i++) {
        p = p->next;
    }
    return p->data;
}

inline SequentialLinkedList::index_type SequentialLinkedList::find_first(element_type x) {
    int idx = 0;
    for (SLLNode *p = m_list->next; p != nullptr; p = p->next) {
        if (p->data == x) {
            return idx;
        }
        idx++;
    }
    return -1; // Not Found
}

inline void SequentialLinkedList::insert(index_type idx, element_type x) {
    if (idx > m_len || idx < 0) {
        oops("ERROR: Index out of boundary.");
        return;
    }
    SLLNode *p = m_list;
    for (index_type i = 0; i < idx; i++) {
        p = p->next;
    }
    SLLNode *p_next = p->next, *node = new SLLNode(x);
    p->next = node;
    node->next = p_next;
    ++m_len;
}

inline SequentialLinkedList::element_type SequentialLinkedList::remove(index_type idx) {
    if (idx >= m_len || idx < 0) {
        oops("ERROR: Index out of boundary.");
        return -1;
    }
    SLLNode *p = m_list;
    for (index_type i = 0; i < idx; i++) {
        p = p->next;
    }
    SLLNode *removed_node = p->next;
    p->next = p->next->next;
    --m_len;

    element_type ret_value = removed_node->data;
    delete removed_node;
    return ret_value;
}

#include <iostream>

inline void SequentialLinkedList::oops(const char *str) {
    std::cout << str << std::endl;
}

inline void SequentialLinkedList::free_list(SLLNode *sll) {
    if (sll) {
        SLLNode *curr = sll;
        for (SLLNode *after = curr->next; after != nullptr; curr = after, after = after->next) {
            delete curr;
        }
        delete curr;
    }
}

#endif