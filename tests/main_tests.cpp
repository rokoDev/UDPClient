#include <fmt/format.h>
#include <ndt/GitInfo.h>
#include <ndt/utils.h>

#include "client/GitInfo.h"
#include "client/Version.h"
#include "gtest/gtest.h"

TEST(TestClientVersion, GitInfoTest)
{
    fmt::print("[          ] branch: {}\n", client::GitInfo::branch());
    fmt::print("[          ] SHA1: {}\n", client::GitInfo::SHA1());
    const std::string isDirty =
        client::GitInfo::isDirty() ? std::string("true") : std::string("false");
    fmt::print("[          ] IS_DIRTY: {}\n\n\n", isDirty);

    fmt::print("[          ] build type: {}\n", ndt::kBuildTypeCStr);
    fmt::print("[          ] branch: {}\n", ndt::GitInfo::branch());
    fmt::print("[          ] SHA1: {}\n", ndt::GitInfo::SHA1());
    const std::string isNDTDirty =
        ndt::GitInfo::isDirty() ? std::string("true") : std::string("false");
    fmt::print("[          ] IS_DIRTY: {}\n", isNDTDirty);

    ASSERT_EQ(0, 0);
}

TEST(TestClientVersion, VersionTest)
{
    fmt::print("[          ] client Version: {}\n", client::Version::str());
    ASSERT_EQ(0, 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
