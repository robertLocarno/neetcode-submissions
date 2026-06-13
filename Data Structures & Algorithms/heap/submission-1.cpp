class MinHeap {
    std::vector<int> items;

public:
    MinHeap() {}

    // Adds value to the heap
    // Need to make sure it's added in order min -> max
    // TODO: O(logn), currently O(n)
    void push(int val) {
        size_t i = 0;
        for (auto item : items) {
            if (val < item) break;
            i++;
        }

        cout << "i: " << i << ", val: " << val << endl;
        items.insert(std::next(items.begin(), i), val); 
    }

    // Removes and returns smallest
    // if empty, return -1
    // O(logn)
    int pop() {
        if (items.empty()) return -1;

        std::vector<int> oldItems = items;
        std::vector<int> newItems;
        newItems.reserve(oldItems.size() - 1);

        int result = oldItems[0];

        std::for_each(std::next(oldItems.begin(), 1), oldItems.end(),
            [&](const auto item) { newItems.push_back(item); });

        items = newItems;

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
    // nums may not be in order
    // O(n)
    void heapify(const std::vector<int>& nums) {
        items.reserve(nums.size());

        for (auto num : nums) {
            push(num);
        }
    }
};