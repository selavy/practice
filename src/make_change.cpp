#include <catch2/catch.hpp>
#include <vector>
#include <utility>
#include <cassert>
#include <set>

int make_change1(int S[], int n, int N)
{
	if (N == 0)
		return 1;
	if (N < 0 || n <= 0)
		return 0;

    int res = make_change1(S, n    , N - S[n-1]);
    res    += make_change1(S, n - 1, N);
	return res;
}

template <class Iter>
int make_change2(Iter first, Iter last, int value) {
    if (value < 0 || (first == last)) {
        return 0;
    }
    assert(first < last);
    if (value == 0) {
        return 1;
    }
    int result = make_change2(first, last, value - *first);
    result    += make_change2(first + 1, last, value);
    return result;
}

struct TestCase {
    std::vector<int> coins;
    int              value;
    int              ways;
};

TEST_CASE("Make change", "[change]") {
    std::vector<TestCase> test_cases = {
        { { 1, 3, 5, 7 }, 8, 6 },
        { { 1, 2, 3 },    4, 4 },
    };

    for (size_t i = 0; i < test_cases.size(); ++i) {
        auto& coins = test_cases[i].coins;
        auto value = test_cases[i].value;
        auto ways = test_cases[i].ways;

        SECTION("Solution #1") {
            auto result = make_change1(coins.data(), coins.size(), value);
            REQUIRE(result == ways);
        }

        SECTION("Solution #2") {
            auto result = make_change2(coins.begin(), coins.end(), value);
            REQUIRE(result == ways);
        }
    }
}
