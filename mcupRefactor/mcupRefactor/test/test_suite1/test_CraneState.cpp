#include "CraneState.h"
#include "Crane.h"
#include <unity.h>

// Test normal state transitions
void test_state_transitions()
{
    Crane crane;

    // Test transition to LowPower
    crane.changeState(new Normal());
    TEST_ASSERT_EQUAL()

    // Reset and test transition to NoConnection
    crane.currentState = &normal;
    normal.changeToNoConnection(crane);
    TEST_ASSERT_EQUAL_PTR(&NoConnection::getInstance(), crane.currentState);
}

// Test singleton behavior
void test_singleton_instances()
{
    Normal &a = Normal::getInstance();
    Normal &b = Normal::getInstance();
    TEST_ASSERT_EQUAL_PTR(&a, &b);

    LowPower &lp1 = LowPower::getInstance();
    LowPower &lp2 = LowPower::getInstance();
    TEST_ASSERT_EQUAL_PTR(&lp1, &lp2);
}

// Add more test cases for other states and methods
