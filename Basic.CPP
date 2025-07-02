#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <fstream>

using namespace std;

// Constants and Structures
const int INF = INT_MAX;  // Infinite value for initialization

struct Edge {
    int destination;
    double travelTime;
    double delay;
};

struct Station {
    int id;
    vector<Edge> routes;
};

// Global Variables
unordered_map<int, Station> graph; // Store the graph as an adjacency list
vector<vector<double>> costMatrix; // Path cost matrix

// Step 1: Graph Representation
void createGraph() { 
    ifstream inputFile("city_graph_data.txt");
    if (!inputFile) {
        cerr << "Error: File not found!" << endl;
        return;
    }

    int numStations, numRoutes;
    inputFile >> numStations >> numRoutes;

    // Initialize stations
    for (int i = 0; i < numStations; ++i) {
        graph[i] = {i, {}}; // Each station has an empty list of routes initially
    }

    // Read routes from the input file
    for (int i = 0; i < numRoutes; ++i) {
        int src, dest;
        double travelTime, delay;
        inputFile >> src >> dest >> travelTime >> delay;
        graph[src].routes.push_back({dest, travelTime, delay});
    }

    inputFile.close();
    cout << "Graph created successfully from file." << endl;
}

// Step 2: Initialize Cost Matrix with Routes
void initializeCostMatrix() {
    int numStations = graph.size();

    if (numStations == 0) {
        cerr << "Error: Graph is empty." << endl;
        return;
    }

    // Resize and set initial values for the cost matrix
    costMatrix.assign(numStations, vector<double>(numStations, INF));

    for (int i = 0; i < numStations; ++i) {
        costMatrix[i][i] = 0; // Zero cost for paths to self
        for (auto& edge : graph[i].routes) {
            // Update the cost matrix with the minimum travel time + delay for each route
            costMatrix[i][edge.destination] = min(costMatrix[i][edge.destination], edge.travelTime + edge.delay);
        }
    }

    cout << "Cost matrix initialized successfully." << endl;
}

// Step 3: Dijkstra’s Algorithm (Using Priority Queue)
void fibonacciDijkstra(int source) {
    int numStations = graph.size();
    vector<double> distance(numStations, INF);  // Initialize distances to infinity
    distance[source] = 0;

    // Min-heap priority queue to select the station with the smallest distance
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> minHeap;
    minHeap.push(make_pair(0, source));  // (distance, station)

    while (!minHeap.empty()) {
        double dist = minHeap.top().first;
        int station = minHeap.top().second;
        minHeap.pop();

        // Ignore if the distance is already updated with a smaller value
        if (dist > distance[station]) continue;

        // Traverse all neighbors of the current station
        for (auto& edge : graph[station].routes) {
            double newDist = dist + edge.travelTime + edge.delay;
            if (newDist < distance[edge.destination]) {
                distance[edge.destination] = newDist;
                minHeap.push(make_pair(newDist, edge.destination));
            }
        }
    }

    // Output the shortest distances from the source station
    cout << "Shortest distances from station " << source << ":\n";
    for (int i = 0; i < numStations; ++i) {
        cout << "To station " << i << ": " << (distance[i] == INF ? -1 : distance[i]) << endl;
    }
}

// Step 4: Real-Time Updates for Delays
void updateDelays(double delayChangeRate) {
    for (auto& stationPair : graph) {
        Station& station = stationPair.second;
        for (auto& edge : station.routes) {
            edge.delay += delayChangeRate; // Update delay dynamically
        }
    }
    cout << "Delays updated with change rate: " << delayChangeRate << endl;
}

// Main Function
int main() {
    int source;
    double delayChangeRate;

    cout << "Enter the source station: ";
    cin >> source;

    cout << "Enter the delay change rate (e.g., 0.05): ";
    cin >> delayChangeRate;

    createGraph();           // Step 1: Create the graph
    initializeCostMatrix();   // Step 2: Initialize the cost matrix
    fibonacciDijkstra(source); // Step 3: Run Dijkstra's algorithm
    updateDelays(delayChangeRate); // Step 4: Update delays in real-time

    // Optional: Re-run Dijkstra after delay updates if needed
    cout << "\nRe-running Dijkstra after delay updates...\n";
    fibonacciDijkstra(source);

    return 0;
}
