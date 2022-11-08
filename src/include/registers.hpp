#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <vector>
#include <string>
#include <any>

template <typename T>
class Register : public std::vector<T> {
public:
    Register() = default;

    void registerItem(T const& item);

    void unregisterItem(T const& item);

    void unregisterItem(int index);
};

#endif
