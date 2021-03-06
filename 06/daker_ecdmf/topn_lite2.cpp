/*
 * top_lite.cpp
 * Emiliano Firmino <emiliano.firmino@gmail.com>
 * Daker Fernandes
 *
 * Copyright (C) 2015
 *
 * Distributed under terms of the MIT license.
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unistd.h>

void topn(char * filename) {
    std::fstream file;
    file.open(filename, std::fstream::in);

    std::unordered_map<std::string, unsigned int> dict;

    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        auto value = dict.find(word);
        if (value == dict.end() )
            dict.insert(std::make_pair(word, 1));
        else
            dict[word] = value->second + 1;
    }


    std::vector<std::pair<std::string, unsigned int>> list(dict.begin(), dict.end());

    std::sort(list.begin(), list.end(),
        [](const std::pair<std::string, unsigned int>& lhs,
           const std::pair<std::string, unsigned int>& rhs) {
               return lhs.second > rhs.second;
        });

    std::priority_queue<std::pair<unsigned int, std::string> > heap;
    for (const auto &w : list) {
        std::pair<unsigned int, std::string> p;
        p.first = w.second;
        p.second = w.first;
        heap.push(p);
    }

    for (int i = 0; i < 10; i++)
    {
        std::cout << heap.top().second << std::endl;
        heap.pop();
    }
}

int main(int argc, char ** argv) {
    int id = 0;
    bool is_parent = true;
    for (id = 1; id < argc - 1; id++) {
        int pid = fork();
        if (pid == 0) {
            // child
            is_parent = false;
            break;
        } else if (pid > 0) {
            // parent
        }
    }

    std::cout << "proc with id " << id << "\n";
    topn(argv[id]);

    if (is_parent) {
        for (int i = 0; i < id - 1; i++) {
            int status;
            wait(&status);
            std::cout << "wait return of " << i << "\n";
        }
    }
}
