#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    string name;
    double x, y;
};

class TrafficSystem {
    unordered_map<int, vector<pair<int, double>>> adjList;
    unordered_map<int, Node> nodes;
    map<string, int> locationMap;

public:
    void addNode(int id, const string &name, double x, double y) {
        nodes[id] = {id, name, x, y};
        locationMap[name] = id;
    }

    void addRoad(const string &u, const string &v, double weight) {
        if (locationMap.find(u) == locationMap.end() || locationMap.find(v) == locationMap.end()) {
            cout << "Error: One of the locations does not exist.\n";
            return;
        }
        int uID = locationMap[u];
        int vID = locationMap[v];
        adjList[uID].push_back({vID, weight});
        adjList[vID].push_back({uID, weight});
    }

    // Remove heuristic logic (Pure Dijkstra's algorithm)
    vector<int> aStar(const string &startLocation, const string &goalLocation) {
        if (locationMap.find(startLocation) == locationMap.end() || locationMap.find(goalLocation) == locationMap.end()) {
            cout << "Invalid start or destination location!" << endl;
            return {};
        }

        int start = locationMap[startLocation];
        int goal = locationMap[goalLocation];

        unordered_map<int, double> gCost;
        unordered_map<int, double> fCost;
        unordered_map<int, int> parent;
        for (auto &[id, _] : nodes) {
            gCost[id] = numeric_limits<double>::infinity();
            fCost[id] = numeric_limits<double>::infinity();
        }
        gCost[start] = 0;
        fCost[start] = 0;  // Ignore heuristic here (Dijkstra's behavior)

        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> openSet;
        openSet.push({fCost[start], start});
        parent[start] = -1;

        while (!openSet.empty()) {
            int current = openSet.top().second;
            openSet.pop();

            if (current == goal) {
                vector<int> path;
                for (int at = goal; at != -1; at = parent[at]) {
                    path.push_back(at);
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (auto &[neighbor, weight] : adjList[current]) {
                double tentativeGCost = gCost[current] + weight;
                if (tentativeGCost < gCost[neighbor]) {
                    parent[neighbor] = current;
                    gCost[neighbor] = tentativeGCost;
                    fCost[neighbor] = gCost[neighbor];  // Pure Dijkstra's
                    openSet.push({fCost[neighbor], neighbor});
                }
            }
        }

        return {};
    }

    void displayPath(const vector<int> &path) {
        if (path.empty()) {
            cout << "No path found.\n";
            return;
        }
        cout << "Shortest Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << nodes[path[i]].name;
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    void displaySystem() {
        cout << "\nLocations:\n";
        for (const auto &entry : nodes) {
            cout << "ID: " << entry.first << ", Name: " << entry.second.name
                 << ", Coordinates: (" << entry.second.x << ", " << entry.second.y << ")\n";
        }

        cout << "\nRoads:\n";
        for (const auto &entry : adjList) {
            cout << "Node " << nodes[entry.first].name << " connects to:\n";
            for (const auto &[neighbor, weight] : entry.second) {
                cout << "  -> " << nodes[neighbor].name << " with distance " << weight << "\n";
            }
        }
        cout << endl;
    }
};

int main() {
    TrafficSystem system;
    system.addNode(1, "Begum Bridge", 28.9900, 77.7100);
    system.addNode(2, "Meerut Cantt", 28.9853, 77.7050);
    system.addNode(3, "Shastri Nagar", 28.9800, 77.7200);
    system.addNode(4, "Modipuram", 29.0500, 77.7000);
    system.addNode(5, "Subharti University", 29.0300, 77.6900);
    system.addNode(6, "Hapur Adda", 28.9600, 77.7400);
    system.addNode(7, "Hapur", 28.7500, 77.7800);
    system.addNode(8, "Muradnagar", 28.7800, 77.6000);
    system.addNode(9, "Modinagar", 28.8300, 77.5800);
    system.addNode(10, "Ghaziabad Junction", 28.6700, 77.4400);

    // Road connections between locations with distances
    system.addRoad("Begum Bridge", "Meerut Cantt", 2.0);
    system.addRoad("Meerut Cantt", "Shastri Nagar", 1.5);
    system.addRoad("Shastri Nagar", "Hapur Adda", 2.5);
    system.addRoad("Begum Bridge", "Modipuram", 5.0);
    system.addRoad("Modipuram", "Subharti University", 3.0);
    system.addRoad("Subharti University", "Meerut Cantt", 4.0);
    system.addRoad("Hapur Adda", "Hapur", 15.0);
    system.addRoad("Hapur", "Muradnagar", 20.0);
    system.addRoad("Muradnagar", "Modinagar", 10.0);
    system.addRoad("Modinagar", "Ghaziabad Junction", 15.0);
    system.addRoad("Hapur Adda", "Muradnagar", 25.0);

    system.displaySystem();

    string startLocation, goalLocation;
    cout << "Enter starting location: ";
    getline(cin, startLocation);
    cout << "Enter destination location: ";
    getline(cin, goalLocation);

    vector<int> path = system.aStar(startLocation, goalLocation);
    system.displayPath(path);

    return 0;
}
