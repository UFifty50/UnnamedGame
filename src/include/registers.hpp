#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <vector>
#include <string>
#include <any>

template <typename T>
class Register : private std::vector<T> {
public:
    Register() = default;

    void registerItem(T const& item);
    void unregisterItem(T const& item);
    void unregisterItem(int index);
    
    using std::vector<T>::begin;
    using std::vector<T>::end;
};

#endif
