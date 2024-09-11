#ifndef HW2_TRANSPORT_H
#define HW2_TRANSPORT_H

#include <string>
#include <utility>

using namespace std;

class Transport {
private:
    int dur;
public:

    explicit Transport(int dur) : dur(dur) {};

    Transport(const Transport &other)  = default;

    Transport(Transport &&other)  noexcept : dur(other.dur) {}

    Transport &operator=(const Transport &other);

    Transport &operator=(Transport &&other)  noexcept;

    bool operator<(const Transport &other) const;

    int getDuration() const {
        return dur;
    }

    virtual int getType() const = 0;

    virtual int getStopTime() const = 0;

    virtual string getName() const = 0;

};


#endif //HW2_TRANSPORT_H
