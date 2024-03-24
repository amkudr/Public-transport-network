#ifndef HW2_BUS_H
#define HW2_BUS_H


#include "Transport.h"

class Bus: public Transport {
private:
    static int stopTime;
public:
    explicit Bus (int dur) : Transport(dur) {}
    int getType() const override {
        return 0;
    }
    int getStopTime() const override;

    static void setStopTime(int time);

    string getName() const override;

};

#endif //HW2_BUS_H
