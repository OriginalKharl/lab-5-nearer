#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <utility>
class DynamicArray {
private:
    int*   data_;
    std::size_t size_;
    std::size_t capacity_;
     void resize(std::size_t newCapacity) {
        if (newCapacity <= capacity_) return;
        int* newBuffer = new int[newCapacity]();
         for (std::size_t i = 0; i < size_; ++i) {
            newBuffer[i] = data_[i];
        }
         delete[] data_;
        data_     = newBuffer;
        capacity_ = newCapacity;
     }

     // 1st commit, DynamicArray start declare
