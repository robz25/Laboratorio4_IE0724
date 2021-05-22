#include "gtest/gtest.h"

#include "Util.hpp"


// Positive testing: use valid input parameter: status should be 0
TEST(Util, positive) {
    int status = false;
    status = Util::isInt("5");
    EXPECT_EQ(status, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
