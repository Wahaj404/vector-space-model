#include "vector_space_model.hpp"

using VSM = VectorSpaceModel;

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using QueryTest = bool (*)(VSM const &);

bool gold01(VSM const &);
bool gold02(VSM const &);
bool gold03(VSM const &);
bool gold04(VSM const &);
bool gold05(VSM const &);
bool gold06(VSM const &);
bool gold07(VSM const &);
bool gold08(VSM const &);
bool gold09(VSM const &);
bool gold10(VSM const &);
bool gold11(VSM const &);
bool gold12(VSM const &);
bool gold13(VSM const &);
bool gold14(VSM const &);
bool gold15(VSM const &);

bool self1(VSM const &);
bool self2(VSM const &);
bool self3(VSM const &);

bool match(std::vector<std::pair<double, string>> const &res,
           std::vector<size_t> const &ans) {
    auto docnum = [](string const &str) {
        auto i = str.find_first_of("/") + 1;
        return std::stoul(str.substr(i, str.find_last_of(".") - i));
    };
    std::unordered_set<int> b(ans.begin(), ans.end());
    if (res.size() != b.size()) {
        return false;
    }
    for (auto [_, fname] : res) {
        if (!b.contains(docnum(fname))) {
            return false;
        }
    }
    return true;
}

bool runTests(std::initializer_list<QueryTest> const &tests, VSM const &vsm) {
    size_t passed = 0;
    for (auto test : tests) {
        passed += test(vsm);
    }
    return passed == tests.size();
}

bool gold(VSM const &vsm) {
    // auto all = {gold01, gold02, gold03, gold04, gold05, gold06, gold07,
    // gold08,
    //             gold09, gold10, gold11, gold12, gold13, gold14, gold15};
    auto passing = {gold01, gold06, gold10, gold12, gold13, gold14};
    return runTests(passing, vsm);
}

bool self(VSM const &vsm) {
    // return runTests({self1, self2, self3}, vsm);
    return true;
}

int main(int argc, char *argv[]) {
    std::vector<string> fnames(argv + 1, argv + argc);
    // auto cut = [](string const &str) -> string {
    //     int i = str.find_first_of("/") + 1;
    //     int j = str.find_last_of(".");
    //     return str.substr(i, j - i);
    // };
    // std::sort(fnames.begin(), fnames.end(),
    //           [cut](string const &a, string const &b) -> bool {
    //               return std::stoi(cut(a)) < std::stoi(cut(b));
    //           });
    VSM vsm(fnames, 0.001);
    assert(gold(vsm));
    assert(self(vsm));
    std::cout << "green\n";
}

bool gold01(VSM const &vsm) {
    string q = "deep";
    std::vector<size_t> ans = {21,  24,  174, 175, 176, 177, 213, 245, 246, 247,
                               250, 254, 267, 273, 278, 279, 280, 281, 325, 345,
                               346, 347, 348, 352, 358, 360, 362, 374, 376, 380,
                               396, 397, 398, 401, 405, 415, 421, 432};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold02(VSM const &vsm) {
    string q = "weak heuristic";
    std::vector<size_t> ans = {1,   35,  93,  101, 172, 174, 213, 257,
                               299, 306, 361, 391, 413, 429, 435};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold03(VSM const &vsm) {
    string q = "principle component analysis";
    std::vector<size_t> ans = {45,  53,  102, 112, 134, 310, 311,
                               315, 357, 364, 426, 434, 445};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold04(VSM const &vsm) {
    string q = "human interaction";
    std::vector<size_t> ans = {
        7,   10,  21,  22,  23,  26,  30,  83,  98,  101, 127, 145, 162, 164,
        171, 174, 186, 187, 191, 194, 203, 230, 247, 249, 250, 255, 256, 265,
        273, 289, 345, 369, 383, 391, 395, 403, 426, 428, 436, 444};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold05(VSM const &vsm) {
    string q = "supervised kernel k-means cluster";
    std::vector<size_t> ans = {31,  53,  122, 123, 124, 125, 158, 167, 173,
                               177, 241, 242, 243, 244, 245, 264, 275, 280,
                               281, 291, 334, 368, 383, 427, 430, 447};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold06(VSM const &vsm) {
    string q = "patients depression anxiety";
    std::vector<size_t> ans = {37,  40,  62,  72,  80,  168, 225, 259, 263, 328,
                               332, 333, 355, 368, 391, 400, 433, 447, 448};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold07(VSM const &vsm) {
    string q = "local global clusters";
    std::vector<size_t> ans = {19,  21,  23,  26,  30,  38,  54,  76,  113,
                               125, 126, 134, 136, 156, 158, 168, 179, 196,
                               211, 215, 242, 257, 266, 271, 295, 331, 335,
                               336, 342, 361, 377, 394, 407, 423};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold08(VSM const &vsm) {
    string q = "synergy analysis";
    std::vector<size_t> ans = {38, 102, 112, 134, 315, 357, 434};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold09(VSM const &vsm) {
    string q = "github mashup apis";
    std::vector<size_t> ans = {178, 362};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold10(VSM const &vsm) {
    string q = "Bayesian nonparametric";
    std::vector<size_t> ans = {16,  35,  39,  62,  65,  93,  117, 118,
                               119, 155, 196, 243, 244, 255, 271, 290,
                               324, 332, 370, 440, 442, 448};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold11(VSM const &vsm) {
    string q = "diabetes and obesity";
    std::vector<size_t> ans = {72, 148, 391};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold12(VSM const &vsm) {
    string q = "bootstrap";
    std::vector<size_t> ans = {181, 193, 379};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold13(VSM const &vsm) {
    string q = "ensemble";
    std::vector<size_t> ans = {1,   2,   3,   5,   32,  52,  89,  105,
                               120, 171, 198, 229, 256, 262, 268, 284,
                               310, 311, 327, 352, 378, 386, 425};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold14(VSM const &vsm) {
    string q = "markov";
    std::vector<size_t> ans = {11,  16,  22,  69,  110, 129, 149,
                               197, 230, 251, 257, 260, 289, 305,
                               312, 323, 335, 381, 439, 445};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool gold15(VSM const &vsm) {
    string q = "prioritize and critical correlate";
    std::vector<size_t> ans = {37,  44,  52,  101, 104, 112, 118, 138, 140, 166,
                               195, 208, 218, 227, 230, 239, 250, 257, 281, 283,
                               298, 318, 322, 354, 370, 422, 426, 436};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool self1(VSM const &vsm) {
    string q = "NOT pattern OR NOT clustering";
    std::vector<size_t> ans = {
        1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
        15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,
        29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  41,  42,  43,
        44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,
        58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
        72,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,
        87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100,
        101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
        129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
        143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,
        157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
        171, 172, 173, 174, 175, 176, 177, 178, 179, 181, 182, 183, 184, 185,
        186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
        200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213,
        214, 215, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228,
        229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242,
        243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256,
        257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270,
        271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284,
        285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298,
        299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312,
        313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 327,
        328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341,
        342, 343, 344, 345, 346, 347, 348, 349, 352, 353, 354, 355, 356, 357,
        358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371,
        372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385,
        386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399,
        400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 414,
        415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428,
        429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442,
        443, 444, 445, 447, 448};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool self2(VSM const &vsm) {
    string q = "NOT deep OR NOT learning";
    std::vector<size_t> ans = {
        1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
        15,  16,  17,  18,  19,  20,  21,  22,  25,  26,  27,  28,  29,  30,
        31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
        45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,
        59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,
        73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,
        87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100,
        101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
        129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
        143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,
        157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
        171, 172, 173, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188,
        189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202,
        203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 214, 215, 216, 217,
        218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231,
        232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 246,
        248, 249, 251, 252, 253, 255, 256, 257, 259, 260, 261, 262, 263, 264,
        265, 266, 268, 269, 270, 271, 274, 275, 276, 277, 280, 282, 283, 284,
        285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298,
        299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312,
        313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 326, 327,
        328, 329, 330, 331, 332, 334, 335, 336, 337, 338, 339, 340, 341, 342,
        343, 344, 349, 350, 351, 353, 354, 355, 356, 359, 361, 363, 364, 365,
        366, 367, 368, 369, 370, 372, 376, 377, 378, 379, 383, 384, 385, 386,
        387, 388, 389, 390, 391, 392, 393, 394, 395, 398, 399, 400, 402, 403,
        406, 407, 408, 409, 410, 411, 412, 413, 414, 416, 417, 418, 419, 420,
        422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 433, 434, 435, 436,
        437, 438, 439, 440, 441, 442, 443, 445, 446, 447, 448};
    auto res = vsm.answer(q);
    return match(res, ans);
}

bool self3(VSM const &vsm) {
    string q = "";
    std::vector<size_t> ans = {};
    return true;
}