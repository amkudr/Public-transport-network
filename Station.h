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
class Edge;
class Station {
private:
    string name;
    int changeTime = 3;
//    vector<Edge> edges;
    map<shared_ptr<Station>, array<pair<shared_ptr<Transport>, int>, 4>> connections; // 0 - bus, 1 - tram, 2 - sprinter, 3 - rail
    map<shared_ptr<Station>, array<pair<shared_ptr<Transport>, int>, 4>> connectionsRev; // Reversion connections
public:
    explicit Station(string name);
    void addConnection(const shared_ptr<Station> &station, shared_ptr<Transport> transport, int duration);
    void addRevConnection(const shared_ptr<Station> &station, shared_ptr<Transport> transport, int duration);

    string getName() {
        return name;
    }

    stringstream printStation();

    map<shared_ptr<Station>, array<pair<shared_ptr<Transport>, int>, 4>> getConnections() { return connections; }
    map<shared_ptr<Station>, array<pair<shared_ptr<Transport>, int>, 4>> getRevConnections() { return connectionsRev; }





};


#endif //HW2_STATION_H
