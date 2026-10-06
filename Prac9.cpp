#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    if(V <= 0)
    {
        cout << "Invalid number of vertices.";
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> E;

    if(E < 0)
    {
        cout << "Invalid number of edges.";
        return 0;
    }

    // Vertices are numbered from 1 to V
    vector<vector<int>> graph(V + 1,
                              vector<int>(V + 1, 0));

    cout << "Enter edges (u v weight):\n";

    for(int i = 0; i < E; i++)
    {
        int u, v, weight;

        cin >> u >> v >> weight;

        // Check whether vertices are valid
        if(u < 1 || u > V || v < 1 || v > V)
        {
            cout << "Invalid vertex number.";
            return 0;
        }

        if(weight <= 0)
        {
            cout << "Weight must be positive.";
            return 0;
        }

        // Undirected graph
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    int startVertex;

    cout << "Enter starting vertex: ";
    cin >> startVertex;

    if(startVertex < 1 || startVertex > V)
    {
        cout << "Invalid starting vertex.";
        return 0;
    }


    // ================= PRIM'S ALGORITHM =================

    vector<int> key(V + 1);
    vector<int> parent(V + 1);
    vector<bool> inMST(V + 1, false);

    // Initialize
    for(int i = 1; i <= V; i++)
    {
        key[i] = 1000000;
        parent[i] = -1;
    }

    // Starting vertex
    key[startVertex] = 0;

    int operations = 0;

    auto start = high_resolution_clock::now();


    // Select V vertices
    for(int count = 0; count < V; count++)
    {
        int minimum = 1000000;
        int u = -1;

        // Find vertex with minimum key
        for(int v = 1; v <= V; v++)
        {
            operations++;

            if(!inMST[v] && key[v] < minimum)
            {
                minimum = key[v];
                u = v;
            }
        }

        // No reachable vertex means graph is disconnected
        if(u == -1)
        {
            cout << "\nGraph is disconnected.";
            return 0;
        }

        // Add selected vertex to MST
        inMST[u] = true;


        // Update keys of adjacent vertices
        for(int v = 1; v <= V; v++)
        {
            operations++;

            if(graph[u][v] != 0 &&
               !inMST[v] &&
               graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }


    auto end = high_resolution_clock::now();

    auto timeTaken =
        duration_cast<nanoseconds>(end - start);


    // ================= DISPLAY MST =================

    int totalWeight = 0;

    cout << "\n\n========== PRIM'S MINIMUM SPANNING TREE ==========\n";

    cout << "\nEdge\tWeight\n";

    for(int v = 1; v <= V; v++)
    {
        if(v != startVertex)
        {
            cout << parent[v]
                 << " - "
                 << v
                 << "\t"
                 << graph[parent[v]][v]
                 << "\n";

            totalWeight += graph[parent[v]][v];
        }
    }

    cout << "\nTotal MST Weight : "
         << totalWeight;

    cout << "\nOperations       : "
         << operations;

    cout << "\nExecution Time   : "
         << timeTaken.count()
         << " ns";


    cout << "\n\n========== COMPLEXITY ==========";

    cout << "\nTime Complexity  : O(V^2)";
    cout << "\nSpace Complexity : O(V^2)";

    cout << "\n=================================\n";

    return 0;
}
