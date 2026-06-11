using namespace std;

class Node {
public:
    int value;

    Node(int value) : value(value), nextNode(this), prevNode(this) {}
    Node(int value, Node* nextNode, Node* prevNode) : value(value), nextNode(nextNode), prevNode(prevNode) {}

    Node* next() {
        return this->nextNode;
    }
    
    void setNext(Node* node) {
        this->nextNode = node;
    }

    Node* previous() {
        return this->prevNode;
    }

    void setPrevious(Node* node) {
        this->prevNode = node;
    }

private:
    Node* nextNode;
    Node* prevNode;
};

class Deque {
public:
    std::size_t count;
    Node* head;

    Deque() {
       this->head = nullptr; 
       this->count = 0;
    }

    bool isEmpty() {
        return this->count == 0;
    }

    void append(int value) {
        if (this->isEmpty()) {
            this->head = new Node(value);
            this->count++;
            return;
        }
        
        Node* oldLast = this->head->previous();
        Node* newNode = new Node(value, oldLast->next(), oldLast);
        oldLast->setNext(newNode);
        newNode->next()->setPrevious(newNode);

        this->count++;
    }

    void appendleft(int value) {
        if (this->isEmpty()) {
            this->head = new Node(value);
            this->count++;
            return;
        }

        Node* oldHead = this->head;

        Node* newNode = new Node(value, oldHead, oldHead->previous());
        oldHead->setPrevious(newNode);
        newNode->previous()->setNext(newNode);

        this->head = newNode;
        this->count++;      
    }

    int pop() {
        if (this->isEmpty()) {
            return -1;
        }

        if (this->count == 1) {
            int value = this->head->value;
            this->head = nullptr;
            this->count = 0;
            return value;
        }
        
        Node* last = this->head->previous();
        int value = last->value;

        last->previous()->setNext(last->next());
        last->next()->setPrevious(last->previous());

        delete last;

        this->count--;

        return value;
    }

    int popleft() {
        if (this->isEmpty()) {
            return -1;
        }
        
        if (this->count == 1) {
            int value = this->head->value;
            this->head = nullptr;
            this->count = 0;
            return value;
        }

        Node* curHead = this->head;
        int value = curHead->value;

        curHead->previous()->setNext(curHead->next());
        curHead->next()->setPrevious(curHead->previous());
        this->head = curHead->next();

        delete curHead;

        this->count--;

        return value;
    }
};
