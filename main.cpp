#include <iostream>
#include "Graph.h"

int main() {
    Graph graph = Graph();
    graph.addEdge("A", "B", 1, 5, 1);
    graph.addEdge("A", "C", 1, 6, 2);
    graph.addEdge("C", "D", 1, 7, 3);
    graph.addEdge("D", "A", 1, 7, 4);
    graph.addEdge("B", "E", 1, 7, 5);
    graph.addEdge("M", "E", 1, 7, 6);
    graph.bfdPrint("A");

//    graph.printGraph();
//    auto v = graph.dijukstra("A", 1);
//    for( const auto& i:v){
//        cout<<i.first<< " "<<i.second<<endl;
//    }
//    graph.bfdPrint("E", true);
    return 0;
}
