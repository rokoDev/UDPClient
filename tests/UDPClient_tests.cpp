//
//  main.cpp
//  GTests
//
//  Created by roko on 7/22/16.
//  Copyright © 2016 roko. All rights reserved.
//

#include "UDPClient.h"
#include "gtest/gtest.h"

TEST(TestGroup1, Test1) { ASSERT_EQ(0, 0); }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
