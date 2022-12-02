#include <iostream>

// A and X is rock      1
// B and Y is paper     2
// C and Z is siccors   3
// lose=0, draw=3, win=6

int calculate_score(char one, char two) {
    int score = 0;
    if (one == two - 23) {
        score += 3;
    } else if (one == 'A' && two == 'Y') {
        score += 6;
    } else if (one == 'B' && two == 'Z') {
        score += 6;
    } else if (one == 'C' && two == 'X') {
        score += 6;
    }
    score += two - 87;

    return score;
}

// X is lose
// Y is draw
// Z is win
// A is rock    1
// B is paper   2
// C is siccors 3
int calculate_score2(char one, char two) {
    int score = 0;
    if (two == 'X') {
        if (one == 'A') { score += 3; }
        if (one == 'B') { score += 1; }
        if (one == 'C') { score += 2; }
    } else if (two == 'Y') {
        score += 3;
        if (one == 'A') { score += 1; }
        if (one == 'B') { score += 2; }
        if (one == 'C') { score += 3; }
    } else if (two == 'Z') {
        score += 6;
        if (one == 'A') { score += 2; }
        if (one == 'B') { score += 3; }
        if (one == 'C') { score += 1; }
    }

    return score;
}

int puzzle(char *file_location, int (*function)(char, char)) {
    int total = 0;
    int c;
    char p1 = 0;
    char p2 = 0;
    FILE *input = fopen(file_location, "r");
    if (input == NULL) {
        return 1;
    } else {
        do {
            c = fgetc(input);
            if (c == 'A' || c == 'B' || c == 'C') {
                p1 = c;
            } else if (c == 'X' || c == 'Y' || c == 'Z') {
                p2 = c;
            }
            if (p1 && p2 != 0) {
                total += function(p1, p2);
                p1 = 0;
                p2 = 0;
            }
        } while (c != EOF);
        fclose(input);
    }
    printf("%d\n", total);
    return 0;
}

int main() {
    if (puzzle((char *)"puzzle_input_test.txt", &calculate_score) == 1) {
        printf("error");
    }
    if (puzzle((char *)"puzzle_input.txt", &calculate_score) == 1) {
        printf("error");
    }
    if (puzzle((char *)"puzzle_input.txt", &calculate_score2) == 1) {
        printf("error");
    }
    return 0;
}