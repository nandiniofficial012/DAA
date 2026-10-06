#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

struct Edge
{
    int u;
    int v;
    int weight;
};

// Find parent of a vertex
int findParent(vector<int> &parent, int x)
{
    while(parent[x] != x)
    {
        x = parent[x];
    }

    return x;
}

// Union two sets using rank
void unionSets(vector<int> &parent, vector<int> &rank, int a, int b)
{
    a = findParent(parent, a);
    b = findParent(parent, b);

    if(a == b)
        return;

    if(rank[a] < rank[b])
    {
        parent[a] = b;
    }
    else if(rank[a] > rank[b])
    {
        parent[b] = a;
    }
    else
    {
        parent[b] = a;
        rank[a]++;
    }
}

// Heapify for Max Heap
void heapify(vector<Edge> &edges, int n, int i, int &operations)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare left child
    if(left < n)
    {
        operations++;

        if(edges[left].weight > edges[largest].weight)
            largest = left;
    }

    // Compare right child
    if(right < n)
    {
        operations++;

        if(edges[right].weight > edges[largest].weight)
            largest = right;
    }

    // If largest is not the root, swap
    if(largest != i)
    {
        Edge temp = edges[i];
        edges[i] = edges[largest];
        edges[largest] = temp;

        operations++;

        heapify(edges, n, largest, operations);
    }
}

// Manual Heap Sort
void heapSort(vector<Edge> &edges, int &operations)
{
    int n = edges.size();

    // Build Max Heap
    for(int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(edges, n, i, operations);
    }

    // Extract elements one by one
    for(int i = n - 1; i > 0; i--)
    {
        Edge temp = edges[0];
        edges[0] = edges[i];
        edges[i] = temp;

        operations++;

        heapify(edges, i, 0, operations);
    }
}

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

    vector<Edge> edges(E);

    cout << "Enter edges (u v weight):\n";

    for(int i = 0; i < E; i++)
    {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;

        if(edges[i].u < 1 || edges[i].u > V ||
           edges[i].v < 1 || edges[i].v > V)
        {
            cout << "Invalid vertex number.";
            return 0;
        }

        if(edges[i].weight <= 0)
        {
            cout << "Weight must be positive.";
            return 0;
        }
    }

    // Parent and rank arrays for Union-Find
    vector<int> parent(V + 1);
    vector<int> rank(V + 1, 0);

    for(int i = 1; i <= V; i++)
    {
        parent[i] = i;
    }

    vector<Edge> mst;

    int operations = 0;
    int mstEdges = 0;
    int totalWeight = 0;

    // Start measuring algorithm time
    auto start = high_resolution_clock::now();

    // Sort edges using manual Heap Sort
    heapSort(edges, operations);

    // Kruskal's Algorithm
    for(int i = 0; i < E; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        int parentU = findParent(parent, u);
        int parentV = findParent(parent, v);

        operations++;

        // If different components, include edge
        if(parentU != parentV)
        {
            unionSets(parent, rank, parentU, parentV);

            mst.push_back(edges[i]);

            totalWeight += weight;
            mstEdges++;

            // MST contains V-1 edges
            if(mstEdges == V - 1)
                break;
        }
    }

    auto end = high_resolution_clock::now();

    auto timeTaken =
        duration_cast<nanoseconds>(end - start);

    // Check if graph is connected
    if(mstEdges != V - 1)
    {
        cout << "\nGraph is disconnected.";
        return 0;
    }

    // Display sorted edges
    cout << "\n\n========== KRUSKAL'S MST ==========\n";

    cout << "\nSorted Edges:\n";

    for(int i = 0; i < E; i++)
    {
        cout << edges[i].u
             << " - "
             << edges[i].v
             << " : "
             << edges[i].weight
             << "\n";
    }

    // Display MST
    cout << "\nMST Edges:\n";

    for(int i = 0; i < mst.size(); i++)
    {
        cout << mst[i].u
             << " - "
             << mst[i].v
             << " : "
             << mst[i].weight
             << "\n";
    }

    cout << "\nTotal MST Weight : "
         << totalWeight;

    cout << "\nMST Edges        : "
         << mstEdges;

    cout << "\nOperations       : "
         << operations;

    cout << "\nExecution Time   : "
         << timeTaken.count()
         << " ns";

    cout << "\n\n========== COMPLEXITY ==========";

    cout << "\nTime Complexity  : O(E log E)";

    cout << "\nSpace Complexity : O(V + E)";

    cout << "\n=================================\n";

    return 0;
}
