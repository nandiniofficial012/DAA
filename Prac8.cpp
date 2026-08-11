#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:

    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }

    // Add an undirected edge
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
//DFS
    void DFS(int start, vector<int> &order, int &edgeChecks)
{
    vector<bool> visited(V, false);

    vector<int> s(V);
    int top = -1;

    s[++top] = start;

    while(top >= 0)
    {
        int node = s[top--];

        if(visited[node])
            continue;

        visited[node] = true;
        order.push_back(node);

        for(int i = adj[node].size() - 1; i >= 0; i--)
        {
            int neighbor = adj[node][i];

            edgeChecks++;

            if(!visited[neighbor])
            {
                s[++top] = neighbor;
            }
        }
    }
}


    // BFS
    void BFS(int start, vector<int> &order, int &edgeChecks)
    {
        vector<bool> visited(V, false);

        // Simple queue using vector
        vector<int> q(V);

        int front = 0;
        int rear = 0;

        visited[start] = true;

        q[rear] = start;
        rear++;

        while(front < rear)
        {
            int node = q[front];
            front++;

            order.push_back(node);

            for(int neighbor : adj[node])
            {
                edgeChecks++;

                if(!visited[neighbor])
                {
                    visited[neighbor] = true;

                    q[rear] = neighbor;
                    rear++;
                }
            }
        }
    }
};

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";

    for(int i = 0; i < E; i++)
    {
        int u, v;

        cin >> u >> v;

        g.addEdge(u, v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    // ---------------- DFS ----------------

    vector<int> dfsOrder;
    int dfsEdgeChecks = 0;

    auto startDFS = high_resolution_clock::now();

    g.DFS(start, dfsOrder, dfsEdgeChecks);

    auto endDFS = high_resolution_clock::now();

    auto dfsTime =
        duration_cast<nanoseconds>(endDFS - startDFS);


    // ---------------- BFS ----------------

    vector<int> bfsOrder;
    int bfsEdgeChecks = 0;

    auto startBFS = high_resolution_clock::now();

    g.BFS(start, bfsOrder, bfsEdgeChecks);

    auto endBFS = high_resolution_clock::now();

    auto bfsTime =
        duration_cast<nanoseconds>(endBFS - startBFS);


    // ---------------- OUTPUT ----------------

    cout << "\nDFS Traversal: ";

    for(int i = 0; i < dfsOrder.size(); i++)
    {
        cout << dfsOrder[i] << " ";
    }

    cout << "\nDFS Vertices Visited: "
         << dfsOrder.size();

    cout << "\nDFS Edge Checks: "
         << dfsEdgeChecks;

    cout << "\nDFS Time: "
         << dfsTime.count() << " ns";


    cout << "\n\nBFS Traversal: ";

    for(int i = 0; i < bfsOrder.size(); i++)
    {
        cout << bfsOrder[i] << " ";
    }

    cout << "\nBFS Vertices Visited: "
         << bfsOrder.size();

    cout << "\nBFS Edge Checks: "
         << bfsEdgeChecks;

    cout << "\nBFS Time: "
         << bfsTime.count() << " ns";

    return 0;
}