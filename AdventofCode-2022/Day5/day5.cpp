#include "day5.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <deque>
#include <vector>
#include <stack>

void print_deques(std::deque<char> mydeque) {
    while (!mydeque.empty()) {
        printf("%c\t", mydeque.back());
        mydeque.pop_back();
    }
    printf(".\n");
}

std::vector<std::deque<char>> create_deque(std::string file) {
    std::fstream myfile(file);
    if (!(myfile.is_open())) { perror("Can't open."); } 
    std::string myline;
    std::vector<std::deque<char>> myvector;
    int current_queue = 0;

    while (std::getline(myfile, myline)) {
        if (myline[1] == '1') { break; }
        for (size_t i = 1; i < myline.length(); i += 4) {
            char current = myline[i];
            if (myvector.size() < (size_t)(current_queue + 1)) {
                myvector.push_back(std::deque<char>());
            }
            if (!(current == ' ')) {
                myvector[current_queue].push_front(current);
            }
            current_queue++;
        }
        current_queue = 0;
    }

    myfile.close();
    return myvector;
}

std::vector<int> create_order(std::string file) {
    std::fstream myfile(file);
    if (!(myfile.is_open())) { perror("Can't open."); }
    std::vector<int> myvector;
    std::string myline;
    std::string token;
    bool instructions = false;
    char delim = ' ';
    int count = 1;
    int place = 0;

    while(std::getline(myfile, myline)) {
        std::stringstream ss(myline);
        while (std::getline(ss, token, delim)) {
            if (token == "move") {
                instructions = true;
            }
            if (instructions) {
                if (count > 0 && (count % 2 == 0)) {
                    myvector.push_back(int());
                    myvector[place] = atoi(token.data());
                    place++;
                    count++;
                } else {
                    count++;
                }
            }
        }
    }

    return myvector;
}

std::vector<std::deque<char>> order_deque(std::vector<std::deque<char>> crates,
                                            std::vector<int> sorting_order) 
{
    for (size_t i = 0; i < sorting_order.size(); i+=3) {
        for (size_t j = 0; j < sorting_order[i]; j++) {
            char moving_crate = crates[sorting_order[i+1] - 1].back();
            crates[sorting_order[i+2] - 1].push_back(moving_crate);
            crates[sorting_order[i+1] - 1].pop_back();
        }
    }
    
    return crates;
}

std::vector<std::deque<char>> order_deque_2(std::vector<std::deque<char>> crates,
                                            std::vector<int> sorting_order)
{
    std::stack<char> temp_stack;
    for (size_t i = 0; i < sorting_order.size(); i += 3)
    {
        for (size_t j = 0; j < sorting_order[i]; j++)
        {
            temp_stack.push(crates[sorting_order[i + 1] - 1].back());
            crates[sorting_order[i + 1] - 1].pop_back();
        }
        while (!temp_stack.empty())
        {
            crates[sorting_order[i + 2] - 1].push_back(temp_stack.top());
            temp_stack.pop();
        }
    }

    return crates;
}

void day5() {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::deque<char>> crates = create_deque("Day5/input.txt");
    std::vector<int> sorting_order = create_order("Day5/input.txt");
    // used to check if deque are in the right order
    for (size_t i = 0; i < crates.size(); i++) {
        print_deques(crates[i]);
    }
    printf("\n");
    // for (size_t i = 0; i < sorting_order.size(); i++)
    // {
    //     printf("%d\t", sorting_order[i]);
    //     if ((i + 1) % 3 == 0) { printf("\n"); }
    // }
    std::vector<std::deque<char>> ordered_crates = order_deque_2(crates, sorting_order);
    for (size_t i = 0; i < ordered_crates.size(); i++) {
        print_deques(ordered_crates[i]);
    }
    printf("\n");
    for (size_t i = 0; i < ordered_crates.size(); i++)
    {
        printf("%c", ordered_crates[i].back());
    }
    printf("\n\n");

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Done in: " << duration.count() << " ms" << std::endl;
}
