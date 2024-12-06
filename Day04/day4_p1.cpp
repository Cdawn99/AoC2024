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

size_t xmas_count(std::vector<std::string>& word_search, int pos_i, int pos_j) {
    const char xmas[] = "XMAS";

    size_t count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dy == 0 && dx == 0) continue;
            bool is_xmas = true;
            for (int k = 1; k <= 3; k++) {
                int i = pos_i + k * dx;
                int j = pos_j + k * dy;
                if (i < 0 || j < 0 || static_cast<size_t>(i) >= word_search.size() || static_cast<size_t>(j) >= word_search[0].size()) {
                    is_xmas = false;
                    break;
                }
                if (word_search[i][j] != xmas[k]) is_xmas = false;
            }
            if (is_xmas) count++;
        }
    }
    return count;
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
    for (size_t i = 0; i < line_count; i++) {
        for (size_t j = 0; j < line_len; j++) {
            if (word_search[i][j] == 'X') {
                xmas_count += ::xmas_count(word_search, i, j);
            }
        }
    }

    std::cout << "XMAS occurs " << xmas_count << " times.\n";
}
