
#include <sstream>
#include <iostream>
#include "Station.h"

using namespace std;

Station::Station(string name) : name(std::move(name)) {
    connections = map<St_ptr, array<Tr_ptr, 4>>();
}

void Station::addConnection(const shared_ptr<Station> &station, const shared_ptr<Transport> &transport, bool rev) {
    auto &currConn = rev ? connectionsRev : connections;
    auto it = currConn.find(station); //find station in connections
    if (it != currConn.end()) {//if station is in connections
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
    ss << "Station: " << name << endl<<"Connections: \n";
    for (const auto &connect: connections) {
        ss << connect.first->getName() <<" by: ";
        for (int i = 0; i < 4; i++) {
            tran = connect.second[i];
            if (tran != nullptr) {
                ss<<tran->getName()<<"-"<<tran->getDuration()<<" ";
            }
        }
        ss<<endl;
    }
    ss<<endl;
    return ss;
}

string Station::getName() {
    return name;
}


