#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

char *dawn_shift_args(int *argc, char ***argv) {
    assert(*argc > 0);
    char *arg = **argv;
    (*argv)++;
    (*argc)--;
    return arg;
}

bool is_xmas(std::vector<std::string>& word_search, int pos_i, int pos_j) {
    char d1 = word_search[pos_i - 1][pos_j - 1];
    char d2 = word_search[pos_i + 1][pos_j + 1];

    char o1 = word_search[pos_i - 1][pos_j + 1];
    char o2 = word_search[pos_i + 1][pos_j - 1];

    return (d1 == 'M' && d2 == 'S' && o1 == 'M' && o2 == 'S')
        || (d1 == 'M' && d2 == 'S' && o1 == 'S' && o2 == 'M')
        || (d1 == 'S' && d2 == 'M' && o1 == 'M' && o2 == 'S')
        || (d1 == 'S' && d2 == 'M' && o1 == 'S' && o2 == 'M');
}

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        std::cout << "Usage: " << program << " <word_search.txt>\n";
        return 1;
    }

    char *fp = dawn_shift_args(&argc, &argv);
    std::ifstream fs(fp);

    std::vector<std::string> word_search;
    for (std::string line; getline(fs, line);) {
        word_search.push_back(line);
    }

    size_t xmas_count = 0;
    size_t line_count = word_search.size();
    size_t line_len = word_search[0].size();
    for (size_t i = 1; i < line_count - 1; i++) {
        for (size_t j = 1; j < line_len - 1; j++) {
            if (word_search[i][j] == 'A' && is_xmas(word_search, i, j)) {
                xmas_count++;
            }
        }
    }

    std::cout << "X-MAS occurs " << xmas_count << " times.\n";
}
