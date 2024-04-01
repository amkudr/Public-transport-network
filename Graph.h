#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H

#include "Station.h"
#include "Bus.h"
#include "Tram.h"
#include "Sprinter.h"
#include "Rail.h"
#include "Intercity.h"
#include "Stad.h"
#include "Central.h"

#include <map>
#include <vector>
#include <memory>

using namespace std;

class Graph {
private:

    array<string,4 > tran_names = {"bus", "tram", "sprinter", "rail"};

    map<string, St_ptr> stations;
    array<Tr_ptr, 4> transport;

    unique_ptr<vector<string>> bfs(const string &startName, bool reverse, int type);

    unique_ptr<map<string, int>> dijkstra(const string &start, int type);

    unique_ptr<array<map<string, int>, 4>> dijkstraMulti(const string &start, const vector<pair<int, int>> &startVector = {});
public:
    explicit Graph();

    void addStation(string name);

    void addEdge(const string &from, const string &to, int type, int duration);

    static void setConfig(const vector<pair<string, int>> &inVector);

    string print();

    void outbound(const string &source_node, bool isInborn = false);

    void inbound(const string &source_node);

    void uniExpress(const string &source_node, const string &target_node);

    void multiExpress(const string &source_node, const string &target_node);

    void viaExpress(const string &source_node, const string &transit_node, const string &target_node);


};


#endif //HW2_GRAPH_H
