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
    mergeSort(pairs) {
		if (pairs.length <= 1) {
			return pairs;
		}

		const middleIndex = Math.floor(pairs.length / 2);
		const firstHalf = this.mergeSort(pairs.slice(0, middleIndex));
		const secondHalf = this.mergeSort(pairs.slice(middleIndex));

		const result = [];
		let firstI = 0;
		let secondI = 0;
		while (firstI < firstHalf.length || secondI < secondHalf.length) {
			if (firstI >= firstHalf.length) {
				result.push(secondHalf[secondI]);
				secondI++;
				continue;
			}
			if (secondI >= secondHalf.length) {
				result.push(firstHalf[firstI]);
				firstI++;
				continue;
			}

			if (firstHalf[firstI].key <= secondHalf[secondI].key) {
				result.push(firstHalf[firstI]);
				firstI++;
				continue;
			} else {
				result.push(secondHalf[secondI]);
				secondI++;
				continue;
			}
		}

		return result;
	}
}
