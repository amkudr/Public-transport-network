#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H

#include "Station.h"
#include <map>
#include <vector>
#include <memory>

using namespace std;

class Graph {
private:
    map<string, St_ptr> stations;
    array<Tr_ptr, 4> transport;
public:
    Graph();

    void addStation(string name);

    void addEdge(const string &from, const string &to, int type, int duration);

    void printGraph();

    void bfdPrint(const string &startName, bool reverse = false);

    map<string, int> dijkstra(const string &start, int type);

    array<map<string, int>, 4> dijkstraMulti(const string &start, const vector<pair<int, int>>& startVector = {});

    int fromAtoBSingle(const string &a, const string &b);

    int fromAtoBMulti(const string &a, const string &b);

    int fromAtoBThrowC(const string &a, const string &b, const string &c);


};


#endif //HW2_GRAPH_H
