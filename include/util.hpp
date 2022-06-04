#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <ranges>
#include <string>
#include <vector>

namespace ranges = std::ranges;
namespace rv = ranges::views;

using std::size_t, std::string;

template <typename T, typename R>
std::vector<T> rangeToVector(R &&r) {
    return {ranges::begin(r), ranges::end(r)};
}

#endif // __UTIL_HPP__
