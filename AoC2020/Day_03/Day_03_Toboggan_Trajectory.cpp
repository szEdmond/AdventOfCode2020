#include <fstream>
#include <vector>
#include <string>
#include <iostream>

void read_input(const std::string& aPath, std::vector<std::string>& aData) {
	std::ifstream f(aPath);
	std::string line;
	while (f >> line) {
		aData.push_back(line);
	}
}

int count_tree_first(const std::vector<std::string>& aData) {
	int treeCount = 0;
	int down = 0;
	int right = 0;

	for (const auto& line : aData) {
		if (line[right % line.size()] == '#')
			treeCount++;
		right += 3;
	}

	return treeCount;
}

unsigned int count_other_slopes(const std::vector<std::string>& aData) {
	std::vector<std::pair<int, int>> slopes{ {1,1}, {3,1}, {5,1}, {7,1}, {1,2} };
	unsigned int result = 1;
	for (auto slope : slopes) {
		int right = 0;
		int treeCount = 0;
		for (int y = 0; y < aData.size(); y += slope.second) {
			if (aData[y][right % aData[0].size()] == '#') {
				treeCount++;
			}
			right += slope.first;
		}
		result *= treeCount;
	}
	return result;
}

int main() {

	std::vector<std::string> data;
	read_input("input/day_03.txt", data);

	int treeCount = count_tree_first(data);
	std::cout << "Trees on slope {3,1}: " << treeCount << '\n';

	unsigned int multiple_slopes = count_other_slopes(data);
	std::cout << "Product of multiple slopes: " << multiple_slopes << '\n';
}
