#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

void load(const shared_ptr<Graph> &graph, string &inputFileName) {
    ifstream inputFile(inputFileName);
    int type = -1;
    if (inputFileName.substr(0, 3) == "bus") type = 0;
    else if (inputFileName.substr(0, 4) == "tram") type = 1;
    else if (inputFileName.substr(0, 8) == "sprinter") type = 2;
    else if (inputFileName.substr(0, 4) == "rail") type = 3;
    if (type == -1) {
        cerr << "Failed to open input file, name " << inputFileName << " is incorrect" << endl;
        return;
    }
    if (inputFile.is_open()) {
        string line;
        string from, to;
        int duration;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            getline(iss, from, '\t');
            getline(iss, to, '\t');
            iss >> duration;
            graph->addEdge(from, to, type, duration);
        }
        inputFile.close();
    } else {
        cerr << "Failed to open input file, file " << inputFileName << " does not exist" << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Not enough arguments" << endl;
        return -1;
    }
    vector<string> inputVector = vector<string>();
    string outputFileName;
    string configFileName;

    //Read Arguments
    for (int i = 1; i < argc; ++i) {
        string arg_name = argv[i];
        if (arg_name == "-i") {
            while (i + 1 < argc && argv[i+1][0] != '-') {
                inputVector.emplace_back(argv[++i]);
            }
        } else if (arg_name == "-c" && i + 1 < argc) {
            configFileName = argv[++i];
        } else if (arg_name == "-o" && i + 1 < argc) {
            outputFileName = argv[++i];
        }
    }

    if (inputVector.empty()) {
        cerr << "No input files" << endl;
        return -1;
    }
    auto graph_ptr = make_shared<Graph>();

    //Read config
    if (!configFileName.empty()) {
        ifstream configFile(configFileName);
        if (configFile.is_open()) {
            vector<pair<string, int>> inVector = vector<pair<string, int>>();
            string line;
            string stationName;
            int duration;
            while (getline(configFile, line)) {
                stringstream ss(line);
                ss >> stationName >> duration;
                inVector.emplace_back(stationName, duration);
            }
            graph_ptr->setConfig(inVector);
            configFile.close();
        } else {
            std::cerr << "Failed to open config file" << std::endl;
        }
    }

    if (outputFileName.empty()) outputFileName = "output.dat";

    //Read input
    for (auto &inputFileName: inputVector) {
        load(graph_ptr, inputFileName);
    }

    //User input
    string command;
    while (cin >> command) {
        if (command == "exit") break;
        if (command == "load") {
            string inputFileName;
            cin>>inputFileName;
            load(graph_ptr, inputFileName);
        }
        else if (command == "outbound"){
            string stationName;
            cin>>stationName;
            graph_ptr->outbound(stationName);
        }
        else if (command == "inbound"){
            string stationName;
            cin>>stationName;
            graph_ptr->outbound(stationName);
        }
        else if (command == "uniExpress"){
            string from, to;
            cin>>from>>to;
            graph_ptr->uniExpress(from, to);
        } else if (command == "multiExpress"){
            string from, to;
            cin>>from>>to;
            graph_ptr->multiExpress(from, to);
        } else if (command == "viaExpress"){
            string from, to, via;
            cin>>from>>to>>via;
            graph_ptr->viaExpress(from, to, via);
        }

    }
//    graph_ptr->uniExpress("CSnoord", "CSzuid");
    //Write output
    ofstream outputFile(outputFileName);
    outputFile << graph_ptr->print();
    outputFile.close();
    return 0;































//    Graph graph = Graph(8,4,5,6);
//    auto inVector = vector<pair<string, int>>();
//    inVector.emplace_back("bus",3);
//    inVector.emplace_back("tram",3);
//    inVector.emplace_back("intercity",8);
//    Graph graph = Graph(inVector);

//    for (char stationName = 'A'; stationName <= 'Z'; ++stationName) {
//        string station = string(1, stationName);
//        graph.addStation(station);
//    }

    // Добавляем рёбра между станциями
//    graph.addEdge("ICA", "CSA", 0, 5);
//    graph.addEdge("CSA", "C", 0, 3);
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
//    graph.addEdge("ICA", "Z", 1, 10);

    // Выполняем операции с графом
//    graph.viaExpress("ICA", "M", "C"); // Путь от A до E через C
//    graph.multiExpress("ICA", "J");    // Множественный кратчайший путь от A до E
//
//    graph.uniExpress("ICA", "J");      // Универсальный кратчайший путь от A до E

//    graph.addEdge("ICA", "CSA", 0, 7);
//    graph.addEdge("ICA", "CSA", 1, 3);
//    graph.addEdge("ICA", "CSA", 2, 1);
//    graph.addEdge("ICA", "CSA", 3, 1);
//    graph.addEdge("CSA", "C", 0, 10);
//    graph.addEdge("CSA", "C", 1, 1);
//    graph.addEdge("C", "D", 0, 5);
//    graph.addEdge("C", "D", 1, 100);
//    graph.addEdge("ICA", "D", 3,2);
//    graph.addEdge("D", "C", 2,2);
//
//    graph.multiExpress("ICA", "C");
//
//    graph.uniExpress("ICA", "C");
//    graph.viaExpress("CSA", "D", "C");
//    graph.inbound("ICA");
//    graph.outbound("CSA");
//    cout<<endl;
//
//
//    graph.print();
//    for(const auto& station: vector){
//        cout<<station<<"\t";
//    }
//






//    graph.addEdge("ICA", "CSA", 1, 1);
//    graph.addEdge("ICA", "CSA", 0, 3);
//    graph.addEdge("CSA", "C", 1, 10);
//    graph.addEdge("CSA", "C", 0, 1);
//    graph.addEdge("C", "D", 1, 3);
//    graph.addEdge("D", "ICA", 1, 4);
//    graph.addEdge("CSA", "E", 1, 5);
//    graph.addEdge("M", "E", 1, 6);
//    graph.addEdge("CSA", "D", 1, 3);
//    graph.print();
//    graph.bfs("E", true);

//    graph.print();
//    auto v = graph.dijkstraMulti("ICA", vector<pair<int, int>>());
//    for( const auto& i:v){
//        cout<<i.first<< " "<<i.second<<endl;
//    }
//    graph.bfs("E", true);
    return 0;
}
