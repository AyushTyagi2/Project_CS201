<<<<<<< HEAD
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
=======
#include <bits/stdc++.h>
using namespace std;

// Edge structure representing a route in the railway network
>>>>>>> 7fd9ae40482b6402b0000d1c3eafce087fbf0f95
struct Edge {
    int destination;
    double travelTime;
    double delay;
};

<<<<<<< HEAD
=======
// Station structure containing id, routes, and delays
>>>>>>> 7fd9ae40482b6402b0000d1c3eafce087fbf0f95
struct Station {
    int id;
    vector<Edge> routes;
};

<<<<<<< HEAD
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
=======

// Constants and global variables
const double INF = numeric_limits<double>::infinity();
unordered_map<int, Station> graph;
vector<vector<double>> costMatrix; 
vector<double> delays;

// Create the railway network graph from the input file
void createGraph(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    int n, s;
    file >> n >> s;  

    for (int i = 0; i < n; ++i) {
        graph[i] = Station{i, {}};
    }
    
    for (int i = 0; i < s; ++i) {
        int u, v;
        double travelTime, delay;
        file >> u >> v >> travelTime >> delay;

        if (u < 0 || v < 0 || u >= n || v >= n || travelTime < 0 || delay < 0) {
            cout << "Invalid input at line " << i + 2 << ". Skipping this entry.\n";
            continue;
        }

        graph[u].routes.push_back({v, travelTime, delay});
    }

    delays.resize(n);
    cout << "Reading delays for each station from the last line of the file...\n";
    for (int i = 0; i < n; ++i) {
        file >> delays[i];
        cout << "Delay for station " << i << ": " << delays[i] << endl;
    }

    file.close();
}

struct FibNode {
    int id;
    double key;
    FibNode* next;
    FibNode* prev;
    FibNode* child;
    FibNode* parent;
    int degree;
    bool mark;

    FibNode(int id, double key) : id(id), key(key), next(this), prev(this),
    child(nullptr), parent(nullptr), degree(0), mark(false) {}
};

struct FibonacciHeap {
    FibNode* minNode;
    int nodeCount;

    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

    bool isEmpty() const {
        return minNode == nullptr;
    }

    void insert(FibNode* node) {
        if (isEmpty()) {
            minNode = node;
        } else {
            node->next = minNode->next;
            node->prev = minNode;
            minNode->next->prev = node;
            minNode->next = node;
            if (node->key < minNode->key) {
                minNode = node;
            }
        }
        nodeCount++;
    }

    void link(FibNode* child, FibNode* parent) {
        // Remove child from root list
        child->prev->next = child->next;
        child->next->prev = child->prev;

        // Make child the new child of parent
        child->parent = parent;
        if (parent->child == nullptr) {
            parent->child = child;
            child->next = child;
            child->prev = child;
        } else {
            child->next = parent->child->next;
            child->prev = parent->child;
            parent->child->next->prev = child;
            parent->child->next = child;
        }

        parent->degree++;
        child->mark = false;
    }

    void consolidate() {
        if (minNode == nullptr) return;

        int maxDegree = static_cast<int>(log2(nodeCount)) + 1;
        vector<FibNode*> degreeTable(maxDegree, nullptr);

        //Iterate through the root list and consolidate nodes with the same degree
        vector<FibNode*> rootList;
        FibNode* current = minNode;

        do {
            rootList.push_back(current);
            current = current->next;
        } while (current != minNode);

        for (FibNode* node : rootList) {
            int d = node->degree;

            //Keep merging until we find an empty spot in the degree table
            while (degreeTable[d] != nullptr) {
                FibNode* other = degreeTable[d];
                
                // Make sure `node` has the smaller key to maintain min-heap order
                if (node->key > other->key) {
                    swap(node, other);
                }
                link(other, node);
                degreeTable[d] = nullptr;
                d++;
            }
            degreeTable[d] = node;
        }

        //Rebuild the root list from the degree table
        minNode = nullptr;
        for (FibNode* node : degreeTable) {
            if (node != nullptr) {
                if (minNode == nullptr) {
                    minNode = node;
                    node->next = node;
                    node->prev = node;
                } else {
                    node->next = minNode->next;
                    node->prev = minNode;
                    minNode->next->prev = node;
                    minNode->next = node;
                    if (node->key < minNode->key) {
                        minNode = node;
                    }
                }
            }
        }
    }


    FibNode* extractMin() {
        FibNode* min = minNode;
        if (min != nullptr) {
            if (min->child) {
                FibNode* child = min->child;
                do {
                    FibNode* nextChild = child->next;
                    // Insert each child into the root list
                    child->prev = minNode->prev;
                    child->next = minNode;
                    minNode->prev->next = child;
                    minNode->prev = child;
                    child->parent = nullptr;
                    child = nextChild;
                } while (child != min->child);
            }

            // Remove min from the root list
            min->prev->next = min->next;
            min->next->prev = min->prev;

            if (min == min->next) {
                minNode = nullptr;
            } else {
                minNode = min->next;
                consolidate();
            }
            nodeCount--;
        }
        return min;
    }

    void cut(FibNode* node, FibNode* parent) {
        if (node == parent->child) {
            parent->child = (node->next != node) ? node->next : nullptr;
        }
        parent->degree--;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = minNode->next;
        node->prev = minNode;
        minNode->next->prev = node;
        minNode->next = node;
        node->parent = nullptr;
        node->mark = false;
    }

    void decreaseKey(FibNode* node, double newKey) {
        if (newKey > node->key) {
            throw invalid_argument("New key is greater than current key");
        }
        node->key = newKey;
        FibNode* parent = node->parent;

        if (parent && node->key < parent->key) {
            cut(node, parent);
            FibNode* ancestor = parent;
            while (ancestor && ancestor->mark) {
                cut(ancestor, ancestor->parent);
                ancestor = ancestor->parent;
            }
            if (ancestor && ancestor->parent) {
                ancestor->mark = true;
            }
        }

        if (node->key < minNode->key) {
            minNode = node;
        }
    }

    int getNodeCount() const {
        return nodeCount;
    }
};

void dijkstra(int start, int target) {
    if (graph.find(start) == graph.end() || graph.find(target) == graph.end()) {
        cout << "One or both stations do not exist." << endl;
        return;
    }

    FibonacciHeap fibHeap;
    unordered_map<int, FibNode*> fibNodes;
    unordered_map<int, double> distances;
    unordered_map<int, int> previous;

    // Initialize nodes and distances
    for (const auto& stationPair : graph) {
        fibNodes[stationPair.first] = new FibNode(stationPair.first, INF);
        fibHeap.insert(fibNodes[stationPair.first]);
        distances[stationPair.first] = INF; // Set initial distances to infinity
    }

    fibNodes[start]->key = 0; // Start from the source node
    fibHeap.decreaseKey(fibNodes[start], 0);
    distances[start] = 0;
    while (!fibHeap.isEmpty()) {
        FibNode* minNode = fibHeap.extractMin();
        int current = minNode->id;

        if (current == target) {
            break; 
        }

        for (const Edge& edge : graph[current].routes) {
            double newDist = distances[current] + edge.travelTime + edge.delay;
            if (newDist < distances[edge.destination]) {
                distances[edge.destination] = newDist;
                previous[edge.destination] = current;
                try {
                    fibHeap.decreaseKey(fibNodes[edge.destination], newDist);
                } catch (const invalid_argument& e) {
                    cerr << e.what() << endl;
                }
            }
        }
    }

    if (distances[target] != INF) {
        cout << "Shortest path from station " << start << " to station " << target << " is " << distances[target] << endl;

        vector<int> path;
        for (int at = target; at != start; at = previous[at]) {
            path.push_back(at);
        }
        path.push_back(start); 

        cout << "Path: ";
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << *it;
            if (it + 1 != path.rend()) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "No path found from station " << start << " to station " << target << endl;
    }
    for (auto& nodePair : fibNodes) {
        delete nodePair.second;
    }
}


// Calculate delays and apply them to edges
void calculateDelays() {
    for (auto& stationPair : graph) {
        Station& station = stationPair.second;
        for (auto& edge : station.routes) {
            edge.delay += delays[station.id] + delays[edge.destination];
        }
    }
}


// Print graph structure to output file
void printGraph(const string& filename, const string& message) {
    ofstream file(filename, ios::trunc); // Change to truncation mode
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    file << message << "\n";
    for (const auto& stationPair : graph) {
        int stationID = stationPair.first;
        const Station& station = stationPair.second;
        file << "Station " << stationID << " -> ";
        for (const auto& edge : station.routes) {
            file << "(" << edge.destination << ", " << edge.travelTime << ", " << edge.delay << ") ";
        }
        file << "\n";
    }
    file << "\n";
    file.close();
}

// Function to get the time-of-day multiplier
double getTimeOfDayMultiplier() {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    int hour = localTime->tm_hour;

    // Adjust based on peak and non-peak hours
    if ((hour >= 7 && hour <= 10) || (hour >= 17 && hour <= 20)) {
        return 1.5;
    } else {
        return 1.0;
    }
}

// Function to optimize delays using a differential equation model
void optimizeWithDifferentialEq() {
    double alpha = 0.02;
    double beta = 0.5;
    double deltaTime = 0.1;
    double timeMultiplier = getTimeOfDayMultiplier();


    for (auto& stationPair : graph) {
        Station& station = stationPair.second;
        for (auto& edge : station.routes) {
            double rateOfChange = alpha * edge.delay + beta;
            edge.delay += deltaTime * rateOfChange* timeMultiplier;
            edge.delay = max(0.0, edge.delay);
        }
    }
>>>>>>> 7fd9ae40482b6402b0000d1c3eafce087fbf0f95
}

void addStation(int id) {
    if (graph.find(id) == graph.end()) {
        graph[id] = Station{id, {}};
        cout << "Station " << id << " added.\n";
    } else {
        cout << "Station " << id << " already exists.\n";
    }
}

void removeStation(int id) {
    if (graph.erase(id) > 0) {
        for (auto& stationPair : graph) {
            auto& routes = stationPair.second.routes;
            routes.erase(remove_if(routes.begin(), routes.end(),
                [id](const Edge& edge) { return edge.destination == id; }), routes.end());
        }
        cout << "Station " << id << " removed.\n";
    } else {
        cout << "Station " << id << " does not exist.\n";
    }
}

void addRoute(int u, int v, double travelTime, double delay) {
    if (graph.find(u) != graph.end() && graph.find(v) != graph.end()) {
        auto& routesU = graph[u].routes;
        bool routeExists = any_of(routesU.begin(), routesU.end(), 
            [v](const Edge& edge) { return edge.destination == v; });
        
        if (!routeExists) {
            routesU.push_back({v, travelTime, delay});
            cout << "One-way route added from station " << u << " to " << v << ".\n";
        } else {
            cout << "Route from " << u << " to " << v << " already exists.\n";
        }
    } else {
        cout << "One or both stations do not exist.\n";
    }
}

void removeRoute(int u, int v) {
    if (graph.find(u) != graph.end() && graph.find(v) != graph.end()) {
        auto& routesU = graph[u].routes;
        auto it = remove_if(routesU.begin(), routesU.end(),
            [v](const Edge& edge) { return edge.destination == v; });
        
        if (it != routesU.end()) {
            routesU.erase(it, routesU.end());
            cout << "One-way route removed from station " << u << " to " << v << ".\n";
        } else {
            cout << "No route from " << u << " to " << v << " exists.\n";
        }
    } else {
        cout << "One or both stations do not exist.\n";
    }
}


void visualizeGraph(const string& outputFile) {
    string dotFileName = "graph.dot";
    ofstream dotFile(dotFileName);
    if (!dotFile.is_open()) {
        cerr << "Error: Could not open dot file for writing.\n";
        return;
    }
    dotFile << "graph RailwayNetwork {\n";
    dotFile << "    node [shape=circle, style=filled, color=lightblue];\n";
    for (const auto& stationPair : graph) {
        int stationID = stationPair.first;
        dotFile << "    " << stationID << " [label=\"Station " << stationID << "\"];\n";
    }
    for (const auto& stationPair : graph) {
        int sourceID = stationPair.first;
        for (const auto& edge : stationPair.second.routes) {
            int destinationID = edge.destination;
            double travelTime = edge.travelTime;
            double delay = edge.delay;
            dotFile << "    " << sourceID << " -- " << destinationID
                    << " [label=\"Time: " << travelTime << ", Delay: " << delay << "\"];\n";
        }
    }

    dotFile << "}\n";
    dotFile.close();

    // Use Graphviz to convert .dot file to an image
    string command = "dot -Tpng " + dotFileName + " -o " + outputFile;
    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error: Failed to generate graph image from DOT file.\n";
    } else {
        cout << "Graph visualized and saved as " << outputFile << "\n";
    }
}


int main() {
<<<<<<< HEAD
    int source;
    cout << "Enter the source station: ";
    cin >> source;

    createGraph();
    initializeCostMatrix();
    fibonacciDijkstra(source);
    optimizeWithDifferentialEq();
    calculateDelays();
    matrixTrafficFlow();

=======
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    createGraph(inputFile);
    calculateDelays();
    printGraph(outputFile, "Initial Graph Structure After Applying Delays:");

    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Find shortest path using Dijkstra's algorithm\n";
        cout << "2. Update delay for a station\n";
        cout << "3. Add station\n";
        cout << "4. Remove station\n";
        cout << "5. Add route\n";
        cout << "6. Remove route\n";
        cout << "7. Display current graph structure\n";
        cout << "8. Real-time delay with Euler's method(choice will depend on the hour of the day)\n";
        cout << "9. Visualize graph\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int start, end;
            cout << "Enter start station ID: ";
            cin >> start;
            cout << "Enter destination station ID: ";
            cin >> end;
            dijkstra(start, end);
        } else if (choice == 2) {
            int station;
            double delay;
            cout << "Enter station ID to update delay: ";
            cin >> station;
            cout << "Enter new delay time: ";
            cin >> delay;
            if (station >= 0 && station < graph.size() && delay >= 0) {
                delays[station] = delay;
                cout << "Delay updated for station " << station << ".\n";
                calculateDelays();
            } else {
                cout << "Invalid station ID or delay time.\n";
            }
        } else if (choice == 3) {
            int id;
            cout << "Enter new station ID: ";
            cin >> id;
            addStation(id);
        } else if (choice == 4) {
            int id;
            cout << "Enter station ID to remove: ";
            cin >> id;
            removeStation(id);
        } else if (choice == 5) {
            int u, v;
            double travelTime, delay;
            cout << "Enter station IDs to connect (u, v): ";
            cin >> u >> v;
            cout << "Enter travel time and delay: ";
            cin >> travelTime >> delay;
            addRoute(u, v, travelTime, delay);
        } else if (choice == 6) {
            int u, v;
            cout << "Enter station IDs to disconnect (u, v): ";
            cin >> u >> v;
            removeRoute(u, v);
        } else if (choice == 7) {
            cout << "Current graph structure:\n";
            printGraph(outputFile, "Current Graph Structure:");
        } else if (choice == 8) {
            optimizeWithDifferentialEq();
            cout << "Real-time delay optimization applied.\n";
            printGraph(outputFile, "Graph Structure After Real-Time Delay Optimization:");
        } else if (choice == 9) {
            cout << "Visualize Graph:\n";
            visualizeGraph("graph.png");
        } else if (choice == 10) {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
>>>>>>> 7fd9ae40482b6402b0000d1c3eafce087fbf0f95
    return 0;
}
