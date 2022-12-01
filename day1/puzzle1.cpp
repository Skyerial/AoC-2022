#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream myfile ("puzzle_input.txt");
    std::string myline;

    int top_three[3] = {0};
    int current_calories = 0;

    if (myfile.is_open()) {
        while (std::getline(myfile, myline) || current_calories != 0) {
            if (myline.compare("") == 0) {
                std::cout << "blank line" << "\n";
                if (current_calories > top_three[0]) {
                    top_three[2] = top_three[1];
                    top_three[1] = top_three[0];
                    top_three[0] = current_calories;
                    current_calories = 0;
                } else if (current_calories > top_three[1]) {
                    top_three[2] = top_three[1];
                    top_three[1] = current_calories;
                    current_calories = 0;
                } else if (current_calories > top_three[2]) {
                    top_three[2] = current_calories;
                    current_calories = 0;
                } else {
                    current_calories = 0;
                }
            } else {
                std::cout << myline << "\t";
                current_calories += std::stoi(myline, nullptr, 0);
                std::cout << current_calories << "\n";
            }
        }
    }
    std::cout << "\n" << top_three[0] << "\n";
    std::cout << top_three[1] << "\n";
    std::cout << top_three[2] << "\n";
    std::cout << top_three[0] + top_three[1] + top_three[2];
}
