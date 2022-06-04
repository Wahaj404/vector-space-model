#include "query.hpp"

#include "word_processing.hpp"

#include <algorithm>

Query::Query(string const &q, std::vector<string> const &dict,
             std::vector<double> const &idf) {
    for (auto token : tokenize(q)) {
        stem(token);
        ++frequencies[token];
    }
    for (auto &[token, freq] : frequencies) {
        auto idx =
            ranges::distance(dict.begin(), ranges::lower_bound(dict, token));
        freq *= idf.at(idx);
        norm_ += freq * freq;
    }
}

double Query::norm() const {
    return norm_;
}

Query::Iterator Query::begin() const {
    return frequencies.begin();
}

Query::Iterator Query::end() const {
    return frequencies.end();
}
