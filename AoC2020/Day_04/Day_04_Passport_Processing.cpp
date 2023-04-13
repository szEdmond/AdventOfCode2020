#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

struct Passport {
	int byr, iyr, eyr, hgt, pid, cid;
	std::string hcl, ecl;
	bool metric, valid;
	
	Passport(const std::string& aPassport) {
		byr = 0;
		iyr = 0;
		eyr = 0;
		hgt = 0;
		pid = 0;
		cid = 0;
		hcl = "";
		ecl = "";
		metric = true;
		valid = true;

		std::string datapair;
		auto stream = std::istringstream{ aPassport };
		
		while (stream >> datapair)
		{
			auto it = datapair.find(':');
			std::string first = datapair.substr(0, it);
			std::string second = datapair.substr(it + 1, datapair.size());

			if (first == "byr") 
			{
				std::regex pat{ "\\d{4}" };
				if (!std::regex_match(second, pat)) {
					valid = false;
					continue;
				}
				byr = std::stoi(second);
				if (byr < 1920 || byr > 2002) {
					valid = false;
					continue;
				}
			}
			if (first == "iyr")
			{
				std::regex pat{ "\\d{4}" };
				if (!std::regex_match(second, pat)) {
					valid = false;
					continue;
				}
				iyr = std::stoi(second);
				if (iyr < 2010 || iyr > 2020) {
					valid = false; 
					continue;
				}
			}
			if (first == "eyr") 
			{
				std::regex pat{ "\\d{4}" };
				if (!std::regex_match(second, pat)) {
					valid = false;
					continue;
				}
				eyr = std::stoi(second);
				if (eyr < 2020 || eyr >2030) {
					valid = false;
					continue;
				}
			}
			if (first == "hgt")
			{
				auto cm_it = second.find("cm");
				auto in_it = second.find("in");
				if (cm_it != std::string::npos) {
					metric = true;
					hgt = std::stoi(second.substr(0, it));
				}
				else if (in_it != std::string::npos) {
					metric = false;
					hgt = std::stoi(second.substr(0, it));
				}
				else {
					valid = false;
					continue;
				}
				if (metric) {
					if (hgt < 150 || hgt > 193) {
						valid = false;
						continue;
					}
				}
				else {
					if (hgt < 59 || hgt > 76) {
						valid = false;
						continue;
					}
				}
			}
			if (first == "hcl")
			{
				std::regex pat{ "[#][0-9|a-f]{6}" };
				if (!std::regex_match(second, pat)) {
					valid = false;
					continue;
				}
				hcl = second;
			}
			if (first == "ecl")
			{
				std::regex pat {"amb|blu|brn|gry|grn|hzl|oth"};
				if (!std::regex_match(second, pat)) {
					valid = false;
					continue;
				}
				ecl = second;
			}
			if (first == "pid")
			{
				std::regex pat{ "^\\d{9}$" };
				if (!std::regex_match(second, pat)) {
					valid = false;
					continue;
				}
				pid = std::stoi(second);
			}
		}

	}
};

void read_input(const std::string& aPath, std::vector<std::string>& aPassports)
{
	std::ifstream f(aPath);
	std::string line;
	std::string passport;

	while (std::getline(f, line))
	{
		if (line.empty() && !passport.empty()) {
			aPassports.push_back(passport);
			passport = " ";
		}
		if (!line.empty()) {
			passport += line;
			passport += " ";
		}
	}
	if (!passport.empty()) {
		aPassports.push_back(passport);
	}
}

int count_and_filter_passports(const std::vector<std::string>& aData, std::vector<std::string>& aPassed)
{
	int count_passed = 0;
	bool valid = true;
	std::vector<std::string> checks{ "byr", "eyr", "iyr", "hgt", "pid", "hcl", "ecl" };
	for (auto data : aData) {
		for (auto field : checks) {
			if (data.find(field) == std::string::npos) {
				valid = false;
				break;
			}
		}
		if (!valid) {
			valid = true;
		}
		else {
			count_passed++;
			aPassed.push_back(data);
		}
	}
	return count_passed;
}

int count_valid_passports(std::vector<std::string>& aFiltered_passports) {
	int valid = 0;
	for (const auto& passport : aFiltered_passports) {
		if (Passport(passport).valid)
			++valid;
	}
	return valid;
}

int main()
{
	std::vector<std::string> passports;
	read_input("input/day_04.txt", passports);

	// Part 1
	std::vector<std::string> filtered_passports;
	int filtered = count_and_filter_passports(passports, filtered_passports);
	std::cout << "Passports that passed: " << filtered << '\n';

	// Part 2
	int valid = count_valid_passports(filtered_passports);
	std::cout << "Valid passports: " << valid << '\n';
}