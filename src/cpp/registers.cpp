#include <vector>
#include <string>
#include <any>

#include "registers.hpp"


template <typename T>
void Register<T>::registerItem(T const& item) {
    this->push_back(item);
}

template <typename T>
void Register<T>::unregisterItem(T const& item) {
    this->erase(std::remove(this->begin(), this->end(), item));
}

template <typename T>
void Register<T>::unregisterItem(int index) {
    this->erase(this->begin() + index);
}
