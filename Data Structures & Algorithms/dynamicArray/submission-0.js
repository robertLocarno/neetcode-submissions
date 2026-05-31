class DynamicArray {
    constructor(capacity) {
        this.capacity = capacity;
        this.items = [];
    }

    get(i) {
        return this.items[i];
    }

    set(i, n) {
        this.items[i] = n;
    }

    pushback(n) {
        const index = this.getSize();

        if (index >= this.capacity) {
            this.resize();
        } 

        this.items[index] = n;
    }

    popback() {
        return this.items.splice(this.getSize() - 1, 1);
    }

    resize() {
        this.capacity *= 2;
    }

    getSize() {
        return this.items.length;
    }

    getCapacity() {
        return this.capacity;
    }
}
