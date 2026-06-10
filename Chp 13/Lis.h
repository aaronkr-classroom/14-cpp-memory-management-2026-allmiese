#progma once
// Lis.h
#ifndef GUARD_LIS_H
#define GUARD_LIS_H

#include <memory>

template<class T> class Node {
public:
    T value; // 15, "Aaron", $15.00
    Node<T>* next;
    Node<T>* prev;

    Node() : value(0), next(0), prev(0) { }
    Node(T t) : value(t), next(0), prev(0) { }
};

template<class T> class NodeItr {
public:
    NodeItr& operator++();
    NodeItr& operator--();
    NodeItr operator++(int);
    NodeItr operator--(int);
    T& operator*() const { return node->value; }
    bool operator!=(const NodeItr rhs) const {
        return node != rhs.node;
    }

    NodeItr(Node<T>* n) : node(n) { }

private:
    Node<T>* node;
};

template<class T> NodeItr<T>& NodeItr<T>::operator++() {
    node = node->next;
    return *this;
}

template<class T> NodeItr<T>& NodeItr<T>::operator--() {
    node = node->prev;
    return *this;
}

template<class T> NodeItr<T>& NodeItr<T>::operator++(int) {
    NodeItr<T> ret(node);
    node = node->next;
    return *this;
}

template<class T> NodeItr<T>& NodeItr<T>::operator--(int) {
    NodeItr<T> ret(node);
    node = node->prev;
    return *this;
}

template<class T> class Lis {
public:
    typedef NodeItr<T> iterator;
    typedef const NodeItr<T> const_iterator;
    typedef size_t size_type;

    Lis() : b(0), e(0), s(0) { }
    explicit Lis(size_type n, const T& t = T()) { create(n, t); }
    Lis (const Lis& v) {create(v.begin(), v.end()); }
    Lis& operator=(const Lis&);
    ~Lis() { uncreate(); }

    void push_back(const T& t);
    size_type size() const { return s; }

    iterator begin() { return b; }
    const_iterator begin() const { return b; }

    iterator end() { return e; }
    const_iterator end() const { return e; }

    void clear() { uncreate(); }
    bool empty() const { return s == 0; }

private:
    Node<T>* b;
    Node<T>* e;
    size_type s;

    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();
};

template<class T>
void Lis<T>::push_back(const T& t) {
    Node<T>* node = new Node<T>(t);

    if (s == 0)
        b = e = node;
    else {
        e->next = node;
        node->prev = e;
        e = node;
    }
    s++;
}

template<class T>
void Lis<T>::create(size_type s, const T& t) {
    for (size_type i = 0; i < s; i++)
        push_back(t);
}

template<class T>
void Lis<T>::create(iterator b, iterator e) {
    while (b != e)
    push_back(*b++); 
}

template<class T>
void Lis<T>::uncreate() {
    Node<T>* node = e;

    while (node != b) {
        Node<T>* node_delete = node;
        node = node->prev;
        delete node_delete;
    }

    b = e = 0;
    s = 0;
}

#endif