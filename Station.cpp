
#include <sstream>
#include "Station.h"

using namespace std;

int Station::changeTime = 3;

Station::Station(string name) {
    this->name = std::move(name);
    connections = map<St_ptr, array<Tr_ptr, 4>>();
}

void Station::addConnection(const shared_ptr<Station> &station, const shared_ptr<Transport> &transport, bool rev) {
    auto &currConn = rev ? connectionsRev : connections;
    auto it = currConn.find(station); //find station in connectionsOld
    if (it != currConn.end()) {//if station is in connectionsOld
        auto &currTr = it->second[transport->getType()];
        if (currTr == nullptr || currTr < transport) currTr = transport;

    } else { //if station is not in connections
        auto it2 = currConn.emplace(station,array<Tr_ptr, 4>{});
        it2.first->second[transport->getType()] = transport;
    }
}

stringstream Station::printStation() {
    stringstream ss;
    Tr_ptr tran;
    ss << "Station: " << name << endl << "Connections: \n";
    for (const auto &connect: connections) {
        ss << connect.first->getName() <<" ";
        for (int i = 0; i < 4; i++) {
            tran = connect.second[i];
            if (tran != nullptr) {
                ss << "by type " <<tran->getType() << " with Stop time "
                   << tran->getStopTime() << " Duration " << tran->getDuration() << endl;
            }
        }
    }
    return ss;
}


