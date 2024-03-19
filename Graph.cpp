#include <iostream>
#include "Graph.h"
#include <sstream>
#include <queue>
#include <algorithm>

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


typedef tuple<int, string, int> iTriple; //Duration, Vertex Name, Type of transport
map<string, int> Graph::dijkstra2(const string &start) {
    auto it = stations.find(start);
    //Check if start inside and -1<type<5
    if (it == stations.end()) {
        return {};
    }
    array<map<string, int>, 2> arrOfDistMap;
    priority_queue<iTriple, vector<iTriple>, greater<iTriple>> priorityQueue; //queue to keep vertexes by algorithm
    auto start_connections = it->second->getConnections();
//    priorityQueue.emplace(0, start, 0);
    for (int i = 0; i < 2; i++) {
        arrOfDistMap[i][start] = 0;
        priorityQueue.emplace(0, start, i);

    }

    while (!priorityQueue.empty()) {

        string currStName = std::get<1>(priorityQueue.top());
        int type = std::get<2>(priorityQueue.top());
        priorityQueue.pop();


//        //check if current distance value bigger than distance that already exist to improve algorithm
//        if(arrOfDistMap[type][currStName]< get<0>(priorityQueue.top())) continue;

        auto currSt_ptr = stations[currStName];
        for (auto &connSt_ptr: currSt_ptr->getConnections()) {
            string connStName = connSt_ptr.first->getName();
            for (int i = 0; i < 2; i++) {
                Tr_ptr tr_ptr = connSt_ptr.second[i];
                if (tr_ptr == nullptr) {
                    continue;
                }
                int weight = tr_ptr->getDuration();
                if (currStName != start) {
                    if (i != type) weight += currSt_ptr->getChangeTime(); //Add transit time
                    else weight += tr_ptr->getStopTime();
                } else {
                    if (i != type) continue;
                }

                if (arrOfDistMap[i].find(connStName) == arrOfDistMap[i].end() ||
                    arrOfDistMap[i][connStName] > arrOfDistMap[type][currStName] + weight) {
                    arrOfDistMap[i][connStName] = arrOfDistMap[type][currStName] + weight;
                    priorityQueue.emplace(arrOfDistMap[i][connStName], connStName, i);
                }
            }
        }
    }
    map<string, int> distMap;


    for (const auto &pair: arrOfDistMap[0]) {
        string key = pair.first;
        int value1 = pair.second;
        int value2 = arrOfDistMap[1][key];
//        int value3 = arrOfDistMap[2][key];
//        int value4 = arrOfDistMap[3][key];

//        int max_value = std::max({value1, value2, value3, value4});
        int min_value = std::min({value1, value2});


        distMap[key] = min_value;
    }
    return distMap;

}

