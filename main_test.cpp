#include <gtest/gtest.h>

// Include your test files here
#include "tests/worldmodel_test.cpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
