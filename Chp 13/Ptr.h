// Ptr.h
#ifndef GUARD_Ptr.h
#define GUARD_Ptr.h

#include <cstddef>
#include <stdexcept>
#include "Vec.h"

using namespace std;

template <class T> class Ptr {
public: 
    void make_unique() {
        if (*refptr != 1) {
            --*refptr;
            refptr = new size_t(1);
            p = p ? clone() : 0;
        }
    }

    Ptr() : p(0), refptr(new size_t(1)) { }
    Ptr(T* t) : p(t), refptr(new size_t(1)) { }
    Ptr(const Ptr& h) : p(h.p), refptr(h.refptr) {
        ++*refptr;
    }

    Ptr& operator=(const Ptr&);
    ~Ptr();

    operator bool() const { return p; }
    T& operator*() const {
        if (p) return *p;
        throw runtime_error("unbound Ptr!");
    }
    T& operator->() const {
        if (p) return p;
        throw runtime_error("unbound Ptr!");
    }
private:
    T* p;
    size_t* refptr;
};

template <>
Vec<char>* clone(const Vec<char>* vp){
    return new Vec<char>(*vp);
}

template <class T> T* clone(const T* tp) {
    return tp->clone();
}

template <class T> 
Ptr<T>& Ptr<T>::operator=(const Ptr& rhs) {
    ++*rhs.refptr;

    if (--*refptr == 0) {
        delete refptr;
        delete p;
    }

    refptr = rhs.refptr;
    p = rhs.p;

    return *this;
}

template <class T> 
Ptr<T>::~Ptr() {
    if (--*refptr == 0) {
        delete refptr;
        delete p;
    }
}

#endif