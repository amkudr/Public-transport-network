#include <iostream>
#include "Graph.h"
#include <sstream>
#include <queue>
#include <climits>
#include <string>
#include <functional>


using namespace std;

Graph::Graph() {
    // Constructor initializes a map of station names (string) to station pointers (St_ptr)
    stations = map<string, St_ptr>();
}

/*
 * setConfig function takes a vector of transport types and their associated time values.
 * It configures stop or change times for different types of transport based on the input vector.
 */
void Graph::setConfig(const vector<pair<string, int>> &inVector) {
    if (inVector.empty()) {
        return;
    }
    for (auto &p: inVector) {
        if (p.second<=0) throw invalid_argument("config time is negative/zero");
        // Set the appropriate stop or change time for the transport type
        if (p.first == "bus") Bus::setStopTime(p.second);
        else if (p.first == "tram") Tram::setStopTime(p.second);
        else if (p.first == "sprinter") Sprinter::setStopTime(p.second);
        else if (p.first == "rail") Rail::setStopTime(p.second);
        else if (p.first == "intercity") Intercity::setChangeTime(p.second);
        else if (p.first == "central") Central::setChangeTime(p.second);
        else if (p.first == "stad") Stad::setChangeTime(p.second);
    }
}

/*
 * addStation function adds a station to the graph by its name.
 * It checks if the station name already exists, and if not, it creates a new station and inserts it into the graph.
 */
void Graph::addStation(string name) {
    if (name.size()>16 || name.find(' ') != string::npos) throw runtime_error("Invalid station name");

    auto it = stations.find(name);
    if (it != stations.end()) {
        return;
    }
    St_ptr sharedPtr;
    // Based on the first two characters of the station name, different types of stations are created
    auto sub_str = name.substr(0, 2);
    if (sub_str == "IC") sharedPtr = make_shared<Intercity>(name);
    else if (sub_str == "CS") sharedPtr = make_shared<Central>(name);
    else sharedPtr = make_shared<Stad>(name);
    stations.insert({std::move(name), sharedPtr});
}

/*
 * addEdge function connects two stations with a transportation type and a specified duration.
 * It validates inputs and uses different transport modes (Bus, Tram, Sprinter, Rail).
 */
void Graph::addEdge(const string &from, const string &to, int type, int duration) {
    if(duration<=0) throw invalid_argument("Duration between" + from + " and " + to + "is negative/zero");
    if(type < 0 || type > 3) throw invalid_argument("Invalid type");

    // Add stations if they don't already exist
    addStation(from);
    addStation(to);
    auto it = stations.find(from);
    auto it2 = stations.find(to);
    Tr_ptr sharedPtr;

    // Create the appropriate transport connection based on the type
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
    // Add the connection to both stations (bidirectional)
    it->second->addConnection(it2->second, sharedPtr);
    it2->second->addConnection(it->second, sharedPtr, true);
}

/*
 * print function outputs the graph as a string representation by iterating over all stations.
 * It returns a string containing station details and connections.
 */
string Graph::print() {
    stringstream ss;
    for (const auto &station: stations)
        ss << station.second->printStation().str();
    return ss.str();
}

/*
 * bfs function performs a Breadth-First Search from a given station.
 * It explores connections based on transport type and direction (forward or reverse).
 * The result is a vector of station names.
 */
unique_ptr<vector<string>> Graph::bfs(const string &startName, bool reverse, int type) {
    auto it = stations.find(startName);

    St_ptr start = it->second;
    set<St_ptr> visited;
    queue<St_ptr> queue;
    auto pathVector_ptr = unique_ptr<vector<string>>(new vector<string>());

    // BFS starting from the initial station
    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        St_ptr station = queue.front();
        queue.pop();

        pathVector_ptr->emplace_back(std::move(station->getName()));
        const auto &connections = reverse ? station->getRevConnections() : station->getConnections();

        // Traverse connections and add unvisited stations to the queue
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

/*
 * dijkstra function implements the Dijkstra's algorithm for finding the shortest path from a source station to all others.
 * It uses a priority queue to process stations by distance.
 */
unique_ptr<map<string, int>> Graph::dijkstra(const string &start, int type) {

    auto distMap = unique_ptr<map<string, int>>(new map<string, int>());
    priority_queue<iPair, vector<iPair>, greater<iPair>> priorityQueue;
    priorityQueue.emplace(0, start);
    (*distMap)[start] = 0;

    while (!priorityQueue.empty()) {
        string currStName = priorityQueue.top().second;
        priorityQueue.pop();

        auto currSt_ptr = stations[currStName];

        // Traverse connections for the current station
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

            // If a shorter path is found, update the distance
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

/*
 * dijkstraMulti function extends Dijkstra's algorithm to consider multiple transport types.
 * It processes connections for all transport types and returns an array of distance maps.
 */
typedef tuple<int, string, int> iTriple; //Duration, Vertex Name, Type of transport
unique_ptr<array<map<string, int>, 4>>
Graph::dijkstraMulti(const string &start, const vector<pair<int, int>> &startVector) {

    auto arrOfDistMap = std::unique_ptr<std::array<std::map<std::string, int>, 4>>(
            new std::array<std::map<std::string, int>, 4>()); //Array of all 4 type of the transport, map<NameVertex, distance>

    priority_queue<iTriple, vector<iTriple>, greater<iTriple>> priorityQueue; //queue to keep vertexes by algorithm
    bool isAdvAlg = !startVector.empty();

    // If we are starting the algorithm with advanced input
    if (isAdvAlg) {
        for (auto &p: startVector) {
            (*arrOfDistMap)[p.first].emplace(start, p.second);
            priorityQueue.emplace(p.second, start, p.first);
        }
    } else {
        // Otherwise, initialize for all transport types
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

        // Traverse all connections
        for (auto &connSt_ptr: currSt_ptr->getConnections()) {
            string connStName = connSt_ptr.first->getName();

            // Process for all transport types
            for (int i = 0; i < 4; i++) {
                Tr_ptr tr_ptr = connSt_ptr.second[i];
                if (tr_ptr == nullptr) { //If there is no connection by type i
                    continue;
                }
                int weight = tr_ptr->getDuration();
                if (currStName != start || isAdvAlg) {
                    if (isAdvAlg && i == type) {
                        weight += tr_ptr->getStopTime();
                    } else if (!isAdvAlg) {
                        weight += tr_ptr->getStopTime();
                    }
                }

                // Update distance if a shorter path is found
                if ((*arrOfDistMap)[i].find(connStName) == (*arrOfDistMap)[i].end() ||
                    (*arrOfDistMap)[i][connStName] > (*arrOfDistMap)[i][currStName] + weight) {
                    (*arrOfDistMap)[i][connStName] = (*arrOfDistMap)[i][currStName] + weight;
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

/*
 * viaExpress function
 * This function calculates the shortest path from source_node to target_node with a mandatory stop at transit_node.
 * It uses Dijkstra's algorithm to find the shortest paths from source_node to transit_node, and then from transit_node to target_node.
 *
 * source_node: starting station
 * transit_node: transit station that must be visited
 * target_node: destination station
 */
void Graph::viaExpress(const string &source_node, const string &transit_node, const string &target_node) {
    if (stations.find(source_node) == stations.end()) {
        throw invalid_argument(source_node + " does not exist in the current network");
    } else if (stations.find(target_node) == stations.end()) {
        throw invalid_argument(target_node + " does not exist in the current network");
    } else if (stations.find(transit_node) == stations.end()) {
        throw invalid_argument(transit_node + " does not exist in the current network");
    }

    auto arrOfDistMap = dijkstraMulti(source_node); // Get all distances from source_node
    vector<pair<int, int>> inputVector; // Vector for transit_node distance results
    int i = 0;

    // Find the shortest distance from source_node to transit_node for each transport type
    for (auto &distMap: (*arrOfDistMap)) {
        auto it = distMap.find(transit_node);
        if (it != distMap.end()) {
            inputVector.emplace_back(i, it->second);
            i++;
        }
    }
    if (inputVector.empty()) {
        cout << source_node << " and " << transit_node << " are not connected." << endl;
        return;
    }

    arrOfDistMap = dijkstraMulti(transit_node, inputVector); // Get all distances from transit_node to target_node
    int minvalue = INT_MAX;

    // Find the shortest distance from transit_node to target_node for each transport type
    for (auto &distMap: (*arrOfDistMap)) {
        auto it = distMap.find(target_node);
        if (it != distMap.end() && it->second < minvalue) {
            minvalue = it->second;
        }
    }

    if (minvalue == INT_MAX)
        cout << transit_node << " and " << target_node << " are not connected." << endl;
    else
        cout << "The shortest way from " << source_node << " to " << target_node << " via " << transit_node << " is " << minvalue << endl;
}

/*
 * uniExpress function
 * This function calculates the shortest path from source_node to target_node for each transport type individually.
 * It uses Dijkstra's algorithm to find the shortest path for each transport type.
 *
 * source_node: starting station
 * target_node: destination station
 */
void Graph::uniExpress(const string &source_node, const string &target_node) {
    if (stations.find(source_node) == stations.end()) {
        throw invalid_argument(source_node + " does not exist in the current network");
    } else if (stations.find(target_node) == stations.end()) {
        throw invalid_argument(target_node + " does not exist in the current network");
    }

    // Calculate the shortest paths for each transport type
    for (int i = 0; i < 4; i++) {
        cout << tran_names[i] << ": ";
        auto distMap = dijkstra(source_node, i);
        auto it = distMap->find(target_node);
        if (it != distMap->end()) {
            cout << it->second << endl; // Output the shortest distance
        } else {
            cout << "route unavailable" << endl;
        }
    }
}

/*
 * multiExpress function
 * This function calculates the shortest path from source_node to target_node across multiple transport types.
 * It uses a modified version of Dijkstra's algorithm (dijkstraMulti) to find the shortest path that may involve different transport types.
 *
 * source_node: starting station
 * target_node: destination station
 */
void Graph::multiExpress(const string &source_node, const string &target_node) {
    if (stations.find(source_node) == stations.end()) {
        throw invalid_argument(source_node + " does not exist in the current network");
    } else if (stations.find(target_node) == stations.end()) {
        throw invalid_argument(target_node + " does not exist in the current network");
    }

    auto arrOfDistMap = dijkstraMulti(source_node); // Get all distances for multiple transport types

    int minvalue = INT_MAX;

    // Find the shortest distance across all transport types
    for (auto distMap: (*arrOfDistMap)) {
        if (distMap.find(target_node) != distMap.end() && distMap[target_node] < minvalue) {
            minvalue = distMap[target_node];
        }
    }

    if (minvalue == INT_MAX) {
        cout << source_node << " and " << target_node << " are not connected" << endl;
    } else {
        cout << "The shortest way between " << source_node << " and " << target_node << " is " << minvalue << endl;
    }
}

/*
 * outbound function
 * This function lists all outbound connections from the source_node.
 * It uses breadth-first search (BFS) to find all stations reachable from source_node for each transport type.
 *
 * source_node: the station name from which outbound connections are searched
 * isInborn: a boolean to toggle between inbound and outbound search
 */
void Graph::outbound(const string &source_node, bool isInborn) {
    if (stations.find(source_node) == stations.end()) throw invalid_argument(source_node + " does not exist in the current network");

    // Search for outbound or inbound connections for each transport type
    for (int i = 0; i < 4; i++) {
        auto conVector_ptr = bfs(source_node, isInborn, i);
        cout << tran_names[i] << ": ";
        if (conVector_ptr->empty()) {
            if (isInborn) cout << "no inbound travel"; // If there are no inbound connections
            else cout << "no outbound travel"; // If there are no outbound connections
        } else {
            for (const auto &station: *conVector_ptr) {
                cout << station << '\t'; // Print all reachable stations
            }
        }
        cout << endl;
    }
}

/*
 * inbound function
 * This function lists all inbound connections to the source_node.
 * It is a wrapper around the outbound function with the isInborn parameter set to true.
 *
 * source_node: the station name to which inbound connections are searched
 */
void Graph::inbound(const string &source_node) {
    outbound(source_node, true); // Call outbound with isInborn = true for inbound search
}
