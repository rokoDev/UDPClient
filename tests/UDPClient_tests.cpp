#include <fmt/core.h>

#include "GitInfo.h"
#include "UDPClient.h"
#include "Version.h"
#include "gtest/gtest.h"

TEST(TestUDPClientVersion, GitInfoTest)
{
    fmt::print("[          ] branch: {}\n", UDPClient::GitInfo::branch());
    fmt::print("[          ] SHA1: {}\n", UDPClient::GitInfo::SHA1());
    const std::string isDirty = UDPClient::GitInfo::isDirty()
                                    ? std::string("true")
                                    : std::string("false");
    fmt::print("[          ] IS_DIRTY: {}\n", isDirty);
    ASSERT_EQ(0, 0);
}

TEST(TestUDPClientVersion, VersionTest)
{
    fmt::print("[          ] UDPClient Version: {}\n",
               UDPClient::Version::str());
    ASSERT_EQ(0, 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
