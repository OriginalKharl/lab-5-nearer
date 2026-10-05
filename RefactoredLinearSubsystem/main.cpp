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

public:

    explicit DynamicArray(std::size_t initialCapacity = 5)
        : data_(new int[initialCapacity]()),
          size_(0),
          capacity_(initialCapacity) {}

          // Constructor segm

      ~DynamicArray() {
        delete[] data_;
        data_ = nullptr;
    }

    // Destructor segm
    // 2nd commit

   DynamicArray(const DynamicArray&)            = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;
    DynamicArray(DynamicArray&& other) noexcept
        : data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_) {
        other.data_     = nullptr;
        other.size_     = 0;
        other.capacity_ = 0;
    }
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_           = other.data_;
            size_           = other.size_;
            capacity_       = other.capacity_;
            other.data_     = nullptr;
            other.size_     = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

   // Rule of Five, 3rd commit

    void addItem(int value) {
        if (size_ >= capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_] = value;
        ++size_;
        std::cout << "Added item: " << value << '\n';
    }

    // addItem() segm

    bool removeItemAt(std::size_t index) {
        if (index >= size_) {
            std::cout << "Invalid index! (out of bounds)\n";
            return false;
        }
        // Single-pass left shift — O(n) worst case
        for (std::size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
        std::cout << "Item removed from index " << index << '\n';
        return true;
    }

    // removeItemAt() segm
    // 4th commit

    int findItem(int target) const {
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i] == target) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // findItem() segm

    void printAll() const {
        std::cout << "Current List Contents: ";
        for (std::size_t i = 0; i < size_; ++i) {
            std::cout << data_[i] << ' ';
        }
        std::cout << '\n';
    }

    // printAll() segm
    // 5th commit

    std::size_t getSize()     const noexcept { return size_; }
    std::size_t getCapacity() const noexcept { return capacity_; }
    bool        isEmpty()     const noexcept { return size_ == 0; }

    int& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("DynamicArray::at");
        return data_[index];
    }
    const int& at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("DynamicArray::at");
        return data_[index];
    }
};

// Accessors
// 6th commit

void processMatrix(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix.front().empty()) {
        std::cout << "Empty matrix — nothing to transpose.\n";
        return;
    }
    const std::size_t rows = matrix.size();
    const std::size_t cols = matrix.front().size();

    std::vector<std::vector<int>> transposed(
        cols, std::vector<int>(rows, 0));
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    std::cout << "Transposed Matrix:\n";
    for (std::size_t i = 0; i < cols; ++i) {
        for (std::size_t j = 0; j < rows; ++j) {
            std::cout << transposed[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

// processMatrix() void main
// 7th commit

// MAIN / Driver demonstration

int main() {
    std::cout << "--- STARTING REFACTORED SUBSYSTEM ---\n";
   {
        DynamicArray arr(5);

        arr.addItem(10);
        arr.addItem(20);
        arr.addItem(30);
        arr.addItem(40);
        arr.addItem(50);
        // Normal / default inserts

        arr.addItem(60);
        // FIX #1 safe resize with no leak

         arr.printAll();
         // FIX #4 no garbage read

        int idx = arr.findItem(30);
        std::cout << "Found 30 at index: " << idx << '\n';
        // FIX #8 single-pass search

        arr.removeItemAt(2);
        arr.printAll();
        // FIX #7 single-pass shift deletion

        arr.removeItemAt(99);
        arr.printAll();
        // FIX #2 out-of-bounds rejected

        arr.removeItemAt(arr.getSize() - 1);
        arr.printAll();
        arr.removeItemAt(static_cast<std::size_t>(999999));
        arr.printAll();
    }
      {
      DynamicArray emptyArr(3);
        emptyArr.printAll();
    }

    // 8th commit
