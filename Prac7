#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;


// ================= DYNAMIC PROGRAMMING =================

int dpCoinChange(vector<int> &coins,
                 int amount,
                 int &operations,
                 vector<int> &dp)
{
    int inf = amount + 1;

    // Create DP table
    dp.resize(amount + 1);

    // Base case
    dp[0] = 0;

    // Initialize remaining values
    for(int i = 1; i <= amount; i++)
        dp[i] = inf;


    // Build DP table
    for(int i = 1; i <= amount; i++)
    {
        for(int j = 0; j < coins.size(); j++)
        {
            operations++;

            if(coins[j] <= i)
            {
                int value = dp[i - coins[j]] + 1;

                if(value < dp[i])
                    dp[i] = value;
            }
        }
    }


    if(dp[amount] == inf)
        return -1;

    return dp[amount];
}


// ================= PRINT DP COINS =================

void printDPCoins(vector<int> &coins,
                 vector<int> &dp,
                 int amount)
{
    int remaining = amount;

    while(remaining > 0)
    {
        bool found = false;

        for(int i = 0; i < coins.size(); i++)
        {
            if(coins[i] <= remaining &&
               dp[remaining] == dp[remaining - coins[i]] + 1)
            {
                cout << coins[i] << " ";

                remaining = remaining - coins[i];

                found = true;

                break;
            }
        }

        // Safety condition
        if(!found)
            break;
    }
}


// ================= GREEDY =================

int greedyCoinChange(vector<int> &coins,
                     int amount,
                     int &operations)
{
    int remaining = amount;
    int count = 0;

    while(remaining > 0)
    {
        int largest = -1;

        // Find largest coin that fits
        for(int i = 0; i < coins.size(); i++)
        {
            operations++;

            if(coins[i] <= remaining)
            {
                if(largest == -1 || coins[i] > largest)
                    largest = coins[i];
            }
        }

        // No coin can make the remaining amount
        if(largest == -1)
            return -1;

        remaining = remaining - largest;

        count++;
    }

    return count;
}


// ================= PRINT GREEDY COINS =================

void printGreedyCoins(vector<int> &coins,
                      int amount)
{
    int remaining = amount;

    while(remaining > 0)
    {
        int largest = -1;

        for(int i = 0; i < coins.size(); i++)
        {
            if(coins[i] <= remaining)
            {
                if(largest == -1 || coins[i] > largest)
                    largest = coins[i];
            }
        }

        if(largest == -1)
        {
            cout << "Not Possible";
            return;
        }

        cout << largest << " ";

        remaining = remaining - largest;
    }
}


// ================= MAIN =================

int main()
{
    int n;

    cout << "Enter number of coin types: ";
    cin >> n;

    if(n <= 0)
    {
        cout << "Invalid number of coin types.\n";
        return 0;
    }


    vector<int> coins(n);

    cout << "Enter coins in any order:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> coins[i];

        if(coins[i] <= 0)
        {
            cout << "Coins must be positive.\n";
            return 0;
        }
    }


    int amount;

    cout << "Enter amount: ";
    cin >> amount;

    if(amount < 0)
    {
        cout << "Amount cannot be negative.\n";
        return 0;
    }


    // ================= DP =================

    int dpOperations = 0;

    vector<int> dp;

    auto startDP = high_resolution_clock::now();

    int dpResult =
        dpCoinChange(coins,
                     amount,
                     dpOperations,
                     dp);

    auto endDP = high_resolution_clock::now();


    // ================= GREEDY =================

    int greedyOperations = 0;

    auto startGreedy = high_resolution_clock::now();

    int greedyResult =
        greedyCoinChange(coins,
                         amount,
                         greedyOperations);

    auto endGreedy = high_resolution_clock::now();


    // ================= TIME =================

    auto dpTime =
        duration_cast<nanoseconds>(endDP - startDP);

    auto greedyTime =
        duration_cast<nanoseconds>(endGreedy - startGreedy);


    // ================= DP OUTPUT =================

    cout << "\n========== DYNAMIC PROGRAMMING ==========\n";

    if(dpResult == -1)
    {
        cout << "Minimum Coins : Not Possible\n";
        cout << "Coins Used    : Not Possible\n";
    }
    else
    {
        cout << "Minimum Coins : "
             << dpResult << endl;

        cout << "Coins Used    : ";

        printDPCoins(coins, dp, amount);

        cout << endl;
    }

    cout << "Operations    : "
         << dpOperations << endl;

    cout << "Time          : "
         << dpTime.count() << " ns\n";


    // ================= GREEDY OUTPUT =================

    cout << "\n========== GREEDY ==========\n";

    if(greedyResult == -1)
    {
        cout << "Minimum Coins : Not Possible\n";
        cout << "Coins Used    : Not Possible\n";
    }
    else
    {
        cout << "Minimum Coins : "
             << greedyResult << endl;

        cout << "Coins Used    : ";

        printGreedyCoins(coins, amount);

        cout << endl;
    }

    cout << "Operations    : "
         << greedyOperations << endl;

    cout << "Time          : "
         << greedyTime.count() << " ns\n";


    // ================= COMPARISON =================

    cout << "\n========== COMPARISON ==========\n";

    if(dpResult == greedyResult)
    {
        cout << "Both approaches give the same result.\n";
    }
    else
    {
        cout << "DP gives the optimal result.\n";
    }


    return 0;
}
