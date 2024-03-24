#include <iostream>
#include "Graph.h"

int main() {
//    Graph graph = Graph(8,4,5,6);
    Graph graph = Graph();

    for (char stationName = 'A'; stationName <= 'Z'; ++stationName) {
        string station = string(1, stationName);
        graph.addStation(station);
    }

    // Добавляем рёбра между станциями
//    graph.addEdge("A", "B", 0, 5);
//    graph.addEdge("B", "C", 0, 3);
//    graph.addEdge("C", "D", 1, 7);
//    graph.addEdge("D", "E", 1, 4);
//    graph.addEdge("E", "F", 1, 6);
//    graph.addEdge("F", "G", 1, 2);
//    graph.addEdge("G", "H", 2, 5);
//    graph.addEdge("H", "I", 2, 3);
//    graph.addEdge("I", "J", 2, 4);
//    graph.addEdge("J", "K", 1, 7);
//    graph.addEdge("K", "L", 2, 6);
//    graph.addEdge("L", "M", 3, 5);
//    graph.addEdge("M", "N", 0, 8);
//    graph.addEdge("N", "O", 1, 9);
//    graph.addEdge("O", "P", 2, 10);
//    graph.addEdge("P", "Q", 3, 11);
//    graph.addEdge("Q", "R", 0, 12);
//    graph.addEdge("R", "S", 1, 13);
//    graph.addEdge("S", "T", 2, 14);
//    graph.addEdge("T", "U", 3, 15);
//    graph.addEdge("U", "V", 0, 16);
//    graph.addEdge("V", "W", 1, 17);
//    graph.addEdge("W", "X", 2, 18);
//    graph.addEdge("X", "Y", 3, 19);
//    graph.addEdge("Y", "Z", 0, 20);
//    graph.addEdge("A", "Z", 1, 10);

    // Выполняем операции с графом
//    graph.viaExpress("A", "M", "C"); // Путь от A до E через C
//    graph.multiExpress("A", "J");    // Множественный кратчайший путь от A до E
//
//    graph.uniExpress("A", "J");      // Универсальный кратчайший путь от A до E

    graph.addEdge("A", "B", 0, 7);
    graph.addEdge("A", "B", 1, 3);
    graph.addEdge("A", "B", 2, 1);
    graph.addEdge("A", "B", 3, 1);
    graph.addEdge("B", "C", 0, 10);
    graph.addEdge("B", "C", 1, 1);
    graph.addEdge("C", "D", 0, 5);
    graph.addEdge("C", "D", 1, 100);
    graph.addEdge("A", "D", 3,2);
    graph.addEdge("D", "C", 2,2);

    graph.multiExpress("A", "C");

    graph.uniExpress("A", "C");
    graph.viaExpress("B", "D", "C");
    graph.outborn("C");
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
