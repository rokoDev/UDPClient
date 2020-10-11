//
//  main.cpp
//  GTests
//
//  Created by roko on 7/22/16.
//  Copyright © 2016 roko. All rights reserved.
//

#include "GitInfo.h"
#include "UDPClient.h"
#include "Version.h"
#include "gtest/gtest.h"

TEST(TestUDPClientVersion, GitInfoTest)
{
    std::cout << "[          ] branch: " << UDPClient::GitInfo::branch()
              << '\n';
    std::cout << "[          ] SHA1: " << UDPClient::GitInfo::SHA1() << '\n';
    const std::string isDirty = UDPClient::GitInfo::isDirty()
                                    ? std::string("true")
                                    : std::string("false");
    std::cout << "[          ] IS_DIRTY: " << isDirty << std::endl;
    ASSERT_EQ(0, 0);
}

TEST(TestUDPClientVersion, VersionTest)
{
    std::cout << "[          ] UDPClient Version: " << UDPClient::Version::str()
              << std::endl;
    ASSERT_EQ(0, 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
