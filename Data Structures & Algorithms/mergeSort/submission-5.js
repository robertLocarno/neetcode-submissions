/** Pair class to store key-value pairs */
// class Pair {
//   /**
//    * @param {number} key The key to be stored in the pair
//    * @param {string} value The value to be stored in the pair
//    */
//   constructor(key, value) {
//       this.key = key;
//       this.value = value;
//   }
// }
class Solution {
    /**
     * @param {Pair[]} pairs
     * @returns {Pair[]}
     */
	// in place implementation
    mergeSort(pairs, i = 0, j = pairs.length) {
		if (j - i <= 1) {
			return pairs;
		}

		const middleIndex = Math.floor((j - i) / 2) + i;
		this.mergeSort(pairs, i, middleIndex);
		this.mergeSort(pairs, middleIndex, j);

		let firstI = i;
		let secondI = middleIndex;
		while (firstI < j) {
			if (secondI >= j || secondI == firstI) {
				break;
			}

			if (pairs[firstI].key <= pairs[secondI].key) {
				firstI++;
				continue;
			}

			this.move(pairs, firstI, secondI);
			firstI++;
			secondI++;
		}

		return pairs;
	}

	move(arr, i, j) {
		arr.splice(i, 0, arr[j]);
		arr.splice(j + 1, 1);
	}
}
