class MinHeap {
    // Stores heap as binary tree
    // Rules:
    //   Parent: (i - 1) / 2
    //   L-Child: (2i) + 1
    //   R-Child: (2i) + 2
    //   Parent must be <= children
    std::vector<int> items;

public:
    MinHeap() {}

    // Adds value to the heap
    // Push to end, then swap with parent if parent > child.
    // O(logn)
    void push(int val) {
        items.push_back(val);

        size_t candidateIndex = items.size() - 1;
        size_t parentIndex = (candidateIndex - 1) / 2;
        while (candidateIndex > 0 && items[candidateIndex] < items[parentIndex]) {
            std::swap(items[candidateIndex], items[parentIndex]);

            candidateIndex = parentIndex;
            parentIndex = (candidateIndex - 1) / 2;
        }
    }

    // Removes and returns smallest
    // Promote last element to first, sift down.
    // if empty, return -1
    // O(logn)
    int pop() {
        if (items.empty()) return -1;

        int result = items[0];

        items[0] = items[items.size() - 1];
        items.pop_back();

        siftDown(0);

        return result;
    }

    // Returns smallest without removing
    // if empty, return -1
    // O(1)
    int top() const {
        if (items.empty()) return -1;

        return items[0];
    }

    // Assign to items (clone) 
    // Need to sort tree. Sift down from bottom up
    // O(n)
    void heapify(const std::vector<int>& nums) {
        items = nums;

        for (size_t i = items.size() / 2; i-- > 0; )
            siftDown(i);
    }

private:
    void siftDown(size_t i) {
        size_t size = items.size();
        while (true) {
            size_t c1i = (i * 2) + 1;
            size_t c2i = c1i + 1;
            size_t min = i;

            if (c1i < size && items[c1i] < items[min]) min = c1i;
            if (c2i < size && items[c2i] < items[min]) min = c2i;
            if (min == i) break;

            std::swap(items[i], items[min]);
            i = min;
        }
    }
};