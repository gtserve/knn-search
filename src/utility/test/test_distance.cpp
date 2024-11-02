//
// Created by Nikos Tsolkas on 1/11/2024.
//

#include <gtest/gtest.h>
#include "../utility_functions.h"
#include <cmath>

TEST(Distance, Test1)
{
    EXPECT_EQ(euclidean_distance(2,1),sqrt(3));
}