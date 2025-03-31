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

class Crane;
class Normal;
class LowPower;
class NoConnection;
class Both;

class CraneState
{
protected:
    Crane *contextRef;

public:
    virtual ~CraneState() = default;

    void set_context(Crane *context)
    {
        this->contextRef = context;
    }

    virtual std::string getState();
    virtual void checkPower(Crane &context) = 0;
    virtual void sendData(Crane &context) = 0;
    virtual void winchControl(Crane &context) = 0;
    virtual void listen(Crane &context) = 0;
};

/*
 Normal State Class
 TODO: Bring in the FSM code
*/
class Normal : public CraneState
{
public:
    std::string getState()
    {
        return "Normal";
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
    std::string getState()
    {
        return "Low Power";
    }
    void checkPower(Crane &context) override;
    void sendData(Crane &context) override;
    void winchControl(Crane &context) override;
    void listen(Crane &context) override;
};

/*
 NoConnection State Class
*/
class NoConnection : public CraneState
{
public:
    std::string getState()
    {
        return "No Connection";
    }
    void checkPower(Crane &context) override;
    void sendData(Crane &context) override;
    void winchControl(Crane &context) override;
    void listen(Crane &context) override;
};

/*
 Both State Class (Low Power and No Connection)
*/
class Both : public CraneState
{
public:
    std::string getState()
    {
        return "Both";
    }
    void checkPower(Crane &context) override;
    void sendData(Crane &context) override;
    void winchControl(Crane &context) override;
    void listen(Crane &context) override;
};

#endif // CRANESTATE_H