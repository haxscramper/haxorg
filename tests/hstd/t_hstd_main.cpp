#include <gtest/gtest.h>
#include <fuzztest/fuzztest.h>
#include <absl/flags/parse.h>
#include <fuzztest/init_fuzztest.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::absl::ParseCommandLine(argc, argv);
    ::fuzztest::InitFuzzTest(&argc, &argv);

    auto result = RUN_ALL_TESTS();


    return result;
}
