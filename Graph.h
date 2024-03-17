#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H

#include "Station.h"
#include <map>
#include <vector>
#include <memory>

using namespace std;

class Graph {
private:
    map<string,St_ptr> stations;
    array<Tr_ptr , 4> transport;
public:
    Graph();
    void addStation(string name);
    void addEdge(const string& from, const string& to, int type, int duration);
    void printGraph();
    void bfdPrint(const string& startName, bool reverse = false);
//    map<string, int> dijukstra(const string &start, int type);
//    map<string, int> dijukstra2(const string &start);


};


#endif //HW2_GRAPH_H
