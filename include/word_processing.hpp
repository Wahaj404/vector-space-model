#ifndef __WORD_PROCESSING_HPP__
#define __WORD_PROCESSING_HPP__

#include "util.hpp"

#include <unordered_set>

void stem(string &str);

std::vector<string> tokenize(string const &sentence);

std::vector<string> tokenize(string const &fname,
                             std::unordered_set<string> const &stopwords);

#endif // __WORD_PROCESSING_HPP__
