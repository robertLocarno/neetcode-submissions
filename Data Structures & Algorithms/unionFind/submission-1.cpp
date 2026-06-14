class UnionFind {
	int size;
	std::vector<int*> components;

public:
	UnionFind(int n) {
		size = n;

		components.reserve(n);
		for (size_t i = 0; i < n; i++) {
			int* val = new int(i);
			components.push_back(val);
		}
	}

	~UnionFind() {
		std::unordered_set<int*> allocatedComponents;
		for (auto component : components) {
			allocatedComponents.insert(component);
		}

		for (auto allocatedComponent : allocatedComponents) {
			delete allocatedComponent;
		}
	}

	UnionFind(const UnionFind& other) {
		for (auto otherComponent : other.getComponents()) {
			int* val = new int(*otherComponent);
			components.push_back(val);
		}
	}

	UnionFind& operator=(const UnionFind other) {
		other.getComponents().swap(components);

		return *this;
	}

	std::vector<int*> getComponents() const {
		return components;
	}

	// Returns the root of the component x belongs to
	int find(int x) const {
		return *components[x];
	}

	// Returns whether x and y belong to the same component
	bool isSameComponent(int x, int y) const {
		return find(x) == find(y);
	}

	// Will union the components that x and y belong to.
	// If they are already in the same component, return false.
	// Otherwise return true.
	// Union is a reserved keyword in C++, so we use _union instead
	bool _union(int x, int y) {
		if (find(x) == find(y)) return false;

		size--;

		int* oldRef = components[y];
		delete components[y];
		
		for (auto i = components.begin(); i < components.end(); i++) {
			if (*i == oldRef) {
				*i = components[x];
			}
		}

		return true;
	}

	// Will return the number of components in the disjoint set
	int getNumComponents() const {
		return size;
	}
};
