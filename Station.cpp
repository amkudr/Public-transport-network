
#include <sstream>
#include "Station.h"

using namespace std;

Station::Station(string name) {
    this->name = std::move(name);
    connections = map<shared_ptr<Station>, array<pair<shared_ptr<Transport>, int>, 4>>();
}

void Station::addConnection(const shared_ptr<Station> &station, shared_ptr<Transport> transport, int duration) {
    auto it = connections.find(station); //find station in connections
    if (it != connections.end()) {//if station is in connections
        auto& currTrPair = it->second[transport->getType()];
        if (currTrPair.first == nullptr) {
            currTrPair.first = transport;
        } else if (duration < currTrPair.second) {
                currTrPair.second = duration;
        }
    }
    else { //if station is not in connections
        auto it2 = connections.insert(pair<shared_ptr<Station>, array<pair<shared_ptr<Transport>,int>, 4>>(station, array<pair<shared_ptr<Transport>,int>, 4>{}));
        it2.first->second[transport->getType()] = make_pair(transport, duration);
    }
}

stringstream Station::printStation() {
    stringstream ss;
    ss<<"Station: "<<name<<endl<<"Connections: \n";
    for (const auto & connect: connections){
        ss<<connect.first->getName()<<endl;
        for (int i=0; i<4; i++){
            if (connect.second[i].first != nullptr){
                ss<<"By type "<<connect.second[i].first->getType()<<" with Stop time "<<connect.second[i].first->getStopTime()<<" Duration "<<connect.second[i].second<<endl;
            }
        }
    }
    return ss;
}

void Station::addRevConnection(const shared_ptr<Station> &station, shared_ptr<Transport> transport, int duration) {
    auto it = connectionsRev.find(station); //find station in connections
    if (it != connectionsRev.end()) {//if station is in connections
        auto& currTrPair = it->second[transport->getType()];
        if (currTrPair.first == nullptr) {
            currTrPair.first = transport;
        } else if (duration < currTrPair.second) {
            currTrPair.second = duration;
        }
    }
    else { //if station is not in connections
        auto it2 = connectionsRev.insert(pair<shared_ptr<Station>, array<pair<shared_ptr<Transport>,int>, 4>>(station, array<pair<shared_ptr<Transport>,int>, 4>{}));
        it2.first->second[transport->getType()] = make_pair(transport, duration);
    }

}


