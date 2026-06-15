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
    quickSort(pairs) {
        this.quickInPlace(pairs, 0, pairs.length - 1);

        return pairs;
    }

    quickInPlace(arr, i, j) {
        if (j - i <= 0) return;

        const pivot = arr[j];
        let tail = i;

        for (let march = i; march < j; march++) {
            if (arr[march].key >= pivot.key) continue;
            if (march == tail) {
                tail++;
                continue;
            }
            
            const temp = arr[tail];
            arr[tail] = arr[march];
            arr[march] = temp;
            tail++;
        }

        const temp = arr[tail];
        arr[tail] = arr[j];
        arr[j] = temp;

        this.quickInPlace(arr, i, tail - 1);
        this.quickInPlace(arr, tail + 1, j);
    }
}
