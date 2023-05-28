#include <gtest/gtest.h>

#include <cstdint>
#include <vector>
#include <iostream>

#include "../booleanminimizer.h"

using namespace std;

TEST(Calculation, Minterms_4x7) {
    vector<vector<int8_t>> input = {{0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0},
                                    {0, 0, 1, 1}, {0, 1, 1, 0}, {1, 0, 1, 0},
                                    {1, 1, 1, 0}};
    vector<vector<int8_t>> output = {{1}, {1}, {1}, {1}, {1}, {1}, {1}};
    EXPECT_EQ(input.size(), output.size());
    BooleanMinimizer boolean_minimizer(input, output);
    auto calc = boolean_minimizer.calculate();
    for (auto &a : calc) {
        std::cout << a.toStdString() << std::endl;
    }
}
