class TreeNode {
    int key;
    int value;
    std::unique_ptr<TreeNode> leftNode;
    std::unique_ptr<TreeNode> rightNode;

public:
    TreeNode(int key, int value) : key(key), value(value) {
        this->leftNode = nullptr;
        this->rightNode = nullptr;
    }

    void insert(std::unique_ptr<TreeNode> candidate) {
        if (candidate->key == this-> key) {
            this->value = candidate->value;
        } else if (candidate->key < this->key) {
            if (this->leftNode == nullptr) {
                this->leftNode = std::move(candidate);
                return;
            }

            this->leftNode->insert(std::move(candidate));
        } else {
            if (this->rightNode == nullptr) {
                this->rightNode = std::move(candidate);
                return;
            }

            this->rightNode->insert(std::move(candidate));
        }

        // Should never happen
    }

    int get(int key) {
        if (key == this->key) {
            return this->value;
        }

        if (key < this->key) {
            if (this->leftNode == nullptr) {
                return -1;
            }

            return this->leftNode->get(key);
        }

        // must be greater
        if (this->rightNode == nullptr) {
            return -1;
        }

        return this->rightNode->get(key);
    }

    int getMin() {
        if (this->leftNode == nullptr) {
            return this->value;
        }

        return this->leftNode->getMin();
    }

    int getMax() {
        if (this->rightNode == nullptr) {
            return this->value;
        }

        return this->rightNode->getMax();
    }

    static std::unique_ptr<TreeNode> remove(std::unique_ptr<TreeNode> node, int key) {
        if (!node) return nullptr;

        if (node->key == key) {
            std::unique_ptr<TreeNode> promoted;

            if (node->leftNode != nullptr) {
                promoted = std::move(node->leftNode);

                if (node->rightNode != nullptr) {
                    promoted->insert(std::move(node->rightNode));
                }

                return promoted;
            } else if (node->rightNode != nullptr) {
                return std::move(node->rightNode);
            } else {
                return nullptr;
            }
        } 

        if (key < node->key) {
            if (node->leftNode == nullptr) {
                return std::move(node);
            }

            node->leftNode = remove(std::move(node->leftNode), key);
            return std::move(node);
        }

        if (node->rightNode == nullptr) {
            return std::move(node);
        }

        node->rightNode = remove(std::move(node->rightNode), key);
        return std::move(node);
    }

    std::vector<int> getInorderKeys() {
        std::vector<int> keys = { this->key };

        if (this->leftNode != nullptr) {
            std::vector<int> leftKeys = this->leftNode->getInorderKeys();

            keys.insert(keys.begin(), leftKeys.begin(), leftKeys.end());
        }

        if (this->rightNode != nullptr) {
            std::vector<int> rightKeys = this->rightNode->getInorderKeys();

            keys.insert(keys.end(), rightKeys.begin(), rightKeys.end());
        }

        return keys;
    }
};

class TreeMap {
    std::unique_ptr<TreeNode> rootNode;

public:
    TreeMap() {
       this->rootNode = nullptr; 
    }

    void insert(int key, int val) {
        auto candidate = std::make_unique<TreeNode>(key, val);

        if (this->rootNode == nullptr) {
            this->rootNode = std::move(candidate);
            return;
        }

        this->rootNode->insert(std::move(candidate)); 
    }

    int get(int key) {
        if (this->rootNode == nullptr) {
            return -1;
        }

        return this->rootNode->get(key);
    }

    int getMin() {
        if (this->rootNode == nullptr) {
            return -1;
        }

        return this->rootNode->getMin();
    }

    int getMax() {
        if (this->rootNode == nullptr) {
            return -1;
        }

        return this->rootNode->getMax();
    }

    void remove(int key) {
        if (this->rootNode == nullptr) {
            return;
        }

        this->rootNode = TreeNode::remove(std::move(this->rootNode), key);
    }

    std::vector<int> getInorderKeys() {
        if (this->rootNode == nullptr) {
            return {};
        }

        return this->rootNode->getInorderKeys();
    }
};
