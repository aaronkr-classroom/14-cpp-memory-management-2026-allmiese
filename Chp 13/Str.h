#progma once
// Str.h
#ifndef GUARD_STR_H
#define GUARD_STR_H

#include <algorithm>
#include <iterator>
#include <cstring>
#include "Vec.h"
#include "Ptr.h" //NEW

using namespace std;

class Str {
friend istream& operator>>(istream&, Str&);
// NEW
friend istream& getline(istream&, Str&); //NEW

public: 
    typedef Vec<char>::size_type size_type;
    typedef char* iterator;
    typedef const char* const_iterator;

    Str() : data(new Vec<char>) { }

    Str(size_type n, char c) : data(new Vec<char>(n, c)) { }

    Str (const char* cp) : data(new Vec<char>) {
        copy ( // std::copy()
            cp, cp + strlen(cp), // std::strlen()
            back_inserter(*data) // std::back_iterator()
        );
    } 

    template<class In> Str(In b, In e) : data(new Vec<char>) {
        copy(b, e, back_inserter(*data));
    }

    size_type size() const { return data->size(); }

    char& operator[](size_type i) { 
        data.make_unique();
        return (*data)[i]; 
    }
    const char& operator[](size_type i) const { return (*data)[i]; }

    Str& operator+=(const Str& s) {
        copy(s.data->begin(), s.data->end(),
            back_inserter(*data));
        return *this;
    }

    iterator begin() { return data->begin(); }
    iterator end() { return data->end(); }

    const_iterator begin() const { return data->begin(); }
    const_iterator end() const { return data->end(); }

    /*
    iterator insert(iterator d, iterator b, iterator e) {
        return data.insert(d, b, e);
    } 
    */
   
private:
    Ptr<Vec<char> > data;
};

ostream& operator<<(ostream&, const Str&);
Str operator+(const Str&, const Str&);

#endif