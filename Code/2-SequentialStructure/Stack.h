#ifndef __SELF_STACK_H__
#define __SELF_STACK_H__

#include <ostream>

class Stack {
public:
    typedef int element_type;
    typedef struct StackNode {
        element_type item;
        struct StackNode *next;
        StackNode() : item(0), next(nullptr) { ; }
        StackNode(element_type _item) : item(_item), next(nullptr) { ; }
        StackNode(element_type _item, struct StackNode *_next) :
            item(_item), next(_next) { ; }
    }StackNode;

    Stack() : m_len(0), m_stack(new StackNode()) { ; }
    Stack(unsigned int num, element_type value);
    Stack(int *arr, unsigned int num);
    Stack(const Stack &stk);
    ~Stack();

    Stack & operator=(const Stack &stk);

    void push(element_type item);
    element_type top();
    element_type pop();
    bool is_empty() { return m_len == 0; }
    void make_empty();

private:
    unsigned int m_len;
    StackNode *m_stack; // 附加头节点的链表

    void free_stack(StackNode *stk);
    void oops(const char *str);

    friend std::ostream &operator<<(std::ostream &os, const Stack &stk);
};

inline Stack::Stack(unsigned int num, element_type value) : m_len(num), m_stack(new StackNode()) {
    StackNode *node;
    for (int i = 0; i < num; i++) {
        node = new StackNode(value);
        node->next = m_stack->next;
        m_stack->next = node;
    }
}

inline Stack::Stack(int *arr, unsigned int num) : m_len(num), m_stack(new StackNode()) {
    StackNode *node;
    for (int i = 0; i < num; i++) {
        node = new StackNode(arr[i], m_stack->next);
        m_stack->next = node;
    }
}

inline Stack::Stack(const Stack &stk) : m_len(stk.m_len), m_stack(new StackNode()) {
    StackNode *p = stk.m_stack->next, *p2 = m_stack, *node;
    for (int i = 0; i < stk.m_len; i++) {
        node = new StackNode(p->item);
        p2->next = node;
        p2 = p2->next;
        p = p->next;
    }
}

inline Stack::~Stack() {
    free_stack(m_stack);
    m_len = 0;
}

inline Stack & Stack::operator=(const Stack &stk) {
    free_stack(m_stack);
    m_stack = new StackNode();
    StackNode *p = m_stack, *node;
    for (StackNode *p2 = stk.m_stack->next; p2 != nullptr; p2 = p2->next) {
        node = new StackNode(p2->item);
        p->next = node;
        p = p->next;
    }
    m_len = stk.m_len;
    return *this;
}

inline void Stack::free_stack(StackNode *stk) {
    if (stk) {
        StackNode *pre = stk, *curr;
        for (curr = stk->next; curr != nullptr; pre = curr, curr = curr->next) {
            delete pre;
        }
        delete pre;
    }
}

inline void Stack::push(element_type item) {
    StackNode *node = new StackNode(item, m_stack->next);
    m_stack->next = node;
    ++m_len;
}

inline Stack::element_type Stack::top() {
    return m_stack->next->item;
}

inline Stack::element_type Stack::pop() {
    if (m_len == 0) {
        oops("ERROR: Index out of boundary.");
    }
    StackNode *node = m_stack->next;
    element_type ret_value = node->item;
    m_stack->next = node->next;
    delete m_stack;
    --m_len;
    return ret_value;
}

inline void Stack::make_empty() {
    free(m_stack->next);
    m_stack->next = nullptr;
    m_len = 0;
}

#include <iostream>

inline void Stack::oops(const char *str) {
    std::cout << str << std::endl;
}

inline std::ostream &operator<<(std::ostream &os, const Stack &stk) {
    os << "{ size = " << stk.m_len << ", ";
    os << "data = [ ";
    for (Stack::StackNode *node = stk.m_stack->next; node != nullptr; node = node->next) {
        os << node->item << ", ";
    }
    os << "] }";
}

#endif