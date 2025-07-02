# Dynamic Railway System Pathfinding

This project implements a dynamic railway network pathfinding system using a Fibonacci Heap-based Dijkstra's algorithm to determine optimal travel paths between stations. It incorporates travel times, delays, and dynamic delay optimization based on time-of-day.

## Features
- **Graph-Based Railway Network**: Represents railway stations and routes using a graph with nodes and edges.
- **Dynamic Delays**: Adjusts delays based on station and route characteristics.
- **Peak Hour Delay Multiplier**: Modifies delays during peak travel times.
- **Fibonacci Heap**: Uses a Fibonacci heap to achieve efficient shortest-path calculations.
- **Differential Equation Optimization**: Updates delay values dynamically over time.
  
## Getting Started

### Prerequisites
- **C++ Compiler** (e.g., GCC)
- **Text editor** (e.g., Visual Studio Code)
- **Input file** formatted as described in the "Input Format" section below.

### Compilation
To compile the program, use the following command in your terminal after changing directory to the folder:
```
g++ main.cpp -o main
```
### Running the Program
Run the compiled executable with the input file as an argument:
```
./railway_system <input_filename>
```
Replace `<input_filename>` with the path to your input file.
---
## Input Format
The input file should be structured as follows:
1. **First Line**: Contains two integers:
 - `n`: Number of stations.
 - `s`: Number of routes.
2. **Next `s` Lines**: Each line should contain:
 - `u` and `v`: IDs of the starting and ending stations for the route.
 - `travelTime`: Travel time between stations `u` and `v`.
 - `delay`: Initial delay on the route.
3. **Last Line**: Contains `n` delay values, representing initial delays for each station.
Example:
```
5 6
0 1 10 1
0 2 15 2
1 3 5 0.5
2 3 7 1.5
3 4 10 1
4 0 8 1.2
0.5 1.0 1.2 0.8 1.5
```
---
## Running the Program
Upon running the program, follow the command prompts:
1. **Create Graph**: Initialize the graph using the input file data.
2. **Run Pathfinding (Dijkstra)**: Choose two stations as start and target for pathfinding.
3. **Optimize Delays**: Use differential equation-based optimization to dynamically adjust delays.
### Commands
- **Add Station**: Add a new station node to the network.
- **Remove Station**: Remove a station node and associated routes.
- **Add Route**: Add a new route between two stations.
- **Print Graph**: Save the current graph structure to an output file.
---
## Expected Output
1. **Graph Creation Confirmation**:
 - The program outputs messages confirming each station and route has been successfully read
and added to the graph.
2. **Shortest Path Calculation**:
 - After specifying start and target stations, the program calculates the shortest path based on
travel times and delays.
 - Example Output:
 ```
 Shortest path from station 0 to station 3 is 16.5
 ```
3. **Dynamic Delay Adjustment**:
 - Shows real-time adjustment of delays on each route based on time-of-day factors and
optimization models.

4. **Graph Structure**:
 - When `printGraph` is used, the program saves the graph structure in an output file. The format is:
 ```
 Station 0 -> (1, travelTime: 10, delay: 1.2) (2, travelTime: 15, delay: 3.0)
 Station 1 -> (3, travelTime: 5, delay: 1.5)
 ...
 ```
---
## Functions and Modules
- **createGraph(filename)**: Reads station and route data from a file and builds the graph.
- **dijkstra(start, target)**: Finds the shortest path from the start to target stations using a Fibonacci
heap.
- **calculateDelays()**: Adjusts route delays based on the delay values at connected stations.
- **optimizeWithDifferentialEq()**: Uses differential equations to dynamically update delays over
time.
- **addStation(id)** / **removeStation(id)**: Adds or removes a station.
- **addRoute(u, v, travelTime, delay)**: Adds a route between two stations.
- **printGraph(filename, message)**: Outputs the graph structure to a file.
---
## Additional Notes
- **Error Handling**: The program skips invalid entries in the input file and informs the user of any
issues.
- **Time of Day Multiplier**: Multiplier increases during peak hours (7-10 AM, 5-8 PM), simulating
real-world traffic delays.
- **Station Delays**: Final delays are updated in each run of `optimizeWithDifferentialEq()` and
directly impact the pathfinding calculations.
--- 
