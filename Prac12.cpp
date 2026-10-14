
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

const int INF = 1000000000;

int tsp(int mask, int pos, int V,
        vector<vector<int>> &cost,
        vector<vector<int>> &dp,
        int &operations)
{
    // All cities visited: return to starting city
    if(mask == (1 << V) - 1)
    {
        if(cost[pos][0] == -1)
            return INF;

        return cost[pos][0];
    }

    if(dp[mask][pos] != -1)
        return dp[mask][pos];

    int answer = INF;

    for(int city = 0; city < V; city++)
    {
        operations++;

        // Visit only unvisited cities with an available edge
        if((mask & (1 << city)) == 0 &&
           cost[pos][city] != -1)
        {
            int remaining = tsp(
                mask | (1 << city), city, V,
                cost, dp, operations
            );

            if(remaining != INF)
            {
                int total = cost[pos][city] + remaining;

                if(total < answer)
                    answer = total;
            }
        }
    }

    dp[mask][pos] = answer;
    return answer;
}

int main()
{
    int V;

    cout << "Enter number of cities: ";
    cin >> V;

    if(V < 2 || V > 20)
    {
        cout << "Enter cities between 2 and 20.";
        return 0;
    }

    vector<vector<int>> cost(V, vector<int>(V));

    cout << "Enter cost matrix (-1 for no path):\n";

    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            cin >> cost[i][j];

            if(cost[i][j] < -1)
            {
                cout << "Invalid edge cost.";
                return 0;
            }

            if(i == j)
                cost[i][j] = -1;
        }
    }

    vector<vector<int>> dp(1 << V, vector<int>(V, -1));

    int operations = 0;

    auto start = high_resolution_clock::now();

    int minimumCost = tsp(
        1, 0, V, cost, dp, operations
    );

    auto end = high_resolution_clock::now();

    auto timeTaken =
        duration_cast<nanoseconds>(end - start);

    if(minimumCost == INF)
    {
        cout << "\nNo complete tour exists.\n";
    }
    else
    {
        cout << "\nMinimum Tour Cost: " << minimumCost << "\n";
    }

    cout << "Operations       : " << operations;
    cout << "\nExecution Time   : " << timeTaken.count() << " ns";
    cout << "\nTime Complexity  : O(V^2 * 2^V)";
    cout << "\nSpace Complexity : O(V * 2^V)\n";

    return 0;
}
