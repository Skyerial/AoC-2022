#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <chrono>
#include <algorithm>

int common_char(char *first_half, char *second_half, int len) {
    int letters[52] = {0};
    for (int i = 0; i < len / 2; i++) {
        if (first_half[i] >= 'A' && first_half[i] <= 'Z') {
            letters[(first_half[i] % 65) + 26]++;
        } else {
            letters[first_half[i] % 97]++;
        }
    }
    for (int i = 0; i < len / 2; i++) {
        if (second_half[i] >= 'A' && second_half[i] <= 'Z') {
            if (letters[(second_half[i] % 65) + 26] != 0) {
                return second_half[i] - 'A' + 27;
            }
        } else {
            if (letters[second_half[i] % 97] != 0) {
                return second_half[i] - 'a' + 1;
            }
        }
    }

    return -100000;
}

int split_string(std::string myline) {
    char first_half[50];
    char second_half[50];
    int len = myline.length();
    memcpy(first_half, myline.data(), len / 2);
    first_half[len / 2] = '\0';
    memcpy(second_half, &myline.data()[len / 2], len / 2);
    second_half[len / 2] = '\0';
    
    int result = common_char(first_half, second_half, len);
    return result;
}

int common_three(std::string *myline) {
    int elf[3][52] = {0};
    int result = 0;

    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < myline[j].length(); i++) {
            if (myline[j][i] >= 'A' && myline[j][i] <= 'Z') {
                elf[j][(myline[j][i] % 65) + 26]++;
            } else {
                elf[j][myline[j][i] % 97]++;
            }
        }
    }

    for (int i = 0; i < 52; i++) {
        if (elf[0][i] != 0 && elf[1][i] != 0 && elf[2][i] != 0) {
            return i + 1;
        }
    }
    
    return -100000;
}

int test(const char *file, bool halved_string) {
    std::ifstream myfile(file);
    std::string myline;
    int sum = 0;
    int count = 0;
    std::string common[3];

    if (!myfile.is_open()) {
        myfile.close();
        perror("Can't open file");
        return 1;
    } else {
        if (halved_string) {
            while (std::getline(myfile, myline)) {
                sum += split_string(myline);
            }
        } else {
            while (std::getline(myfile, myline)) {
                common[count] = myline;
                count++;
                if (count >= 3) {
                    sum += common_three(common);
                    count = 0;
                }
            }
        }
    }

    printf("%d\n", sum);
    myfile.close();
    return 0;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    if (strcmp(argv[1], "test") == 0) {
        if (test("test.txt", true) == 1) { return 1; }
    } else if (strcmp(argv[1], "p1") == 0) {
        if (test("input.txt", true) == 1) { return 1; }
    } else if (strcmp(argv[1], "p2") == 0) {
        if (test("input.txt", false) == 1) { return 1; }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                                                                (stop - start);

    std::cout << "Done in: " << duration.count() << " ms" << std::endl;
    return 0;
}