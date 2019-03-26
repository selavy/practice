#include <catch2/catch.hpp>
#include <vector>
#include <algorithm>


// solution #1: sort
std::vector<int> sort_binary_array1(std::vector<int> input) {
    std::sort(input.begin(), input.end());
    return input;
}

// solution #2: counting
std::vector<int> sort_binary_array2(std::vector<int> input) {
    std::vector<int> rv;
    int ones = 0;
    for (int it : input) {
        if (it == 0) {
            rv.push_back(0);
        } else {
            ++ones;
        }
    }
    rv.insert(rv.end(), ones, 1);
    return rv;
}

// solution #3: fill
std::vector<int> sort_binary_array3(std::vector<int> input) {
    std::vector<int> rv(input.size(), 1);
    auto cur = rv.begin();
    for (int it : input) {
        if (it == 0) {
            *cur++ = 0;
        }
    }
    return rv;
}

TEST_CASE("SortBinaryArray", "[binarray]") {
    std::vector<std::pair<std::vector<int>, std::vector<int>>> test_cases = {
        { { 0, 1, 1, 0 },             { 0, 0, 1, 1 } },
        { { 1, 0, 1, 0, 1, 0, 0, 1 }, { 0, 0, 0, 0, 1, 1, 1, 1 } },
        { { 1, 0 },                   { 0, 1 } },
        { { 0, 1 },                   { 0, 1 } },
        { { 0 },                      { 0 } },
        { { 1 },                      { 1 } },
    };

    for (auto& tc : test_cases) {
        auto& input = tc.first;
        auto& expected = tc.second;

        SECTION("SortBinArray #1") {
            auto result = sort_binary_array1(input);
            REQUIRE(result == expected);
        }

        SECTION("SortBinArray #2") {
            auto result = sort_binary_array2(input);
            REQUIRE(result == expected);
        }

        SECTION("SortBinArray #3") {
            auto result = sort_binary_array3(input);
            REQUIRE(result == expected);
        }
    }
}
