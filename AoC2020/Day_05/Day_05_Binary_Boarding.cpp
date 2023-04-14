#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include<algorithm>
#include <chrono>

class Seat {
public:
	int mRow{ INT_MIN };
	int mCol{ INT_MIN };
	int mSeatID{ INT_MIN };

	Seat(const std::string& aSeatCode) 
	{
		mRow = parseRow(aSeatCode);
		mCol = parseCol(aSeatCode);
		mSeatID = mRow * 8 + mCol;
	}
	
	bool operator<(const Seat& other) const 
	{
		return mSeatID> other.mSeatID;
	}

private:
	int parseCol(const std::string& aSeatCode) const 
	{
		int low = 0;
		int high = 7;
		for (int i = 7; i < 10; ++i) {
			if (aSeatCode[i] == 'L') 
				high = high - ((high - low) / 2) - 1;
			else 
				low = low + ((high - low) / 2) + 1;
		}
		return high;
	}

	int parseRow(const std::string& aSeatCode) const
	{
		int low = 0;
		int high = 127;
		for (int i = 0; i < 7; ++i) {
			if (aSeatCode[i] == 'F') 
				high = high - ((high - low) / 2) - 1;
			else 
				low = low + ((high - low) / 2) + 1;
		}
		return high;
	}
};

void read_input(const std::string& aPath, std::vector<Seat>& aSeats) 
{
	std::ifstream f(aPath);
	std::string line;

	while (std::getline(f, line)) 
	{
		aSeats.push_back(Seat(line));
	}
}

int find_missing_seat(const std::vector<Seat>& aSeats) 
{
	for (int i = 0; i < aSeats.size() - 1; ++i) 
	{
		if (aSeats[i].mSeatID - 1 != aSeats[i + 1].mSeatID)
		{
			return aSeats[i].mSeatID - 1;
		}
	}
	return 0;
}


int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<Seat> seats;
	seats.reserve(1000);
	read_input("input/day_05.txt", seats);
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	//std::cout << "time taken: " << time << "\n";
	
	// Part 1
	std::sort(seats.begin(), seats.end());
	std::cout << "Highest SeatID: " << seats[0].mSeatID << '\n';

	// Part 2
	std::cout << "The ID of our seat is: " << find_missing_seat(seats) << '\n';
}