class Solution {
    /**
     * @param {number[][]}
     * @returns {number}
     */
    shortestPath(grid) {
        return (new DFS(grid)).getShortest();
    }
}

class DFS {
    static STATES = {
        land: 0,
        rock: 1,
        visited: 2,
    };

    grid;
    gridMaxY;
    gridMaxX;
    start;
    end;
    queue;
    result;
    visited;

    constructor(grid) {
        this.grid = grid;
        this.gridMaxY = grid.length - 1;
        this.gridMaxX = grid[this.gridMaxY].length - 1;

        this.start = { x: 0, y: 0 };
        this.end = { x: this.gridMaxX, y: this.gridMaxY };

        this.queue = [];
        this.result = -1;
        this.visited = [];
        
        this.addToQueue(this.start);
    }

    getShortest() {
        let item;
        while ((item = this.queue.shift()) && this.result == -1) {
            this.getShortestIter(item)
        }

        return this.result;
    }

    getShortestIter({ position, history }) {
        if (!position) return;

        if (this.lookup(position) != DFS.STATES.land)
            if (this.lookup(position))
                return;

        if (position.x == this.end.x && position.y == this.end.y) {
            this.result = history.length;
            return;
        }

        this.setPos(position, DFS.STATES.visited);

        const candidates = [
            { x: position.x,     y: position.y - 1 },
            { x: position.x,     y: position.y + 1 },
            { x: position.x - 1, y: position.y     },
            { x: position.x + 1, y: position.y     },
        ];

        candidates.forEach((candidate) => {
            if (candidate.x < 0) return;
            if (candidate.y < 0) return;
            if (candidate.x > this.gridMaxX) return;
            if (candidate.y > this.gridMaxY) return;
            if (this.lookup(candidate) != DFS.STATES.land) return;

            this.addToQueue(candidate, history.concat(`${position.x},${position.y}`));
        });
    }

    addToQueue(position, history=[]) {
        this.queue.push({
            position,
            history,
        });
    }

    lookup(position) {
        return this.grid[position.y][position.x];
    }

    setPos(position, value) {
        this.grid[position.y][position.x] = value;
    }
}