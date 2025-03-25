/**
 * @file CraneState.h
 * @author Daniel Reeves (dtr@vt.edu)
 * @brief Defines the state classes for the crane.
 * @brief The state classes are: LowPower, NoConnection, Both
 * @brief They're all in the same file because their class transitions are dependent on each other.
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef CRANESTATE_H
#define CRANESTATE_H
#include "Crane.h"

class CraneState
{
public:
    virtual ~CraneState() = default;
    virtual void checkPower(Crane &c) = 0;
    virtual void sendData(Crane &c) = 0;
    virtual void winchControl(Crane &c) = 0;
    virtual void listen(Crane &c) = 0;
};

/*
 Normal State Class
 TODO: Bring in the FSM code
*/
class Normal : public CraneState
{
public:
    static Normal &getInstance()
    {
        static Normal instance;
        return instance;
    }

    void checkPower(Crane &c) override
    {
        // Implementation for Normal state
    }

    void sendData(Crane &c) override
    {
        // Implementation for Normal state
    }

    void winchControl(Crane &c) override;

    void listen(Crane &c) override
    {
        // TODO: Implement normal state listening functionality
        // TODO: Check for incoming commands and messages
    }

    void changeToLowPower(Crane &c)
    {
        // Perform any necessary cleanup before state change
        c.changeState(LowPower::getInstance());
    }

private:
    Normal() {}
    Normal(const Normal &) = delete;
    Normal &operator=(const Normal &) = delete;
};

/*
 LowPower State Class
*/
class LowPower : public CraneState
{
public:
    static LowPower &getInstance()
    {
        static LowPower instance;
        return instance;
    }

    void checkPower(Crane &c) override
    {
        // Implementation for LowPower state
    }

    void sendData(Crane &c) override
    {
        // Implementation for LowPower state
    }

    void winchControl(Crane &c) override;

    void listen(Crane &c) override
    {
        // TODO: Implement low power state listening functionality
        // TODO: Minimize power consumption while listening
    }

private:
    LowPower() {}
    LowPower(const LowPower &) = delete;
    LowPower &operator=(const LowPower &) = delete;
};

/*
 NoConnection State Class
*/
class NoConnection : public CraneState
{
public:
    static NoConnection &getInstance()
    {
        static NoConnection instance;
        return instance;
    }

    void checkPower(Crane &c) override
    {
        // Implementation for NoConnection state
    }

    void sendData(Crane &c) override
    {
        // Implementation for NoConnection state
    }

    void winchControl(Crane &c) override;

    void listen(Crane &c) override
    {
        // TODO: Implement no connection state listening functionality
        // TODO: Periodically check for connection restoration
    }

    void timerWinchControl(Crane &c);

private:
    NoConnection() {}
    NoConnection(const NoConnection &) = delete;
    NoConnection &operator=(const NoConnection &) = delete;
};

/*
 Both State Class (Low Power and No Connection)
*/
class Both : public CraneState
{
public:
    static Both &getInstance()
    {
        static Both instance;
        return instance;
    }

    void checkPower(Crane &c) override
    {
        // Implementation for Both state
    }

    void sendData(Crane &c) override
    {
        // Implementation for Both state
    }

    void winchControl(Crane &c) override;

    void listen(Crane &c) override;

private:
    Both() {}
    Both(const Both &) = delete;
    Both &operator=(const Both &) = delete;
};

#endif // CRANESTATE_H