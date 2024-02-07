#include <gtest/gtest.h>
#include <absl/flags/parse.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::absl::ParseCommandLine(argc, argv);

    auto result = RUN_ALL_TESTS();


    return result;
}
