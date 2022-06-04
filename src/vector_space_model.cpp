#include "vector_space_model.hpp"

#include "word_processing.hpp"

#include <algorithm>
#include <cmath> // std::sqrt

using VSM = VectorSpaceModel;

std::unordered_set<string> const VSM::stopwords =
    []() -> std::unordered_set<string> {
    auto tokens = tokenize("Stopword-List.txt", {});
    return {tokens.begin(), tokens.end()};
}();

VSM::VectorSpaceModel(std::vector<string> const &fnames, double alpha) :
    alpha(alpha), numDocs(fnames.size()) {
    buildVocabulary(fnames);
    buildDocuments(fnames);
}

void VSM::buildVocabulary(std::vector<string> const &fnames) {
    dict.reserve(numDocs * 300);
    for (auto const &fname : fnames) {
        ranges::copy(tokenize(fname, stopwords), std::back_inserter(dict));
    }
    ranges::sort(dict);
    auto [first, last] = ranges::unique(dict);
    dict.erase(first, last);
    dict.shrink_to_fit();

    frequencies.resize(dict.size(), 0UL);
    idf.resize(dict.size(), 0.0);
}

void VSM::buildDocuments(std::vector<string> const &fnames) {
    docs.reserve(numDocs);

    auto makeDoc = [this](string const &fname) -> Document {
        return {fname, dict, stopwords, frequencies};
    };
    ranges::transform(fnames, std::back_inserter(docs), makeDoc);

    for (auto const &doc : docs) {
        for (auto i : rv::iota(0UL, dict.size())) {
            idf.at(i) += doc[i] != 0.0;
        }
    }

    for (auto &i : idf) {
        // i = std::log10(static_cast<double>(numDocs) / i);
        i = std::log10(static_cast<double>(numDocs) / i);
    }

    for (auto &doc : docs) {
        doc.applyIDF(idf);
    }
}

#include <iostream>

std::vector<std::pair<double, string>> VSM::answer(string const &qs) const {
    Query q(qs, dict, idf);

    using ScoredDoc = std::pair<double, Document const *>;
    auto mp = [](Document const &doc) -> ScoredDoc { return {0.0, &doc}; };

    std::vector<ScoredDoc> result;
    result.reserve(numDocs);

    ranges::transform(docs, std::back_inserter(result), mp);

    for (auto [token, freq] : q) {
        auto idx = ranges::distance(ranges::begin(dict),
                                    ranges::lower_bound(dict, token));
        for (auto &[score, doc] : result) {
            score += (*doc)[idx] * freq;
        }
    }
    for (auto &[score, doc] : result) {
        score /= std::sqrt(doc->norm() * q.norm());
    }

    auto [first, last] = ranges::remove_if(
        result, [this](double score) { return score < alpha; },
        &ScoredDoc::first);
    result.erase(first, last);
    ranges::sort(result);

    std::vector<std::pair<double, string>> ans;
    ans.reserve(result.size());
    ranges::transform(result | rv::reverse, std::back_inserter(ans),
                      [](ScoredDoc const &p) {
                          return std::make_pair(p.first, p.second->name());
                      });
    return ans;
}