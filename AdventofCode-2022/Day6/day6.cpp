#include "day6.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <deque>

namespace 
{
	std::string ReadFile(const std::string& file)
	{
		if (std::ifstream infile(file); infile.good())
		{
			std::string file_content;
			std::getline(infile, file_content);
			return file_content;
		}
		return "";
	}

	// This definitely isn't the best way to do this
	bool CheckUnique(const std::deque<char>& marker)
	{
		for (size_t i = 0; i < marker.size(); i++)
		{
			for (size_t j = i; j < marker.size(); j++)
			{
				if (marker[i] == marker[j] && i != j)
					return false;
			}
		}

		return true;
	}

	int FindMarker(const std::string& input, const size_t packet_size)
	{
		std::deque<char> marker;
		for (size_t i = 0; i < input.size(); i++)
		{
			marker.push_back(input[i]);
			if (marker.size() == packet_size && CheckUnique(marker))
				return static_cast<int>(i) + 1;
			if (i >= (packet_size - 1))
				marker.pop_front();
		}

		return -1;
	}
} // end of anonymous namespace

void Day6(const Day6Choices choice)
{
	switch (choice)
	{
	case k6Test:
		std::cout << FindMarker(ReadFile("Day6/test.txt"), 4) << std::endl;
		break;
	case k6Part1:
		std::cout << FindMarker(ReadFile("Day6/input.txt"), 4) << std::endl;
		break;
	case k6Part2:
		std::cout << FindMarker(ReadFile("Day6/input.txt"), 14) << std::endl;
		break;
	default:  // NOLINT(clang-diagnostic-covered-switch-default)
		std::cout << "Not a viable option" << std::endl;
		break;
	}
}