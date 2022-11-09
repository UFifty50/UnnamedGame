#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <vector>
#include <algorithm>


template <typename T>
class Register : private std::vector<T> {
public:
    Register() = default;

    void registerItem(T item) {
        this->push_back(item);
    }

    void unregisterItem(T item) {
        this->erase(std::remove(this->begin(), this->end(), item));
    }

    void unregisterItem(int index) {
        this->erase(this->begin() + index);
    }
    
    using std::vector<T>::begin;
    using std::vector<T>::end;
};

#endif
