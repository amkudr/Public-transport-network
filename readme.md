# Public Transport Network Simulation 

## Project Overview

This project simulates a public transport network in a metropolitan area using **C++** with an object-oriented approach. It models transportation routes, stations, and various transport types, providing the ability to perform queries on the network, such as shortest routes and connectivity.

## Features

- **Graph-based Network**: The public transport network is represented as a graph with nodes (stations) and edges (routes).
- **Transport Modes**: Bus, tram, sprinter, and rail are modeled, each with different stop and transit times.
- **Queries**: Support for various queries like shortest path, connected nodes, and transit switching times.
- **Error Handling**: Input validation and exception handling using C++'s modern exception mechanism.
- **Optimized Performance**: Emphasizes efficiency using move semantics and smart pointers.

## Simulation Objects

### Transport Modes:
- **Bus**: Default stop time - 2 minutes.
- **Tram**: Default stop time - 3 minutes.
- **Sprinter**: Default stop time - 4 minutes.
- **Rail**: Default stop time - 5 minutes.

### Station Types:
- **Intercity Station**: Default transit time - 15 minutes.
- **City Station**: Default transit time - 10 minutes.
- **Central Station**: Default transit time - 5 minutes.

## Command Line Usage

After compiling, the program is run through the terminal. It accepts multiple input files describing the transport network, with options for configuration and output files.

### Example Usage:
```C++
$ ./netOmsterdam -i <infile1> [<infile2> <infile3> ...] [-c <config_file>] [-o <outfile>]
```
### Input Files:
Each input file should describe routes between stations using the format:
```C++
<source_node> <TAB> <target_node> <TAB> <duration>
```
Example Input File:
```C++
Westzijde    Prinsengracht    10
RAI          CSzuid           20
```
##User Interaction
The program supports several commands for interacting with the network:

###Loading New Data:
```C++
load <filename>
```
## User Commands (Terminal Interaction)

Once the program is running, it supports the following user commands through terminal input:

**Load Network Data**: Load additional network data from a file. ```load <filename> ```

**Outbound Query**: List all stations reachable from a given station. ```outbound <station> ```

**Inbound Query**: List all stations that can reach a given station. ```inbound <station> ```

**Shortest Path**: Calculate the shortest travel time between two stations. ```uniExpress <source_station> <destination_station> ```

**Shortest Path with Transit**: Calculate the shortest path with transit between two stations. ```multiExpress <source_station> <destination_station> ```

**Via Query**: Find the shortest path between two stations that passes through an intermediate station. ```viaExpress <source_station> <transit_station> <destination_station> ```

## Output File

Upon receiving certain commands, such as printing the network, the program will write the output to the specified file or to the default `output.dat` file. The format of the output is customizable and will be generated based on the current state of the network.

## Compilation

To ensure compatibility with the server, the code must be compiled using the following flags:

```g++ -std=c++11 -o netOmsterdam main.cpp graph.cpp queries.cpp ```
