#ifndef HW2_TRAM_H
#define HW2_TRAM_H
#include "Transport.h"
class Tram: public Transport {
private:
    static int stopTime;
public:
    explicit Tram(int dur) : Transport(dur) {}
    int getType() const override;
    int getStopTime() const override;
    static void setStopTime(int time);
    string getName() const override;
};
#endif //HW2_TRAM_H
