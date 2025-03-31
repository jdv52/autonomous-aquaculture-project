#include "CraneState.h"
#include "Crane.h"
#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

// Test normal state transitions
void test_state_transitions()
{
    Crane crane(new NoConnection);
    TEST_ASSERT_EQUAL_STRING("No Connection", crane.getState().c_str());
    // Test transition to LowPower
    crane.transitionTo(new Normal);
    TEST_ASSERT_EQUAL_STRING("Normal", crane.getState().c_str());
    crane.transitionTo(new LowPower);
    TEST_ASSERT_EQUAL_STRING("Low Power", crane.getState().c_str());
    crane.transitionTo(new Both);
    TEST_ASSERT_EQUAL_STRING("Both", crane.getState().c_str());
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_state_transitions);

    // Add more test runners here
    return UNITY_END();
}
