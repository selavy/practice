#include <catch2/catch.hpp>
#include <vector>
#include <utility>
#include <unordered_set>

// naive solution: set
int find_dup1(std::vector<int> vs) {
    std::unordered_set<int> s;
    for (int v : vs) {
        if (s.find(v) != s.end()) {
            return v;
        } else {
            s.insert(v);
        }
    }
    return -1;
}

int find_dup2(std::vector<int> vs) {
    std::vector<bool> seen(vs.size(), false);
    for (int v : vs) {
        if (seen[v]) {
            return v;
        }
        seen[v] = true;
    }
    return -1;
}

TEST_CASE("Find Duplicate", "[duplicate]") {
    std::vector<std::pair<std::vector<int>, int>> test_cases = {
        { { 1, 2, 3, 4, 4 }, 4 },
        { { 1, 4, 3, 4, 2 }, 4 },
        { { 1, 1, 3, 2, 4 }, 1 },
        { { 0 },            -1 },
    };

    for (auto& tc : test_cases) {
        auto& input = tc.first;
        auto expected = tc.second;

        SECTION("Solution #1") {
            auto result = find_dup1(input);
            REQUIRE(result == expected);
        }

        SECTION("Solution #2") {
            auto result = find_dup2(input);
            REQUIRE(result == expected);
        }
    }
}
