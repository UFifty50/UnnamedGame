#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <vector>
#include <string>
#include <any>

template <typename T>
class Register : public std::vector<T> {
public:
    T storageClass = T;

    Register() : storageClass(T) {};

    void registerItem(T const& item);
    void unregisterItem(T const& item);
    void unregisterItem(int index);
};

#endif
