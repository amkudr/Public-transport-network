#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"


//function to load new input files
void load(const shared_ptr<Graph> &graph, string &inputFileName, bool update) {

    ifstream inputFile(inputFileName);
    int type = -1;
    if (inputFileName.substr(0, 3) == "bus") type = 0;
    else if (inputFileName.substr(0, 4) == "tram") type = 1;
    else if (inputFileName.substr(0, 8) == "sprinter") type = 2;
    else if (inputFileName.substr(0, 4) == "rail") type = 3;
    if (type == -1) {
        throw invalid_argument("ERROR opening the specified file.");
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
        if (update) cout<<"Update was successful."<<endl; //if we update current system
    } else {
        throw ifstream::failure("ERROR opening the specified file.");
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
            while (i + 1 < argc && argv[i + 1][0] != '-') {
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

    try {

        //Read config
        if (!configFileName.empty()) {
            ifstream configFile(configFileName);

            if (configFile.is_open()) {
                vector<pair<string, int>> inVector;
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
                throw ifstream::failure("Failed to open config file, file " + configFileName + " does not exist");
            }
        }


        if (outputFileName.empty()) outputFileName = "output.dat";

        //Read input
        auto i = inputVector.size();
        for (auto &inputFileName: inputVector) {
            try {
                load(graph_ptr, inputFileName, false);
            }
            catch (const exception &e) {
                i--;
            }
            if (i == 0) throw invalid_argument("ERROR problem with opening input files");
        }

        //User input
        string command;
        while (cin >> command) {
            try {
                if (command == "exit") break;
                if (command == "load") {
                    string inputFileName;
                    cin >> inputFileName;
                    load(graph_ptr, inputFileName, true);
                } else if (command == "outbound") {
                    string stationName;
                    cin >> stationName;
                    graph_ptr->outbound(stationName);
                } else if (command == "inbound") {
                    string stationName;
                    cin >> stationName;
                    graph_ptr->inbound(stationName);
                } else if (command == "uniExpress") {
                    string from, to;
                    cin >> from >> to;
                    graph_ptr->uniExpress(from, to);
                } else if (command == "multiExpress") {
                    string from, to;
                    cin >> from >> to;
                    graph_ptr->multiExpress(from, to);
                } else if (command == "viaExpress") {
                    string from, to, via;
                    cin >> from >> via >> to;
                    graph_ptr->viaExpress(from, via, to);
                } else if (command == "print") {
                    ofstream outputFile(outputFileName);
                    if (!outputFile.is_open()) {
                        throw ifstream::failure(
                                "Failed to open output file, file " + outputFileName + " does not exist");
                    } else {
                        outputFile << graph_ptr->print();
                        outputFile.close();
                    }
                } else cout << "Unknown command" << endl;
            }
            catch (const invalid_argument &e){
                cerr << e.what() << endl;
            }
        }
    }
    catch (exception &e){
        cerr << e.what() << endl;
        return -1;
    }
    return 0;
}
