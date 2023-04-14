#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

class Answers {
public:
	int mAnswers[26] {};
	int mGroupSize{ 0 };

	Answers(const std::string& aGroup, int aGroupSize) {
		for (int i = 0; i < aGroup.size(); ++i) {
			mAnswers[aGroup[i] - 'a']++;
		}
		mGroupSize = aGroupSize;
	}
};

void read_input(const std::string& aPath, std::vector<Answers>& aAnswers) {
	std::fstream f(aPath);
	std::string group = "";
	std::string line;
	int groupSize = 0;
	while (std::getline(f, line)){
		if (line.empty()) {
			aAnswers.push_back(Answers(group, groupSize));
			group = "";
			groupSize = 0;
		}
		else {
			group += line;
			++groupSize;
		}
	}
	aAnswers.push_back(Answers(group, groupSize));
}

int count_any_yes(const std::vector<Answers>& aAnswers) {
	int sum = 0;
	for (const Answers& group : aAnswers) {
		for (const auto& ans : group.mAnswers) {
			if (ans != 0) {
				sum++;
			}
		}
	}
	return sum;
}

int count_group_yes(const std::vector<Answers>& aAnswers) {
	int res = 0;
	for (const Answers& group : aAnswers) {
		for (const auto& ans : group.mAnswers) {
			if (ans == group.mGroupSize) {
				res++;
			}
		}
	}
	return res;
}

int main()
{
	std::vector<Answers> answers;
	read_input("input/day_06.txt", answers);

	// Part 1
	int anyYes = count_any_yes(answers);
	std::cout << "Num of any question answered with yes: " << anyYes <<  '\n';

	// Part 2
	int groupYes = count_group_yes(answers);
	std::cout << "Num of questions to which everyone answered yes: " << groupYes << '\n';
}