#include <iostream>
#include "Graph.h"
#include <sstream>
#include <queue>

using namespace std;

Graph::Graph() {
    stations = map<string,shared_ptr<Station>>();
    map<string, shared_ptr<Station>>();
}

void Graph::addStation(string name) {
    auto it = stations.find(name);
    if (it!= stations.end()) {
        std::cout << "Station already exists" << std::endl;
        return;
    }
    shared_ptr<Station> sharedPtr = make_shared<Station>(name);
    stations.insert({name, sharedPtr});
    std::cout << "Station added" << std::endl;
}

void Graph::addEdge(string from, string to, int type, int StopTime, int duration) {
    addStation(from);
    addStation(to);
    auto it = stations.find(from);
    auto it2 = stations.find(to);
    std::shared_ptr<Transport> sharedPtr = std::make_shared<Transport>(StopTime, type);
    it->second->addConnection(it2->second, sharedPtr, duration);
    it2->second->addRevConnection(it->second, sharedPtr, duration);
}

void Graph::printGraph() {
    for (const auto &station: stations)
        std::cout << station.second->printStation().str();


}

//void Graph::bfdPrint(const string& startName, bool reverse) {
//    auto it = stations.find(startName);
//    if (it == stations.end()) {
//        std::cout << "Station not found" << std::endl;
//        return;
//    }
//    shared_ptr<Station> start = it->second;
//    std::set<shared_ptr<Station>> visited;
//    std::queue<shared_ptr<Station>> queue;
//    queue.push(start);
//    visited.insert(start);
//    while (!queue.empty()) {
//        shared_ptr<Station> station = queue.front();
//        queue.pop();
//        std::cout << station->getName() << "\t";
//        map<shared_ptr<Station>, array<pair<shared_ptr<Transport>, int>, 4>> connections;
//        if(reverse){
//             connections = station->getRevConnections();
//        } else connections = station->getConnections();
//        for (const auto &connection: connections) {
//            if (visited.find(connection.first) == visited.end()) {
//                queue.push(connection.first);
//                visited.insert(connection.first);
//            }
//        }
//    }
//}

//typedef pair<int, string> iPair;
//map<string, int> Graph::dijukstra(const string &start, int type) {
//    //Check if start inside and -1<type<5
//    map<string, int> distMap;
//    priority_queue<iPair, vector<iPair>, greater<iPair>> priorityQueue;
//    priorityQueue.emplace(0, start);
//    distMap[start] = 0;
//    while (!priorityQueue.empty()){
//        string currStName = priorityQueue.top().second;
//        priorityQueue.pop();
//        auto currSt = stations[currStName];
//        for(auto & connSt: currSt->getConnections()){
//            string connStName = connSt.first->getName();
//            shared_ptr<Transport> weight_ptr = connSt.second[type].first;
//            if(weight_ptr== nullptr) {
//                continue;
//            }
//            int weight = weight_ptr->getStopTime();
//            if (distMap.find(connStName) == distMap.end() || distMap[connStName] > distMap[currStName] + weight){
//                distMap[connStName] = distMap[currStName] + weight;
//                priorityQueue.emplace(distMap[connStName], connStName);
//            }
//        }
//    }
//    return distMap;
//}

//map<string, int> Graph::dijukstra2(const string &start) {
//    //Check if start inside and -1<type<5
//    map<string, int> distMap;
//    priority_queue<iPair, vector<iPair>, greater<iPair>> priorityQueue;
//    int type = -1;
//    priorityQueue.emplace(0, start);
//    distMap[start] = 0;
//    while (!priorityQueue.empty()){
//        string currStName = priorityQueue.top().second;
//        priorityQueue.pop();
//        auto currSt = stations[currStName];
//        for(auto & connSt: currSt->getConnections()){
//            string connStName = connSt.first->getName();
//            array<shared_ptr<Transport>, 4> connTrArray = connSt.second;
//            int weight = -1;
//            if(type == -1)
//                for(const auto& transport: connTrArray){
//                    if (transport == nullptr) continue;
//                    if (weight == -1 || weight > transport->getStopTime()) {
//                        weight = transport->getStopTime();
//                        type = transport->getType();
//                    }
//            }
//            else {
//                for(const auto& transport: connTrArray){
//                    if (transport == nullptr) continue;
//                    int passWeight = (transport->getType() == type) ? transport->getStopTime():transport->getStopTime() +
//                    if (weight == -1 || weight > transport->getStopTime()) {
//                        weight = transport->getStopTime();
//                        type = transport->getType();
//                    }
//
//            }
//            if (distMap.find(connStName) == distMap.end() || distMap[connStName] > distMap[currStName] + weight){
//                distMap[connStName] = distMap[currStName] + weight;
//                priorityQueue.emplace(distMap[connStName], connStName);
//            }
//        }
//    }
//    return distMap;
//}

