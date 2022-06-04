#ifndef __DOCUMENT_HPP__
#define __DOCUMENT_HPP__

#include "util.hpp"

#include <unordered_set>

class Document {
    string name_;
    double norm_ = 0.0;
    size_t totalTerms_ = 0UL;
    std::vector<double> vec;

public:
    Document(string const &fname, std::vector<string> const &dict,
             std::unordered_set<string> const &stopwords,
             std::vector<size_t> &globalFrequencies);

    string const &name() const;
    double norm() const;
    size_t totalTerms() const;

    void applyIDF(std::vector<double> const &idf);

    double &operator[](size_t i);
    double operator[](size_t i) const;
};

#endif // __DOCUMENT_HPP__
