class Solution {
    static STATES = {
        land: 0,
        rock: 1,
        visited: 2,
    };

    /**
     * @param {number[][]} grid
     * @returns {number}
     */
    countPaths(grid) {
        const start = [0, 0];
        const goal = [grid.length - 1, grid[grid.length - 1].length - 1];

        console.log(start, goal);

        return this.traverse(grid, start, goal);
    }

    // Both position & goal are in form [y, x]
    // returns an int with positions found
    traverse(grid, position, goal, path = []) {
        if (grid[position[0]][position[1]] != Solution.STATES.land)
            return 0;
            
        if (position[0] == goal[0] && position[1] == goal[1])
            return 1;

        path.push(position);

        const x = position[1];
        const y = position[0];
        
        grid[y][x] = Solution.STATES.visited;

        const candidates = [
            [y,     x - 1], // Left
            [y,     x + 1], // Right
            [y - 1, x    ], // Down
            [y + 1, x    ], // Up
        ];

        for (let i = 0; i < candidates.length; i++) {
            const candidate = candidates[i];

            if (candidate[0] < 0 || candidate[0] >= grid.length
                || candidate[1] < 0 || candidate[1] >= grid[candidate[0]].length) {
                candidates.splice(i, 1);
                i--;
            }
        }

        let routeCount = 0;
        candidates.forEach((candidate) => {
            if (grid[candidate[0]][candidate[1]] === Solution.STATES.land) {
                routeCount += this.traverse(grid, candidate, goal, path);
            }
        });

        grid[y][x] = Solution.STATES.land;
        path.splice(-1, 1);

        return routeCount;
    }
}
