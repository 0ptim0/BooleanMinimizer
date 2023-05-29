#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <vector>

#include "../booleanminimizer.h"

using namespace std;

TEST(Calculation, Onedimensional_4x4) {
    vector<vector<int8_t>> input = {
        {0, 0, 0, 1}, {0, 0, 1, 1}, {1, 0, 1, 0}, {1, 1, 1, 0}};
    vector<vector<int8_t>> output = {{1}, {1}, {1}, {1}};

    EXPECT_EQ(input.size(), output.size());

    BooleanMinimizer boolean_minimizer(input, output);
    auto calc = boolean_minimizer.calculate();
    // for (auto &a : calc) {
    //     cout << endl << a.toStdString() << endl << endl;
    // }
    EXPECT_EQ(calc[0], QString("Y1 = X̄1X̄2X4 + X1X3X̄4"));
}

TEST(Calculation, Onedimensional_4x7) {
    vector<vector<int8_t>> input = {{0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
                                    {0, 1, 1, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}};
    vector<vector<int8_t>> output = {{1}, {1}, {1}, {1}, {1}, {1}};

    EXPECT_EQ(input.size(), output.size());

    BooleanMinimizer boolean_minimizer(input, output);
    auto calc = boolean_minimizer.calculate();
    // for (auto &a : calc) {
    //     cout << endl << a.toStdString() << endl << endl;
    // }
    EXPECT_EQ(calc[0], QString("Y1 = X̄1X̄2X4 + X3X̄4"));
}

TEST(Calculation, Multidimensional_4x6x3) {
    vector<vector<int8_t>> input = {{0, 0, 1, 0}, {0, 0, 0, 1}, {1, 0, 1, 0},
                                    {1, 0, 0, 1}, {0, 1, 1, 1}, {0, 1, 0, 0}};
    vector<vector<int8_t>> output = {{1, 0, 1}, {1, 1, 0}, {1, 0, 0},
                                     {1, 1, 0}, {1, 0, 1}, {1, 1, 1}};

    EXPECT_EQ(input.size(), output.size());

    BooleanMinimizer boolean_minimizer(input, output);
    auto calc = boolean_minimizer.calculate();
    // for (auto &a : calc) {
    //     cout << endl << a.toStdString() << endl << endl;
    // }
    EXPECT_EQ(calc[0], QString("Y1 = X̄1X2X̄3X̄4 + X̄1X2X3X4 + X̄2X̄3X4 + X̄2X3X̄4"));
    EXPECT_EQ(calc[1], QString("Y2 = X̄1X2X̄3X̄4 + X̄2X̄3X4"));
    EXPECT_EQ(calc[2], QString("Y3 = X̄1X̄2X3X̄4 + X̄1X2X̄3X̄4 + X̄1X2X3X4"));
}
