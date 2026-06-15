// Definition for a Pair
// class Pair {
// public:
//     int key;
//     string value;
//
//     Pair(int key, string value) : key(key), value(value) {}
// };
class Solution {
public:
	std::vector<std::vector<Pair>> insertionSort(std::vector<Pair>& pairs) {
		std::vector<Pair> result{};
		std::vector<std::vector<Pair>> resultHistory{};

		for (size_t i = 0; i < pairs.size(); i++) {
			for (size_t j = 0; j <= result.size(); j++) {
				if (j == result.size()) {
					result.push_back(pairs[i]);
					break;
				}

				if (result[j].key > pairs[i].key) {
					result.insert(result.begin() + j, pairs[i]);
					break;
				}
			}

			std::vector<Pair> log = result;
			for (size_t z = result.size(); z < pairs.size(); z++) {
				log.push_back(pairs[z]);
			}

			resultHistory.push_back(log);
		}

		return resultHistory; 
	}
};
