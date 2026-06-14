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
        
        return hasPath(destination, visited);
    }

    bool hasPath(Node* destination, std::unordered_set<Node*> visited) {
        if (visited.contains(this)) return false;
    
        for (auto candidate : destinations) {
            if (destination == candidate) return true;
        }

        visited.insert(this);
        for (auto candidate : destinations) {
            if (candidate->hasPath(destination, visited)) return true;
        }

        return false;
    }
};

class Graph {
    std::vector<Node*> nodes;

public:
    Graph() {}

    ~Graph() {
        for (Node* node : nodes) {
            delete node;
        }
    }

    Graph(const Graph& other) {
        nodes.clear();

        for (auto node : other.nodes) {
            nodes.push_back(new Node(node->getSource()));
        }

        for (auto node : other.nodes) {
            for (auto destination : node->getDestinations()) {
                addEdge(node->getSource(), destination->getSource());
            }
        }
    }

    Graph& operator=(const Graph other) {
        nodes.clear();

        for (auto node : other.nodes) {
            nodes.push_back(new Node(node->getSource()));
        }

        for (auto node : other.nodes) {
            for (auto destination : node->getDestinations()) {
                addEdge(node->getSource(), destination->getSource());
            }
        }

        return *this;
    }

    void addEdge(int src, int dst) {
        Node* srcNode = findNode(src);
        Node* dstNode = findNode(dst);

        if (!srcNode) {
            srcNode = new Node(src);
            nodes.push_back(srcNode);
        }

        if (!dstNode) {
            dstNode = new Node(dst);
            nodes.push_back(dstNode);
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
    Node* findNode(int src) {
        for (auto node : nodes) {
            if (node->getSource() == src)
                return node;
        }

        return nullptr;
    }
};
