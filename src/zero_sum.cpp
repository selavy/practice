#include <catch2/catch.hpp>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

// naive solution: sort + linear scan
bool zero_sum1(std::vector<int> input) {
    std::sort(input.begin(), input.end());
    for (auto i = input.begin(); i != input.end(); ++i) {
        // invariant: [i, end) sorted
        // invariant: sum([0, i)) < 0
        int sum = *i;
        if (sum == 0) {
            return true;
        } else if (sum > 0) {
            // every element in range (i, end) is greater than i, therefore can't sum to 0
            return false;
        }
        for (auto j = i + 1; j != input.end(); ++j) {
            sum += *j;
            if (sum == 0) {
                return true;
            } else if (sum > 0) {
                return false;
            }

            assert(sum < 0 && "loop invariant broken");
        }
    }

    return false;
}

TEST_CASE("Zero sum", "[zero sum]") {
    std::vector<std::pair<std::vector<int>, bool>> test_cases = {
        { { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 }, true  },
        { { 1, 1, 1, 1 },                       false },
        { { 1, 2, 3, -6 },                      true  },
        { { 6, 7, 2, -1, -4 },                  false },
        { { 1, 2, 3, 4, -4, -3, -2, -1 },       true  },
    };

    for (auto& tc : test_cases) {
        auto& input = tc.first;
        auto& expected = tc.second;

        SECTION("ZeroSum1") {
            auto result = zero_sum1(input);
            REQUIRE(result == expected);
        }
    }
}
