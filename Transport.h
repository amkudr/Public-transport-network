#ifndef HW2_TRANSPORT_H
#define HW2_TRANSPORT_H

#include <string>
#include <utility>

using namespace std;

class Transport {
private:
    int type;
    int dur;
public:
    static int stopTime;

    Transport(int type, int dur) : type(type), dur(dur) {};
    bool operator <(const Transport &other) const;
    int getDuration() const{
        return dur;
    }

    int getType() const {
        return type;
    }
    static int getStopTime() {
        return stopTime;
    }
};


#endif //HW2_TRANSPORT_H
