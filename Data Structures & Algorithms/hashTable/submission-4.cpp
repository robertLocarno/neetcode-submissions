class HashNode {
public:
    int key;
    int value;
    std::unique_ptr<HashNode> child;

    HashNode(int key, int value) : key(key), value(value) {}

    // Returns true if a new node was appended, else false
    bool upsert(std::unique_ptr<HashNode> orphan) {
        if (orphan->child) {
            // For now, this is handled in HashTable#insert and each node is inserted separately
            std::cout << "Upserting a node with a child is not allowed" << std::endl;
            return false;
        }

        if (key == orphan->key) {
            value = orphan->value;
            return false;
        }

        if (!child) {
            child = std::move(orphan);
            return true;
        }

        return child->upsert(std::move(orphan));
    }

    int get(int searchKey) const {
        if (searchKey == key) {
            return value;
        }

        if (child) {
            return child->get(searchKey);
        }

        return -1;
    }
};

class HashTable {
    int capacity;
    int size;
    std::vector<std::unique_ptr<HashNode>> buckets;

public:
    HashTable(int capacity) : capacity(capacity) {
        size = 0;
        buckets.resize(capacity);
    }

    void insert(int key, int value) {
        std::unique_ptr<HashNode> node = std::make_unique<HashNode>(key, value);
        insert(std::move(node));
    }

    void insert(std::unique_ptr<HashNode> node) {
        if (node->child) {
            insert(std::move(node->child));
        }

        size_t bucketIndex = hash(node->key);
        if (!buckets[bucketIndex]) {
            buckets[bucketIndex] = std::move(node);
            size++;

            if (shouldResize()) resize();

            return;
        }
        
        if (buckets[bucketIndex]->upsert(std::move(node))) {
            size++;
        }

        if (shouldResize()) resize();
    }

    int get(int key) {
        size_t bucketIndex = hash(key);

        if (!buckets[bucketIndex]) {
            return -1;
        }

        return buckets[bucketIndex]->get(key);
    }

    bool remove(int key) {
        size_t bucketIndex = hash(key);

        if (!buckets[bucketIndex]) {
            return false;
        }        

        HashNode* candidate = buckets[bucketIndex].get();
        if (candidate->key == key) {
            buckets[bucketIndex] = std::move(candidate->child);
            size--;
            return true;
        }
        while (candidate->child) {
            if (candidate->child->key == key) {
                candidate->child = std::move(candidate->child->child);
                size--;
                return true;
            }

            candidate = candidate->child.get();
        };

        return false;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    void resize() {
        capacity *= 2;
        size = 0;

        std::vector<std::unique_ptr<HashNode>> oldBuckets = std::move(buckets);
        std::vector<std::unique_ptr<HashNode>> newBuckets(capacity);
        this->buckets = std::move(newBuckets);
        
        for (size_t i = 0; i < oldBuckets.capacity(); i++) {
            if (oldBuckets[i]) insert(std::move(oldBuckets[i]));
        }
    }

private:
    // Simple hash function to 'evenly' distribute keys
    size_t hash(int key) const {
        int h = key % capacity;

        return h < 0 ? h + capacity : h;
    }

    float loadFactor() const {
        return (float) size / capacity;
    }

    bool shouldResize() const {
        return loadFactor() >= 0.4;
    }
};
