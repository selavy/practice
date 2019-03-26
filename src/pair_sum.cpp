#include <catch2/catch.hpp>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>


// version #1: linear scan
template <class Iter>
std::pair<Iter, Iter> pair_sum1(Iter first, Iter last, int value) {
    for (auto i = first; i != last; ++i) {
        for (auto j = i + 1; j != last; ++j) {
            if (*i + *j == value) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(last, last);
}

// version #2: sort + scan
template <class Iter>
std::pair<Iter, Iter> pair_sum2(Iter first, Iter last, int value) {
    std::sort(first, last);
    auto lo = first;
    auto hi = last - 1;
    while (lo < hi) {
        // invariant: sum in range [lo, hi] if exists
        // invariant: sorted [lo, hi], therefore *lo <= *hi
        //
        int sum = *lo + *hi;
        if (value == sum) {
            return std::make_pair(lo, hi);
        } else if (sum > value) {
            --hi;
        } else {
            ++lo;
        }
    }
    return std::make_pair(last, last);
}

// version #3: hash table + scan
template <class Iter>
std::pair<Iter, Iter> pair_sum3(Iter first, Iter last, int value) {
    std::unordered_map<int, Iter> seen;
    for (;first != last; ++first) {
        int other = value - *first;
        auto found = seen.find(other);
        if (found != seen.end()) {
            return std::make_pair(first, found->second);
        }
        seen.emplace(*first, first);
    }
    return std::make_pair(last, last);
}

TEST_CASE("Pair Sum", "[pair sum]") {
    std::vector<int> vs = { 1, 5, 2, 9, 6, 3, 7, 8, 1, 0, 8, 6, -1, -5 };

    std::vector<std::pair<int, bool>> test_cases = {
        {   6, true },
        {   9, true },
        {   3, true },
        {  10, true },
        {  20, false },
        {  21, false },
        { -10, false },
        {  -5, true },
        {   0, true },
    };

    for (auto&& tc : test_cases) {
        auto value = tc.first;
        auto expected = tc.second;

        SECTION("PairSum1") {
            auto result = pair_sum1(vs.begin(), vs.end(), value);
            if (expected) {
                REQUIRE(result.first != vs.end());
                REQUIRE(result.second != vs.end());
                REQUIRE((*result.first + *result.second) == value);
            } else {
                REQUIRE(result.first == vs.end());
                REQUIRE(result.second == vs.end());
            }
        }

        SECTION("PairSum2") {
            auto result = pair_sum2(vs.begin(), vs.end(), value);
            if (expected) {
                REQUIRE(result.first != vs.end());
                REQUIRE(result.second != vs.end());
                REQUIRE((*result.first + *result.second) == value);
            } else {
                REQUIRE(result.first == vs.end());
                REQUIRE(result.second == vs.end());
            }
        }

        SECTION("PairSum3") {
            auto result = pair_sum3(vs.begin(), vs.end(), value);
            if (expected) {
                REQUIRE(result.first != vs.end());
                REQUIRE(result.second != vs.end());
                REQUIRE((*result.first + *result.second) == value);
            } else {
                REQUIRE(result.first == vs.end());
                REQUIRE(result.second == vs.end());
            }
        }
    }
}
