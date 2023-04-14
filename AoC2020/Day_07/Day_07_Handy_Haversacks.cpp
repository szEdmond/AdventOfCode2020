#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include <queue>


std::unordered_map<std::string, std::vector<std::string>> thisCanBeInsideof;//this color of bag can fit into
std::unordered_map < std::string, std::unordered_map<std::string,int>> contains;
//regex for number, adjective, color : /([\d][\s]+[\w]+[\s]+[\w]+)/
// regex for first 2 words ^[\w]+[\s][\w]+;

void read_input(const std::string& aPath) {
	std::ifstream f(aPath);	
	std::string line;
	std::string bag;
	std::regex pat{ "^[\\w]+[\\s][\\w]+" }; // regex for first 2 words of string
	std::regex pat2{ "[\\d][\\s]+[\\w]+[\\s]+[\\w]+" }; // regex for "number adjective color"
	std::smatch match;

	std::string currentBag;

	while (std::getline(f, line))
	{
		std::unordered_map<std::string, int> inside;
		// get current bag
		if (std::regex_search(line, match, pat))
		{
			currentBag = match[0];
		}
		// get bags that this bag can contain
		for (std::sregex_iterator it = std::sregex_iterator(line.begin(), line.end(), pat2);
			it != std::sregex_iterator(); it++) {
			match = *it;
			std::string temp = match.str();
			contains[currentBag][temp.substr(2, temp.size())] = (temp[0]-'0');
			thisCanBeInsideof[temp.substr(2,temp.size())].push_back(currentBag);
		}
	}
}
int number_of_bags_can_hold_it() {
	std::unordered_set<std::string> bags{ "shiny gold" };
	int count = 0;
	while (count < bags.size()) {//if anything has been added to the list
		count = bags.size();
		for (const auto& bag : bags) { //fore bag thats in shinyGold
			for (const auto& moreBags : thisCanBeInsideof[bag]) { 
				if (!bags.contains(moreBags)) {
					bags.insert(moreBags);
				}
			}
		}
	}
	return bags.size() - 1;
}

int max_bags_inside() {
	std::queue<std::string> bagQ;
	bagQ.push("shiny gold");
	int count = 0;
	while (!bagQ.empty()) {
		std::string current = bagQ.front();
		bagQ.pop();
		for (auto& bag : contains[current]) {
			for (int i = 0; i < bag.second; i++) {
				bagQ.push(bag.first);
				count++;
			}
		}
	}
	return count;
}

int main()
{
	read_input("input/day_07.txt");
	
	// Part 1 (How many bag colors can eventualy contain at least one "shiny gold")
	std::cout << number_of_bags_can_hold_it() << '\n';

	// Part 2 (Maximum bags can be held in shiny gold)
	std::cout << max_bags_inside() << '\n';
}
