// Directed vertex with directed edges to other nodes
class Node {
    int source;
    std::vector<Node*> destinations;

public:
    Node(int source) : source(source) {}

    int getSource() {
        return source;
    }

    std::vector<Node*> getDestinations() {
        return destinations;
    }

    void addDestination(Node* destination) {
        for (auto candidate : destinations) {
            if (candidate == destination) return;
        }

        destinations.push_back(destination);
    }

    void setDestinations(std::vector<Node*> destinations) {
        this->destinations = destinations;
    }

    bool removeDestination(Node* destination) {
        for (auto i = destinations.begin(); i < destinations.end(); i = std::next(i, 1)) {
            Node* candidate = *i;

            if (destination == candidate) {
                destinations.erase(i);
                return true;
            }
        }

        return false;
    }

    bool hasPath(Node* destination) {
        std::unordered_set<Node*> visited;

        return hasPath(destination, &visited);
    }

    bool hasPath(Node* destination, std::unordered_set<Node*>* visited) {
        if (visited->contains(this)) return false;
    
        for (auto candidate : destinations) {
            if (destination == candidate) return true;
        }

        visited->insert(this);
        for (auto candidate : destinations) {
            if (candidate->hasPath(destination, visited)) return true;
        }

        return false;
    }
};

class Graph {
    std::unordered_map<int, Node*> nodeMap;

public:
    Graph() {}

    ~Graph() {
        for (auto idNodePair : nodeMap) {
            delete std::get<Node*>(idNodePair);
        }
    }

    Graph(const Graph& other) {
        copyNodes(other.nodeMap);
    }

    Graph& operator=(const Graph other) {
        copyNodes(other.nodeMap);

        return *this;
    }

    void addEdge(int src, int dst) {
        Node* srcNode = findNode(src);
        Node* dstNode = findNode(dst);

        if (!srcNode) {
            srcNode = new Node(src);
            nodeMap[src] = srcNode;
        }

        if (!dstNode) {
            dstNode = new Node(dst);
            nodeMap[dst] = dstNode;
        }

        srcNode->addDestination(dstNode);
    }

    bool removeEdge(int src, int dst) {
        Node* srcNode = findNode(src);
        Node* dstNode = findNode(dst);

        if (!srcNode || !dstNode) return false;

        return srcNode->removeDestination(dstNode);
    }

    bool hasPath(int src, int dst) {
        Node* srcNode = findNode(src);
        Node* dstNode = findNode(dst);

        if (!srcNode || !dstNode) return false;
        
        return srcNode->hasPath(dstNode);
    }

private:
    Node* findNode(int key) {
        auto iterator = nodeMap.find(key);

        if (iterator == nodeMap.end()) return nullptr;

        return std::get<Node*>(*iterator);
    }

    void copyNodes(std::unordered_map<int, Node*> otherNodes) {
        nodeMap.clear();

        for (auto idNodePair : otherNodes) {
            int source = std::get<Node*>(idNodePair)->getSource();
            nodeMap[source] = new Node(source);
        }

        for (auto idNodePair : otherNodes) {
            Node* node = std::get<Node*>(idNodePair);

            for (auto destination : node->getDestinations()) {
                addEdge(node->getSource(), destination->getSource());
            }
        }
    }
};
