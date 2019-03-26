#include <catch2/catch.hpp>
#include <vector>
#include <utility>

bool truth(bool cond, bool then_, bool else_) {
    return cond ? then_ : else_;
}

bool branchless_if(bool cond, bool then_, bool else_) {
    return (cond & then_) | (!cond & else_);
}

struct TestCase {
    bool cond, a, b, out;
};

TEST_CASE("Branchless if/else") {
    std::vector<TestCase> test_cases = {
        // cond,     a,     b,   out
        //----------------------------
        { false, false, false, false },
        { false, false,  true,  true },
        { false,  true, false, false },
        { false,  true,  true,  true },

        {  true, false, false, false },
        {  true, false,  true, false },
        {  true,  true, false,  true },
        {  true,  true,  true,  true },
    };

    for (auto tc : test_cases) {
        SECTION("Source of Truth") {
            auto result = truth(tc.cond, tc.a, tc.b);
            REQUIRE(result == tc.out);
        }

        SECTION("Branchless") {
            auto result = branchless_if(tc.cond, tc.a, tc.b);
            REQUIRE(result == tc.out);
        }
    }
}
