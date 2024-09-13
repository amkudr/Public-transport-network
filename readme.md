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
```bash
$ ./netOmsterdam -i <infile1> [<infile2> <infile3> ...] [-c <config_file>] [-o <outfile>]
