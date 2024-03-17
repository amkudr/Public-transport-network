#include <iostream>
#include "Graph.h"

int main() {
    Graph graph = Graph();
    graph.addEdge("A", "B", 1, 1);
    graph.addEdge("A", "C", 1, 2);
    graph.addEdge("C", "D", 1, 3);
    graph.addEdge("D", "A", 1, 4);
    graph.addEdge("B", "E", 1, 5);
    graph.addEdge("M", "E", 1, 6);
    graph.printGraph();
    graph.bfdPrint("E", true);

//    graph.printGraph();
//    auto v = graph.dijukstra("A", 1);
//    for( const auto& i:v){
//        cout<<i.first<< " "<<i.second<<endl;
//    }
//    graph.bfdPrint("E", true);
    return 0;
}
