#include "day4.hpp"

#include <iostream>
#include <fstream>
#include <string>
// #include <cstring>
#include <string_view>
// includes for the timing
#include <chrono>

int test(std::string elf1, std::string elf2) {
    std::string delim = "-";
    bool elf1_smaller = false;
    bool elf1_bigger = false;
    bool elf2_smaller = false;
    bool elf2_bigger = false;

    if (std::stoi(elf2.substr(0, elf2.find(delim))) < 
        std::stoi(elf1.substr(0, elf1.find(delim)))) {
        elf1_smaller = false;
        elf2_smaller = true;
    } else if (std::stoi(elf2.substr(0, elf2.length())) == 
        std::stoi(elf1.substr(0, elf1.length()))) {
        elf1_smaller = true;
        elf2_smaller = true;
    } else {
        elf1_smaller = true;
        elf2_smaller = false;
    }
    if (std::stoi(elf2.substr(elf2.find(delim) + 1, elf2.length())) > 
        std::stoi(elf1.substr(elf1.find(delim) + 1, elf1.length()))) {
        elf1_bigger = false;
        elf2_bigger = true;
    } else if (std::stoi(elf2.substr(elf2.find(delim) + 1, elf2.length())) == 
        std::stoi(elf1.substr(elf1.find(delim) + 1, elf1.length()))) {
        elf1_bigger = true;
        elf2_bigger = true;
    } else {
        elf1_bigger = true;
        elf2_bigger = false;
    }

    if ((elf1_bigger && elf1_smaller) || (elf2_bigger && elf2_smaller)) {
        return 1;
    }
    return 0;
}

int any_overlap(std::string elf1, std::string elf2) {
    std::string delim = "-";

    if (std::stoi(elf2.substr(0, elf2.find(delim))) <= 
        std::stoi(elf1.substr(elf1.find(delim) + 1, elf1.length())) &&
        std::stoi(elf2.substr(elf2.find(delim) + 1, elf2.length())) >= 
        std::stoi(elf1.substr(0, elf1.find(delim)))) {
        printf("1\n");
        return 1;
    }

    printf("0\n");
    return 0;
}

void read_input(std::string file, int (*function)(std::string, std::string)) {
    std::ifstream myfile(file);
    std::string myline;
    int result = 0;
    std::string elf1, elf2;
    std::string delim = ",";
    std::string test_string = "hello man";

    if (myfile.is_open()) {
        while(std::getline(myfile, myline)) {
            elf1 = myline.substr(0, myline.find(delim));
            elf2 = myline.substr(myline.find(delim) + 1, myline.length());
            printf("%s\t", myline.data());
            result += (*function)(elf1, elf2);
        }
    } else {
        perror("Can't open file");
        return;
    }

    printf("Amount of assignments with full overlap: %d\n", result);
}

void day4(usecase4 uc) {
    auto start = std::chrono::high_resolution_clock::now();
    if (uc == 0) 
    {
        read_input("Day4/test.txt", &any_overlap);
    }
    else if (uc == 1) 
    {
        read_input("Day4/input.txt", &test);
    }
    else if (uc == 2) 
    {
        read_input("Day4/input.txt", &any_overlap);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                                                                (stop - start);

    std::cout << "Done in: " << duration.count() << " ms" << std::endl;
}