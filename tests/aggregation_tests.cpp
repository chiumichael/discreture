#include "Combinations.hpp"
#include "IndexedView.hpp"
#include "Permutations.hpp"
#include "generate_strings.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

template <typename AggView, typename Container, typename IndexContainer>
void check_indexed_view(const AggView& A,
                        const Container& T,
                        const IndexContainer& X)
{
    ASSERT_EQ(A.size(), X.size());
    for (int i = 0; i < A.size(); ++i)
    {
        ASSERT_EQ(A[i], T[X[i]]);
    }
}

TEST(AggViews, CreationAndSanity)
{
    std::vector<int> tonto = {0, 10, 20, 30, 40, 50, 60, 70};
    std::array<int, 5> indices = {{0, 1, 5, 2, 5}};
    auto T = dscr::indexed_view(tonto, indices);
    ASSERT_EQ(T.size(), indices.size());
    check_indexed_view(T, tonto, indices);
}

TEST(AggViews, Combinations)
{
    for (int n = 0; n < 10; ++n)
    {
        std::vector<std::string> total = generate_random_strings(n);
        auto X = dscr::combinations(n, n/2);

        for (auto& x : X)
        {
            auto T = dscr::indexed_view(total, x);

            check_indexed_view(T, total, x);
        }
    }
}

TEST(AggViews, Permutations)
{
    for (int n = 0; n < 9; ++n)
    {
        auto total = generate_random_strings(n);
        auto P = dscr::permutations(n);
        for (auto& p : P)
        {
            auto T = dscr::indexed_view(total, p);

            check_indexed_view(T, total, p);
        }
    }
}
