#include <vector>

using namespace std;

class LLNode {
public:
    LLNode* nextPtr;
    int value;

    LLNode(int value) {
        this->nextPtr = nullptr;
        this->value = value;
    }

    void setNext(LLNode* nextPtr) {
        this->nextPtr = nextPtr;
    }
};

class LinkedList {
public:
    std::size_t size = 0;
    LLNode* firstNodePtr = nullptr;
    
    LinkedList() = default;

    int get(int index) {
        if (index >= size) {
            return -1;
        }

        LLNode* current = firstNodePtr;
        for (std::size_t i = 0; i < index; i++) {
            current = current->nextPtr;
        }

        return current->value;
    }

    void insertHead(int val) {
       LLNode *node = new LLNode(val);
       node->setNext(this->firstNodePtr); 

       firstNodePtr = node;

       size++;
    }
    
    void insertTail(int val) {
        LLNode *node = new LLNode(val);

        if (size == 0) {
            firstNodePtr = node;
            size++;
            return;
        }

        LLNode *lastNode = firstNodePtr;
        while (lastNode->nextPtr != nullptr) {
            lastNode = lastNode->nextPtr;
        }

        lastNode->setNext(node);
        size++;
    }

    bool remove(int index) {
        if (index < 0 || index >= size) {
            return false;
        }

        if (index == 0) {
            LLNode* victim = firstNodePtr;
            firstNodePtr = firstNodePtr->nextPtr;
            delete victim;
            size--;
            return true;
        }

        LLNode *gapStart = firstNodePtr;
        for (std::size_t i = 0; i < index - 1; i++) {
            gapStart = gapStart->nextPtr;
        }
        
        LLNode* gapEndPtr = (gapStart && gapStart->nextPtr)
            ? gapStart->nextPtr->nextPtr
            : nullptr;

        LLNode* victim = gapStart->nextPtr;
        gapStart->setNext(gapEndPtr);
        delete victim;
        size--;

        return true;
    }

    vector<int> getValues() {
        vector<int> result = {};

        LLNode* current = firstNodePtr; 
        while (current != nullptr) {
            result.push_back(current->value);
            current = current->nextPtr;
        }

        return result;
    }
};
