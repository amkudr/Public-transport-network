#include <iostream>
#include "Graph.h"
#include <sstream>
#include <queue>

using namespace std;

Graph::Graph() {
    stations = map<string, St_ptr>();
}

void Graph::addStation(string name) {
    auto it = stations.find(name);
    if (it != stations.end()) {
        std::cout << "Station already exists" << std::endl;
        return;
    }
    St_ptr sharedPtr = make_shared<Station>(name);
    stations.insert({std::move(name), sharedPtr});
    std::cout << "Station added" << std::endl;
}

void Graph::addEdge(const string &from, const string &to, int type, int duration) {
    addStation(from);
    addStation(to);
    auto it = stations.find(from);
    auto it2 = stations.find(to);
    Tr_ptr sharedPtr = std::make_shared<Transport>(type, duration);
    it->second->addConnection(it2->second, sharedPtr);
    it2->second->addConnection(it->second, sharedPtr, true);
}

void Graph::printGraph() {
    for (const auto &station: stations)
        std::cout << station.second->printStation().str();


}

void Graph::bfdPrint(const string &startName, bool reverse) {
    auto it = stations.find(startName);
    if (it == stations.end()) {
        std::cout << "Station not found" << std::endl;
        return;
    }
    St_ptr start = it->second;
    std::set<St_ptr> visited;
    std::queue<St_ptr> queue;
    queue.push(start);
    visited.insert(start);
    while (!queue.empty()) {
        St_ptr station = queue.front();
        queue.pop();
        std::cout << station->getName() << "\t";
        map<St_ptr, array<Tr_ptr, 4>> connections;
        if (reverse) {
            connections = station->getRevConnections();
        } else connections = station->getConnections();
        for (const auto &connection: connections) {
            if (visited.find(connection.first) == visited.end()) {
                queue.push(connection.first);
                visited.insert(connection.first);
            }
        }
    }
}

typedef pair<int, string> iPair;

map<string, int> Graph::dijkstra(const string &start, int type) {
    //Check if start inside and -1<type<5
    if (stations.find(start) == stations.end() || type < 0 || type >= 5) {
        return {};
    }
    map<string, int> distMap; //keep distance for every vertex from vertex start
    priority_queue<iPair, vector<iPair>, greater<iPair>> priorityQueue; //queue to keep vertexes by algorithm
    priorityQueue.emplace(0, start);
    distMap[start] = 0;
    while (!priorityQueue.empty()) {
        string currStName = priorityQueue.top().second;
        priorityQueue.pop();


        //check if current distance value bigger than distance that already exist to improve algorithm
        if (distMap[currStName] < priorityQueue.top().first) {
            continue;
        }

        auto currSt_ptr = stations[currStName];
        for (auto &connSt_ptr: currSt_ptr->getConnections()) {
            string connStName = connSt_ptr.first->getName();
            Tr_ptr tr_ptr = connSt_ptr.second[type];
            if (tr_ptr == nullptr) {
                continue;
            }
            int weight = tr_ptr->getDuration();
            if (currStName != start)
                weight += tr_ptr->getStopTime(); //Check if it is start vertex, we don't need to add stop time

            if (distMap.find(connStName) == distMap.end() || distMap[connStName] > distMap[currStName] + weight) {
                distMap[connStName] = distMap[currStName] + weight;
                priorityQueue.emplace(distMap[connStName], connStName);
            }
        }
    }
    return distMap;
}

map<string, int> Graph::dijukstra2(const string &start) {
    //Check if start inside and -1<type<5
    if (stations.find(start) == stations.end()) {
        return {};
    }
    map<string, int> distMap; //keep distance for every vertex from vertex start
    priority_queue<iPair, vector<iPair>, greater<iPair>> priorityQueue; //queue to keep vertexes by algorithm
    priorityQueue.emplace(0, start);
    distMap[start] = 0;
    while (!priorityQueue.empty()) {
        string currStName = priorityQueue.top().second;
        priorityQueue.pop();


        //check if current distance value bigger than distance that already exist to improve algorithm
        if (distMap[currStName] < priorityQueue.top().first) {
            continue;
        }

        auto currSt_ptr = stations[currStName];
        for (auto &connSt_ptr: currSt_ptr->getConnections()) {
            string connStName = connSt_ptr.first->getName();
            Tr_ptr tr_ptr = connSt_ptr.second[type];
            if (tr_ptr == nullptr) {
                continue;
            }
            int weight = tr_ptr->getDuration();
            if (currStName != start)
                weight += tr_ptr->getStopTime(); //Check if it is start vertex, we don't need to add stop time

            if (distMap.find(connStName) == distMap.end() || distMap[connStName] > distMap[currStName] + weight) {
                distMap[connStName] = distMap[currStName] + weight;
                priorityQueue.emplace(distMap[connStName], connStName);
            }
        }
    }
    return distMap;
}

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
