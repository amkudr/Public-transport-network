#ifndef HW2_STATION_H
#define HW2_STATION_H

#include <string>
#include "Transport.h"
#include <map>
#include <vector>
#include "memory"
#include "set"
#include <array>


using namespace std;

class Station;

typedef shared_ptr<Station> St_ptr;
typedef shared_ptr<Transport> Tr_ptr;

class Station {
private:
    string name;

    map<St_ptr, array<Tr_ptr, 4>> connections; // 0 - bus, 1 - tram, 2 - sprinter, 3 - rail
    map<St_ptr, array<Tr_ptr, 4>> connectionsRev; // Reversion connections

public:
    static int changeTime;

    explicit Station(string name);

    void addConnection(const St_ptr &station, const Tr_ptr &transport, bool rev = false);

    string getName() {
        return name;
    }

    stringstream printStation();

    map<St_ptr, array<Tr_ptr, 4>> getConnections() { return connections; }

    map<St_ptr, array<Tr_ptr, 4>> getRevConnections() { return connectionsRev; }

    static int getChangeTime(){
        return changeTime;
    }

};


#endif //HW2_STATION_H
