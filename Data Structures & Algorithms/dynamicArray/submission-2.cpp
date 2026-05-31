#include <utility>
#include <algorithm>

using namespace std;

class DynamicArray {
public:
    std::size_t capacity;
    std::size_t count;
    int* arr;

    DynamicArray(std::size_t capacity) {
        this->capacity = capacity;
        this->arr = new int[capacity];
        this->count = 0;
    }

    ~DynamicArray() {
        delete[] arr;
    }

    DynamicArray(const DynamicArray& other)
        : capacity(other.capacity), count(other.count), arr(new int[other.capacity]) {
        std::copy(other.arr, other.arr + count, arr);
    }

    DynamicArray(DynamicArray&& other) noexcept
        : capacity(other.capacity), count(other.count), arr(std::exchange(other.arr, nullptr)) {
        other.capacity = 0;
        other.count = 0;
    }

    DynamicArray& operator=(DynamicArray other) noexcept
    {
        std::swap(capacity, other.capacity);
        std::swap(count, other.count);
        std::swap(arr, other.arr);
        return *this;
    }

    int get(int i) {
        return arr[i];
    }

    void set(int i, int n) {
        arr[i] = n;
    }

    void pushback(int n) {
        if (count >= capacity) {
            resize();
        }

        arr[count] = n;
        count++;
    }

    int popback() {
        std::size_t i = count - 1;
        int result = arr[i];

        count--;

        return result;
    }

    void resize() {
        capacity *=2;
        int* tempArr = new int[capacity];

        for (std::size_t i = 0; i < count; i++) {
            tempArr[i] = arr[i];
        }

        delete[] arr;
        arr = tempArr;
    }

    int getSize() {
        return count; 
    }

    int getCapacity() {
        return capacity;
    }
};
