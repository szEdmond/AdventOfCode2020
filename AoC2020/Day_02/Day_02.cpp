#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

struct pw {
	int min;
	int max;
	char ch;
	std::string password;

	friend std::istream& operator>>(std::istream& in, pw& password);
};

std::istream& operator>>(std::istream& in, pw& aPw) {
	char temp;
	in >> aPw.min;
	in >> temp;
	in >> aPw.max;
	in >> aPw.ch;
	in >> temp;
	in >> aPw.password;
	return in;
}

void read_input(std::vector<pw>& data) {
	std::ifstream f{ "input/day_02.txt" };
	pw temp_pw;
	while (f >> temp_pw) {
		data.push_back(temp_pw);
	}
}

int count_passwords_part1(const std::vector<pw>& passwords) {
	int count = 0;
	for (const auto& data : passwords) {
		int cnt = std::count(data.password.begin(), data.password.end(), data.ch);
		if (cnt >= data.min && cnt <= data.max)
			++count;
	}
	return count;
}

int count_passwords_part2(const std::vector<pw>& passwords) {
	int count = 0;
	for (const auto& data : passwords) {
		if ((data.password[data.min - 1] == data.ch) ^ (data.password[data.max - 1] == data.ch))
			++count;
	}
	return count;
}

int main()
{
	std::vector<pw> data;
	data.reserve(1000);

	auto start = std::chrono::high_resolution_clock::now();
	read_input(data);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Reading input took: " << duration << " microseconds\n";
	
	// Part1
	int good_pw = count_passwords_part1(data);
	std::cout << "Number of passwords with old policy: " << good_pw << '\n';

	// Part2
	int good_pw2 = count_passwords_part2(data);
	std::cout << "Number of passwords with new policy: " << good_pw2 << '\n';

}