#ifndef NORMAL_H
#define NORMAL_H
#include "Crane.h"
#include "CraneState.h"
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

private:
    Normal() {}
    Normal(const Normal &) = delete;
    Normal &operator=(const Normal &) = delete;
};

#endif // CRANESTATE_H