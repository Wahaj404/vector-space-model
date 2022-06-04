#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include "util.hpp"

#include <unordered_map>

class Query {
    using MapT = std::unordered_map<string, double>;
    using Iterator = MapT::const_iterator;

    double norm_ = 0.0;
    MapT frequencies;

public:
    Query(string const &q, std::vector<string> const &dict,
          std::vector<double> const &idf);

    double norm() const;

    auto size() const {
        return frequencies.size();
    }

    Iterator begin() const;
    Iterator end() const;
};

#endif // __QUERY_HPP__
