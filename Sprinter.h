
#ifndef HW2_SPRINTER_H
#define HW2_SPRINTER_H
#include "Transport.h"

class Sprinter: public Transport {
private:
    static int stopTime;
public:
    explicit Sprinter(int dur) : Transport(dur) {}
    int getType() const override;
    int getStopTime() const override;
    static void setStopTime(int time);
    string getName() const override;
};

#endif //HW2_SPRINTER_H
