using namespace std;

class DynamicArray {
public:
    std::size_t capacity;
    std::size_t count;
    int* arr;

    DynamicArray(int capacity) {
        this->capacity = capacity;
        this->arr = new int[capacity];
        this->count = 0;
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

        arr[i] = NULL;
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
