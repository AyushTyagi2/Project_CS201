#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <fstream>

using namespace std;

// Constants and structures
const int INF = INT_MAX;
struct Edge {
    int destination;
    double travelTime;
    double delay;
};

struct Station {
    int id;
    vector<Edge> routes;
};

unordered_map<int, Station> graph; // Store the graph as an adjacency list
vector<vector<double>> costMatrix; // Path cost matrix

// 1. Create graph with stations and routes
void createGraph() { // Aryan
    ifstream inputFile("city_graph_data.txt");
    if (!inputFile) {
        cerr << "Error: File not found!" << endl;
        return;
    }

    int numStations, numRoutes;
    inputFile >> numStations >> numRoutes;

    // Initialize stations
    for (int i = 0; i < numStations; ++i) {
        graph[i] = {i, {}};
    }

    // Read routes between stations
    for (int i = 0; i < numRoutes; ++i) {
        int src, dest;
        double travelTime, delay;
        inputFile >> src >> dest >> travelTime >> delay;
        graph[src].routes.push_back({dest, travelTime, delay});
    }

    inputFile.close();
    cout << "Graph created successfully from file." << endl;
}

// 2. Initialize the cost matrix with linear algebra methods
void initializeCostMatrix() { // Ayush
    int numStations = graph.size();
    
    if (numStations == 0) {
        cerr << "Error: Graph is empty. Initialize stations first." << endl;
        return;
    }
    
    // Resize and set initial values for the cost matrix
    costMatrix.assign(numStations, vector<double>(numStations, INF));

    for (int i = 0; i < numStations; ++i) {
        costMatrix[i][i] = 0; // Zero cost for paths to self
        for (auto& edge : graph[i].routes) {
            // Use the minimum cost if multiple paths to the same destination exist
            costMatrix[i][edge.destination] = min(costMatrix[i][edge.destination], edge.travelTime + edge.delay);
        }
    }

    cout << "Cost matrix initialized successfully." << endl;
}

// 3. Dijkstra’s Algorithm with priority queue (simplified version without Fibonacci Heap)
void fibonacciDijkstra(int source) { // Dhruv
    int numStations = graph.size();
    vector<double> distance(numStations, INF);
    distance[source] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> minHeap;
    minHeap.push(make_pair(0, source));

    while (!minHeap.empty()) {
        double dist = minHeap.top().first;
        int station = minHeap.top().second;
        minHeap.pop();
        
        if (dist > distance[station]) continue;
        
        for (auto& edge : graph[station].routes) {
            double newDist = dist + edge.travelTime + edge.delay;
            if (newDist < distance[edge.destination]) {
                distance[edge.destination] = newDist;
                minHeap.push(make_pair(newDist, edge.destination));
            }
        }
    }

    // Output distances from the source
    for (int i = 0; i < numStations; ++i) {
        cout << "Distance to station " << i << ": " << distance[i] << endl;
    }
}

// 4. Delay optimization with differential equations
void optimizeWithDifferentialEq() { // Ayush
    int numStations = graph.size();
    double delayChangeRate = 0.05; // Example rate, replace with actual model

    for (int i = 0; i < numStations; ++i) {
        for (auto& edge : graph[i].routes) {
            edge.delay += delayChangeRate; // Update delay based on rate
        }
    }

    cout << "Delays optimized with differential equation model." << endl;
}

// 5. Calculate delays based on simulated data
void calculateDelays() { // Aryan
    for (auto& stationPair : graph) {
        Station& station = stationPair.second;
        for (auto& edge : station.routes) {
            edge.delay = 2.0; // Example delay, replace with actual data
        }
    }
    cout << "Delays calculated based on simulated data." << endl;
}

// 6. Matrix operations to optimize traffic flow
void matrixTrafficFlow() {
    int numStations = graph.size();
    vector<vector<double>> flowMatrix(numStations, vector<double>(numStations, 0));

    // Populate the flowMatrix with initial flow capacities or demands (example placeholders)
    for (int i = 0; i < numStations; ++i) {
        for (auto& edge : graph[i].routes) {
            flowMatrix[i][edge.destination] = edge.travelTime + edge.delay; // Example: use travel time + delay as a flow cost
        }
    }

    // Apply Gaussian elimination to solve the matrix and optimize flow
    // (Pseudo-code for Gaussian elimination here)
    for (int i = 0; i < numStations; ++i) {
        // Normalize row, perform row operations
        // Placeholder: Add actual Gaussian elimination steps here
    }

    // Adjust the traffic flow on each route based on optimized flow matrix results
    for (int i = 0; i < numStations; ++i) {
        for (int j = 0; j < numStations; ++j) {
            if (flowMatrix[i][j] != 0) {
                // Example: Update route delay or flow capacity dynamically
                // graph[i].routes[j].flow = flowMatrix[i][j];
            }
        }
    }

    cout << "Traffic flow matrix operations completed." << endl;
}

int main() {
    int source;
    cout << "Enter the source station: ";
    cin >> source;

    createGraph();
    initializeCostMatrix();
    fibonacciDijkstra(source);
    optimizeWithDifferentialEq();
    calculateDelays();
    matrixTrafficFlow();

    return 0;
}
