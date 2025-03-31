#include <unity.h>
#include "test_cranestate.h"

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_singleton_instances);
    RUN_TEST(test_normal_transitions);
    // Add more test runners here
    return UNITY_END();
}
