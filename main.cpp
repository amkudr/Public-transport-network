#include <iostream>
#include "Graph.h"

int main() {
    Graph graph = Graph();
    graph.addEdge("A", "B", 0, 7);
    graph.addEdge("A", "B", 1, 3);
    graph.addEdge("A", "B", 2, 1);
    graph.addEdge("A", "B", 3, 1);
    graph.addEdge("B", "C", 0, 10);
    graph.addEdge("B", "C", 1, 1);
    graph.addEdge("C", "D", 0, 5);
    graph.addEdge("C", "D", 1, 100);

    graph.multiExpress("A", "C");

    graph.uniExpress("A", "C");
    graph.viaExpress("B", "D", "C");
    graph.inborn("C");
//    for(const auto& station: vector){
//        cout<<station<<"\t";
//    }
//






//    graph.addEdge("A", "B", 1, 1);
//    graph.addEdge("A", "B", 0, 3);
//    graph.addEdge("B", "C", 1, 10);
//    graph.addEdge("B", "C", 0, 1);
//    graph.addEdge("C", "D", 1, 3);
//    graph.addEdge("D", "A", 1, 4);
//    graph.addEdge("B", "E", 1, 5);
//    graph.addEdge("M", "E", 1, 6);
//    graph.addEdge("B", "D", 1, 3);
//    graph.printGraph();
//    graph.bfs("E", true);

//    graph.printGraph();
//    auto v = graph.dijkstraMulti("A", vector<pair<int, int>>());
//    for( const auto& i:v){
//        cout<<i.first<< " "<<i.second<<endl;
//    }
//    graph.bfs("E", true);
    return 0;
}
