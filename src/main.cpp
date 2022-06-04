#include "vector_space_model.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<string> fnames(argv + 1, argv + argc);
    auto docnum = [](string const &str) -> int {
        auto i = str.find_first_of("/") + 1;
        return std::stoi(str.substr(i, str.find_last_of(".") - i));
    };
    std::sort(fnames.begin(), fnames.end(),
              [docnum](string const &a, string const &b) -> bool {
                  return docnum(a) < docnum(b);
              });

    VectorSpaceModel vsm(fnames, 0.001);
    std::cout << "> ";
    for (string q; std::getline(std::cin, q); std::cout << "> ") {
        auto ans = vsm.answer(q);
        std::sort(ans.begin(), ans.end(),
                  [docnum](auto const &a, auto const &b) -> bool {
                      return docnum(a.second) < docnum(b.second);
                  });
        for (auto [score, fname] : ans) {
            std::cout << score << ' ' << fname << '\n';
        }
    }
}