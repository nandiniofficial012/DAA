
#include <iostream>
#include <vector>
using namespace std;

const int INF = 1000000000;

int main()
{
    int V;

    cout << "Enter number of vertices: ";
    cin >> V;

    if(V <= 0)
    {
        cout << "Invalid number of vertices.";
        return 0;
    }

    vector<vector<int>> dist(V, vector<int>(V));

    cout << "Enter adjacency matrix (-1 for no edge):\n";

    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            cin >> dist[i][j];

            if(i == j)
                dist[i][j] = 0;
            else if(dist[i][j] == -1)
                dist[i][j] = INF;
        }
    }

    int operations = 0;

    // Floyd-Warshall Algorithm
    for(int k = 0; k < V; k++)
    {
        for(int i = 0; i < V; i++)
        {
            // Optimization 1: Skip unreachable paths
            if(dist[i][k] == INF)
                continue;

            for(int j = 0; j < V; j++)
            {
                operations++;

                // Optimization 2: Skip unreachable destinations
                if(dist[k][j] == INF)
                    continue;

                int newDistance = dist[i][k] + dist[k][j];

                if(newDistance < dist[i][j])
                {
                    dist[i][j] = newDistance;
                }
            }
        }
    }

    cout << "\nShortest Distance Matrix:\n";

    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            if(dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }

        cout << "\n";
    }

    cout << "\nOperations       : " << operations;
    cout << "\nTime Complexity  : O(V^3)";
    cout << "\nSpace Complexity : O(V^2)\n";

    return 0;
}
