#include "word_processing.hpp"

#include "olestem/stemming/english_stem.h"

#include <fstream>
#include <sstream>

string wtos(std::wstring const &ws) {
    return {ws.cbegin(), ws.cend()};
}

std::wstring stow(string const &s) {
    return {s.cbegin(), s.cend()};
}

void trimPunctuationRight(std::wstring &str) {
    static std::unordered_set<wchar_t> const punct = {L',', L'.'};
    while (!str.empty() && punct.contains(str.back())) {
        str.pop_back();
    }
}

void toLower(std::wstring &str) {
    std::transform(str.begin(), str.end(), str.begin(), towlower);
}

std::vector<std::wstring> splitOnPunctuation(std::wstring &str) {
    static auto punct = L"(),.-/";

    std::vector<std::wstring> ret;
    size_t i = 0, j = 0;
    while ((j = str.find_first_of(punct, i)) != string::npos) {
        if (j - i > 1) {
            ret.push_back(str.substr(i, j - i));
        }
        i = j + 1;
    }
    if (str.length() - i > 1) {
        ret.push_back(str.substr(i));
    }
    return ret;
}

static stemming::english_stem stemmer;

std::vector<std::wstring> normalize(std::wstring &str) {
    toLower(str);
    trimPunctuationRight(str);
    auto words = splitOnPunctuation(str);
    for (auto &word : words) {
        stemmer(word);
    }
    return words;
}

void stem(string &str) {
    auto ws = stow(str);
    stemmer(ws);
    str = wtos(ws);
}

std::vector<string> tokenize(std::wistream &stream,
                             std::unordered_set<string> const &stopwords) {
    std::vector<string> ret;
    std::wstring word;
    while (stream >> word) {
        for (auto const &ws : normalize(word)) {
            ret.emplace_back(ws.begin(), ws.end());
        }
    }
    std::erase_if(ret, [stopwords](string const &str) -> bool {
        return stopwords.contains(str);
    });
    return ret;
}

std::vector<string> tokenize(string const &sentence) {
    std::wstringstream ss(stow(sentence));
    return tokenize(ss, {});
}

std::vector<string> tokenize(string const &fname,
                             std::unordered_set<string> const &stopwords) {
    std::wifstream file(fname);
    return tokenize(file, stopwords);
}
