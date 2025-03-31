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

class Crane;        // Forward declaration of Crane class
class Normal;       // Forward declaration of Normal state class
class LowPower;     // Forward declaration of LowPower state class
class NoConnection; // Forward declaration of NoConnection state class
class Both;         // Forward declaration of Both state class

class CraneState
{
protected:
    std::string state;
    Crane contextRef;

public:
    // Default constructor
    CraneState() = default;
    CraneState(Crane &context)
    {
        this->state = "null";
        this->contextRef = context;
    }
    virtual ~CraneState() = default;
    virtual void checkPower(Crane &context) = 0;
    virtual void sendData(Crane &context) = 0;
    virtual void winchControl(Crane &context) = 0;
    virtual void listen(Crane &context) = 0;
    inline std::string getState() { return this->state; }
    // State transition methods
    void changeToNormal(Crane &context)
    {
        context.changeState(new Normal(context));
    }
    void changeToLowPower(Crane &context)
    {
        context.changeState(new LowPower(context));
    }
    void changeToNoConnection(Crane &context)
    {
        context.changeState(new NoConnection(context));
    }
    void changeToBoth(Crane &context)
    {
        context.changeState(new Both(context));
    }
};

/*
 Normal State Class
 TODO: Bring in the FSM code
*/
class Normal : public CraneState
{
public:
    Normal(Crane &context)
    {
        this->state = "Normal";
        this->contextRef = context;
    }
    void checkPower(Crane &context) override;
    void sendData(Crane &context) override;
    void winchControl(Crane &context) override;
    void listen(Crane &context) override;
};

/*
 LowPower State Class
*/
class LowPower : public CraneState
{
public:
    LowPower(Crane &context)
    {
        this->state = "Low Power";
        this->contextRef = context;
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
        return;
    }
};

/*
 NoConnection State Class
*/
class NoConnection : public CraneState
{
public:
    NoConnection(Crane &context)
    {
        this->state = "No Connection";
        this->contextRef = context;
    }
    static NoConnection *getInstance()
    {
        static NoConnection *instance = new NoConnection();
        return instance;
    }

    void checkPower(Crane &c) override
    {
        // Implementation for NoConnection state
    }

    void sendData(Crane &c) override
    {
        // Implementation for NoConnection state
        // it should probably do this to "reconnect"
    }

    void winchControl(Crane &c) override;

    void listen(Crane &c) override
    {
        // TODO: Implement no connection state listening functionality
        // TODO: Periodically check for connection restoration
    }

    void timerWinchControl(Crane &c);
};

/*
 Both State Class (Low Power and No Connection)
*/
class Both : public CraneState
{
public:
    Both(Crane &context)
    {
        this->state = "Both";
        this->contextRef = context;
    }
    static Both *getInstance()
    {
        static Both *instance = new Both();
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
};

#endif // CRANESTATE_H