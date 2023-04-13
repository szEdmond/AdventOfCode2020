#include<iostream>
#include<fstream>
#include <string>
#include <unordered_map>
#include <chrono>


#define PART1
#define PART2

int main() {
	std::string text;
	std::ifstream f("input/day_01.txt");
	std::unordered_map<int, int> mp;

	while (std::getline(f, text)) {
		mp[std::stoi(text)]++;
	}

//#define PART1
#ifdef PART1
	printf("%s", "Part1 Solution: ");
	for (auto [val, occ] : mp) {
		int tolookFor = 2020 - val;
		if (mp.find(tolookFor) != mp.end()) {
			std::cout << val * tolookFor << '\n';
			break;
		}
	}
#endif // !PART1

#ifdef PART2
	printf("%s", "Part2 Solution: ");
	auto start = std::chrono::high_resolution_clock::now();

	bool found = false;
	for (auto [first, occ] : mp) {
		for (auto [second, x] : mp) {
			if (first + second < 2020) {
				int remaining = 2020 - first - second;
				if (mp.find(remaining) != mp.end()) {
					std::cout << first * second * remaining << '\n';
					found = true;
					break;
				}
			}
		}
		if (found) 
			break;
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	printf("%s", "Time taken: ");
	std::cout << duration.count();
#endif // !PART1

}