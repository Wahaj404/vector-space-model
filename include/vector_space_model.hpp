#ifndef __VECTOR_SPACE_MODEL_HPP__
#define __VECTOR_SPACE_MODEL_HPP__

#include "document.hpp"
#include "query.hpp"
#include "util.hpp"

#include <unordered_set>

class VectorSpaceModel {
    static std::unordered_set<string> const stopwords;

    double const alpha;
    size_t const numDocs;

    std::vector<Document> docs;
    std::vector<string> dict;
    std::vector<size_t> frequencies;
    std::vector<double> idf;

    void buildVocabulary(std::vector<string> const &fnames);
    void buildDocuments(std::vector<string> const &fnames);

public:
    VectorSpaceModel(std::vector<string> const &fnames, double alpha);

    std::vector<std::pair<double, string>> answer(string const &q) const;
};

#endif // __VECTOR_SPACE_MODEL_HPP__
