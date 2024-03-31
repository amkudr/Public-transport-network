#include <iostream>
#include "Graph.h"
#include <sstream>
#include <queue>
#include <climits>
#include <string>
#include <functional>


using namespace std;

Graph::Graph() {
    stations = map<string, St_ptr>();
}

void Graph::setConfig(const vector<pair<string, int>> &inVector) {
    if (inVector.empty()) {
        return;
    }
    for (auto &p: inVector) {
        if (p.second<=0) continue;
        if (p.first == "bus") Bus::setStopTime(p.second);
        else if (p.first == "tram") Tram::setStopTime(p.second);
        else if (p.first == "sprinter") Sprinter::setStopTime(p.second);
        else if (p.first == "rail") Rail::setStopTime(p.second);
        else if (p.first == "intercity") Intercity::setChangeTime(p.second);
        else if (p.first == "central") Central::setChangeTime(p.second);
        else if (p.first == "stad") Stad::setChangeTime(p.second);
    }
}


void Graph::addStation(string name) {
    auto it = stations.find(name);
    if (it != stations.end()) {
//        cout << "Station already exists" << endl;
        return;
    }
    St_ptr sharedPtr;
    auto sub_str = name.substr(0, 2);
    if (sub_str == "IC") sharedPtr = make_shared<Intercity>(name);
    else if (sub_str == "CS") sharedPtr = make_shared<Central>(name);
    else sharedPtr = make_shared<Stad>(name);
    stations.insert({std::move(name), sharedPtr});
//    cout << "Station added" << endl;
}

void Graph::addEdge(const string &from, const string &to, int type, int duration) {
    addStation(from);
    addStation(to);
    auto it = stations.find(from);
    auto it2 = stations.find(to);
    Tr_ptr sharedPtr;
    switch (type) {
        case 0:
            sharedPtr = make_shared<Bus>(duration);
            break;
        case 1:
            sharedPtr = make_shared<Tram>(duration);
            break;
        case 2:
            sharedPtr = make_shared<Sprinter>(duration);
            break;
        case 3:
            sharedPtr = make_shared<Rail>(duration);
            break;
        default:
            break;

    }
    it->second->addConnection(it2->second, sharedPtr);
    it2->second->addConnection(it->second, sharedPtr, true);
}

string Graph::print() {
    stringstream ss;
    for (const auto &station: stations)
        ss << station.second->printStation().str();
    return ss.str();
}

unique_ptr<vector<string>> Graph::bfs(const string &startName, bool reverse, int type) {
    auto it = stations.find(startName);
    if (it == stations.end()) {
        cout << "Station not found" << endl;
        return {};
    }

    St_ptr start = it->second;
    set<St_ptr> visited;
    queue<St_ptr> queue;
    auto pathVector_ptr = unique_ptr<vector<string>>(new vector<string>());
    queue.push(start);
    visited.insert(start);
    while (!queue.empty()) {
        St_ptr station = queue.front();
        queue.pop();
        pathVector_ptr->emplace_back(std::move(station->getName()));
        const auto &connections = reverse ? station->getRevConnections() : station->getConnections();
        for (const auto &connection: connections) {
            if (visited.find(connection.first) == visited.end() && connection.second[type] != nullptr) {
                queue.push(connection.first);
                visited.insert(connection.first);
            }
        }
    }
    pathVector_ptr->erase(pathVector_ptr->cbegin()); //Delete first Station
    return pathVector_ptr;
}

typedef pair<int, string> iPair;

unique_ptr<map<string, int>> Graph::dijkstra(const string &start, int type) {
    if (stations.find(start) == stations.end() || type < 0 || type >= 5) {
        return nullptr;
    }

    auto distMap = unique_ptr<map<string, int>>(new map<string, int>());
    priority_queue<iPair, vector<iPair>, greater<iPair>> priorityQueue;
    priorityQueue.emplace(0, start);
    (*distMap)[start] = 0;

    while (!priorityQueue.empty()) {
        string currStName = priorityQueue.top().second;
        priorityQueue.pop();

        auto currSt_ptr = stations[currStName];

        for (auto &connSt_ptr: currSt_ptr->getConnections()) {
            string connStName = connSt_ptr.first->getName();
            Tr_ptr tr_ptr = connSt_ptr.second[type];
            if (tr_ptr == nullptr) {
                continue;
            }
            int weight = tr_ptr->getDuration();
            if (currStName != start) {
                weight += tr_ptr->getStopTime();
            }

            if (distMap->find(connStName) == distMap->end() ||
                (*distMap)[connStName] > (*distMap)[currStName] + weight) {
                (*distMap)[connStName] = (*distMap)[currStName] + weight;
                priorityQueue.emplace((*distMap)[connStName], connStName);
            }
        }
    }
    if (distMap->empty()) {
        return nullptr; // Return nullptr if arrOfDistMap is empty
    }

    return distMap;
}

typedef tuple<int, string, int> iTriple; //Duration, Vertex Name, Type of transport
unique_ptr<array<map<string, int>, 4>>
Graph::dijkstraMulti(const string &start, const vector<pair<int, int>> &startVector) {
    auto it = stations.find(start);
    if (it == stations.end()) {    //Check if start inside

        return {};
    }
    auto arrOfDistMap = std::unique_ptr<std::array<std::map<std::string, int>, 4>>(
            new std::array<std::map<std::string, int>, 4>()); //Array of all 4 type of the transport, map<NameVertex, distance>
    priority_queue<iTriple, vector<iTriple>, greater<iTriple>> priorityQueue; //queue to keep vertexes by algorithm
    bool isAdvAlg = !startVector.empty();
    if (isAdvAlg) { //If algorithm is second part of viaExpress function
        for (auto &p: startVector) {
            (*arrOfDistMap)[p.first].emplace(start, p.second);
            priorityQueue.emplace(p.second, start, p.first);
        }
    } else { //if we start algorithm from one Vertex
        for (int i = 0; i < 4; i++) {
            (*arrOfDistMap)[i][start] = 0;
            priorityQueue.emplace(0, start, i);

        }
    }

    while (!priorityQueue.empty()) {

        string currStName = get<1>(priorityQueue.top());
        int type = get<2>(priorityQueue.top());
        priorityQueue.pop();

        auto currSt_ptr = stations[currStName];

        for (auto &connSt_ptr: currSt_ptr->getConnections()) { //Go through all connections
            string connStName = connSt_ptr.first->getName();
            for (int i = 0; i < 4; i++) {
                Tr_ptr tr_ptr = connSt_ptr.second[i];
                if (tr_ptr == nullptr) { //If there is no connection by type i
                    continue;
                }
                int weight = tr_ptr->getDuration();
                if (currStName != start || isAdvAlg) { //If not the first vertex or it is advanced algorithm
                    if (i != type) weight += currSt_ptr->getChangeTime(); //Add transit time
                    else weight += tr_ptr->getStopTime(); //Add stop time
                } else {
                    if (i != type) continue; //optimization for start vertex
                }

                if ((*arrOfDistMap)[i].find(connStName) == (*arrOfDistMap)[i].end() ||
                    (*arrOfDistMap)[i][connStName] >
                    (*arrOfDistMap)[type][currStName] + weight) { //Check if new way is shorter
                    (*arrOfDistMap)[i][connStName] = (*arrOfDistMap)[type][currStName] + weight;
                    priorityQueue.emplace((*arrOfDistMap)[i][connStName], connStName, i);
                }
            }
        }
    }
    if (arrOfDistMap->empty()) {
        return nullptr; // Return nullptr if arrOfDistMap is empty
    }
    return arrOfDistMap;
}


void Graph::viaExpress(const string &source_node, const string &target_node, const string &transit_node) {
    if (stations.find(source_node) == stations.end() || stations.find(target_node) == stations.end() ||
        //Check if stations exist
        stations.find(transit_node) == stations.end())
        return;

    auto arrOfDistMap = dijkstraMulti(source_node); //Get all distances from a
    vector<pair<int, int>> inputVector; //Vector for advanced algorithm
    int i = 0;
    for (auto &distMap: (*arrOfDistMap)) { //Get the smallest distance from a to c by combination of transport
        auto it = distMap.find(transit_node);
        if (it != distMap.end()) {
            inputVector.emplace_back(i, it->second);
            i++;
        }
    }
    if (inputVector.empty())
        cout << source_node << " and " << transit_node << " are not connected."
             << endl; //If there is no connection from a to c
    arrOfDistMap = dijkstraMulti(transit_node, inputVector); //Get all distances from c to b
    int minvalue = INT_MAX;
    for (auto &distMap: (*arrOfDistMap)) { //Get the smallest value of all type of transport
        auto it = distMap.find(target_node);
        if (it != distMap.end() && it->second < minvalue) {
            minvalue = it->second;
        }
    }
    if (minvalue == INT_MAX)
        cout << transit_node << " and " << target_node << " are not connected."
             << endl; //If there is no connection from c to b
    else
        cout << "The shortest way from " << source_node << " to " << target_node << " via " << transit_node << " is "
             << minvalue << endl;
}

void Graph::uniExpress(const string &source_node, const string &target_node) {
    if (stations.find(source_node) == stations.end() ||
        stations.find(target_node) == stations.end()) //Check if stations exist
        return;

    for (int i = 0; i < 4; i++) {
        cout << tran_names[i] << ": ";
        auto distMap = dijkstra(source_node, i);
        auto it = distMap->find(target_node);
        if (it != distMap->end()) {
            cout << it->second << endl;
        } else {
            cout << "route unavailable" << endl;
        }
    }
}

void Graph::multiExpress(const string &source_node, const string &target_node) {
    if (stations.find(source_node) == stations.end() ||
        stations.find(target_node) == stations.end()) //Check if stations exist
        return;
    auto arrOfDistMap = dijkstraMulti(source_node);

    int minvalue = INT_MAX;
    for (auto distMap: (*arrOfDistMap)) {
        if (distMap.find(target_node) != distMap.end() && distMap[target_node] < minvalue) {
            minvalue = distMap[target_node];
        }
    }
    if (minvalue == INT_MAX) {
        cout << source_node << " and " << target_node << " are not connected" << endl;
    } else
        cout << "The shortest way between " << source_node << " and " << target_node << " is " << minvalue << endl;

}

void Graph::outbound(const string &source_node, bool isInborn) {
    if (stations.find(source_node) == stations.end()) //Check if station exist
        return; //CHANGE!!!!!!!!!!!!!!!
    for (int i = 0; i < 4; i++) {
        auto conVector_ptr = bfs(source_node, isInborn, i);
        cout << tran_names[i] << ": ";
        if (conVector_ptr->empty()) {
            if (isInborn) cout << "no inbound travel";
            else cout << "no outbound travel";
        } else {
            for (const auto &station: *conVector_ptr) {
                cout << station << "\t";
            }
        }
        cout << endl;
    }
}

void Graph::inbound(const string &source_node) {
    outbound(source_node, true);
}

