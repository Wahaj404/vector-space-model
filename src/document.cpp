#include "document.hpp"

#include "word_processing.hpp"

#include <algorithm>

Document::Document(string const &fname, std::vector<string> const &dict,
                   std::unordered_set<string> const &stopwords,
                   std::vector<size_t> &globalFrequencies) :
    name_(fname),
    vec(dict.size(), 0UL) {
    for (auto const &token : tokenize(fname, stopwords)) {
        auto i =
            ranges::distance(dict.begin(), ranges::lower_bound(dict, token));
        ++vec[i];
        ++globalFrequencies[i];
    }
    for (auto freq : vec) {
        norm_ += freq * freq;
        totalTerms_ += freq != 0.0;
    }
}

string const &Document::name() const {
    return name_;
}

double Document::norm() const {
    return norm_;
}

size_t Document::totalTerms() const {
    return totalTerms_;
}

double &Document::operator[](size_t i) {
    return vec.at(i);
}

double Document::operator[](size_t i) const {
    return vec.at(i);
}

void Document::applyIDF(std::vector<double> const &idf) {
    for (auto i : rv::iota(0UL, vec.size())) {
        vec.at(i) *= idf.at(i);
        // norm_ += vec.at(i) * vec.at(i);
    }
}
