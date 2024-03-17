#ifndef HW2_TRANSPORT_H
#define HW2_TRANSPORT_H

#include <string>
#include <utility>

using namespace std;

class Transport {
private:
    int type;
    int StopTime;
public:
    Transport(int StopTime, int type) : StopTime(StopTime), type(type){};
    bool operator <(const Transport &other) const;
    int getType() {
        return type;
    }
    int getStopTime() {
        return StopTime;
    }


};


#endif //HW2_TRANSPORT_H
