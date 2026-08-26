#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;


// ============================================================
// 2D DYNAMIC PROGRAMMING
// Time  : O(n * W)
// Space : O(n * W)
// ============================================================

int knapsack2D(vector<int> &weight,
               vector<int> &profit,
               int n,
               int maxWeight,
               int &operations,
               vector<vector<int>> &dp)
{
    // Create complete DP table
    dp.resize(n + 1, vector<int>(maxWeight + 1, 0));

    operations = 0;

    // Process every item
    for(int i = 1; i <= n; i++)
    {
        // Try every possible capacity
        for(int w = 0; w <= maxWeight; w++)
        {
            operations++;

            // Option 1: Do not take the item
            dp[i][w] = dp[i - 1][w];

            // Option 2: Take the item
            if(weight[i - 1] <= w)
            {
                int take =
                    profit[i - 1]
                    + dp[i - 1][w - weight[i - 1]];

                if(take > dp[i][w])
                    dp[i][w] = take;
            }
        }
    }

    return dp[n][maxWeight];
}


// ============================================================
// 1D DYNAMIC PROGRAMMING
// Time  : O(n * W)
// Space : O(W)
// ============================================================

int knapsack1D(vector<int> &weight,
               vector<int> &profit,
               int n,
               int maxWeight,
               int &operations,
               vector<int> &dp)
{
    // Only one row is stored
    dp.assign(maxWeight + 1, 0);

    operations = 0;

    // Process every item
    for(int i = 0; i < n; i++)
    {
        // IMPORTANT:
        // Move from right to left.
        // This guarantees 0/1 selection.
        for(int w = maxWeight;
            w >= weight[i];
            w--)
        {
            operations++;

            int take =
                profit[i]
                + dp[w - weight[i]];

            if(take > dp[w])
                dp[w] = take;
        }
    }

    return dp[maxWeight];
}


// ============================================================
// PRINT 2D DP TABLE
// ============================================================

void printDPTable(vector<vector<int>> &dp,
                  vector<int> &weight,
                  vector<int> &profit,
                  int n,
                  int maxWeight)
{
    cout << "\n\n================ 2D DP TABLE ================\n\n";

    cout << "Item/Weight ";

    for(int w = 0; w <= maxWeight; w++)
        cout << w << "   ";

    cout << "\n-------------------------------------------------\n";

    // Row 0
    cout << "Item 0      ";

    for(int w = 0; w <= maxWeight; w++)
        cout << dp[0][w] << "   ";

    cout << "\n";

    // Remaining rows
    for(int i = 1; i <= n; i++)
    {
        cout << "Item " << i << "      ";

        for(int w = 0; w <= maxWeight; w++)
            cout << dp[i][w] << "   ";

        cout << "\n";
    }

    cout << "================================================\n";
}


// ============================================================
// FIND SELECTED ITEMS FROM 2D TABLE
// ============================================================

void findSelectedItems(vector<vector<int>> &dp,
                       vector<int> &weight,
                       vector<int> &profit,
                       int n,
                       int maxWeight,
                       vector<int> &selected)
{
    selected.assign(n, 0);

    int w = maxWeight;

    // Start from last item and move backward
    for(int i = n; i >= 1; i--)
    {
        // If value changed, item was selected
        if(dp[i][w] != dp[i - 1][w])
        {
            selected[i - 1] = 1;

            w = w - weight[i - 1];
        }
    }
}


// ============================================================
// PRINT 1D ARRAY
// ============================================================

void print1DArray(vector<int> &dp)
{
    for(int i = 0; i < dp.size(); i++)
        cout << dp[i] << " ";
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    int n;
    int maxWeight;

    cout << "Enter number of items: ";
    cin >> n;

    if(n <= 0)
    {
        cout << "Invalid number of items.\n";
        return 0;
    }

    vector<int> weight(n);
    vector<int> profit(n);

    cout << "\nEnter weights: ";

    for(int i = 0; i < n; i++)
    {
        cin >> weight[i];

        if(weight[i] <= 0)
        {
            cout << "Weight must be positive.\n";
            return 0;
        }
    }

    cout << "Enter profits: ";

    for(int i = 0; i < n; i++)
    {
        cin >> profit[i];

        if(profit[i] < 0)
        {
            cout << "Profit cannot be negative.\n";
            return 0;
        }
    }

    cout << "Enter maximum weight: ";
    cin >> maxWeight;

    if(maxWeight < 0)
    {
        cout << "Maximum weight cannot be negative.\n";
        return 0;
    }


    // ========================================================
    // 2D DP
    // ========================================================

    vector<vector<int>> dp2D;

    int operations2D = 0;

    auto start2D = high_resolution_clock::now();

    int result2D =
        knapsack2D(weight,
                   profit,
                   n,
                   maxWeight,
                   operations2D,
                   dp2D);

    auto end2D = high_resolution_clock::now();

    auto time2D =
        duration_cast<nanoseconds>(end2D - start2D);


    // ========================================================
    // 1D DP
    // ========================================================

    vector<int> dp1D;

    int operations1D = 0;

    auto start1D = high_resolution_clock::now();

    int result1D =
        knapsack1D(weight,
                   profit,
                   n,
                   maxWeight,
                   operations1D,
                   dp1D);

    auto end1D = high_resolution_clock::now();

    auto time1D =
        duration_cast<nanoseconds>(end1D - start1D);


    // ========================================================
    // SELECTED ITEMS FROM 2D
    // ========================================================

    vector<int> selected;

    findSelectedItems(dp2D,
                      weight,
                      profit,
                      n,
                      maxWeight,
                      selected);


    int totalWeight = 0;
    int totalProfit = 0;


    for(int i = 0; i < n; i++)
    {
        if(selected[i] == 1)
        {
            totalWeight += weight[i];
            totalProfit += profit[i];
        }
    }


    // ========================================================
    // INPUT INFORMATION
    // ========================================================

    cout << "\n\n================ INPUT ================\n";

    cout << "Weights : ";

    for(int i = 0; i < n; i++)
        cout << weight[i] << " ";

    cout << "\nProfits : ";

    for(int i = 0; i < n; i++)
        cout << profit[i] << " ";

    cout << "\nMaximum Weight : "
         << maxWeight;


    // ========================================================
    // 2D TABLE
    // ========================================================

    printDPTable(dp2D,
                 weight,
                 profit,
                 n,
                 maxWeight);


    // ========================================================
    // 2D RESULT
    // ========================================================

    cout << "\n\n============== 2D DP RESULT ==============\n";

    cout << "Maximum Profit : "
         << result2D << "\n";

    cout << "Operations     : "
         << operations2D << "\n";

    cout << "Execution Time : "
         << time2D.count()
         << " ns\n";

    cout << "DP Integer Cells : "
         << (n + 1) * (maxWeight + 1)
         << "\n";

    cout << "Space Complexity : O(nW)\n";


    cout << "\nSelected Items (0/1): ";

    for(int i = 0; i < n; i++)
        cout << selected[i] << " ";


    cout << "\nSelected Weights: ";

    for(int i = 0; i < n; i++)
    {
        if(selected[i] == 1)
            cout << weight[i] << " ";
    }

    cout << "\nSelected Profits : ";

    for(int i = 0; i < n; i++)
    {
        if(selected[i] == 1)
            cout << profit[i] << " ";
    }

    cout << "\nTotal Weight : "
         << totalWeight;

    cout << "\nTotal Profit : "
         << totalProfit;


    // ========================================================
    // 1D RESULT
    // ========================================================

    cout << "\n\n============== 1D DP RESULT ==============\n";

    cout << "Final DP Array : ";

    print1DArray(dp1D);

    cout << "\n";

    cout << "Maximum Profit : "
         << result1D << "\n";

    cout << "Operations     : "
         << operations1D << "\n";

    cout << "Execution Time : "
         << time1D.count()
         << " ns\n";

    cout << "DP Integer Cells : "
         << maxWeight + 1
         << "\n";

    cout << "Space Complexity : O(W)\n";


    // ========================================================
    // SPACE COMPARISON
    // ========================================================

    int cells2D =
        (n + 1) * (maxWeight + 1);

    int cells1D =
        maxWeight + 1;

    int cellsSaved =
        cells2D - cells1D;


    double reduction =
        ((double)cellsSaved / cells2D) * 100;


    cout << "\n\n============== SPACE COMPARISON ==============\n";

    cout << "2D DP Integer Cells : "
         << cells2D << "\n";

    cout << "1D DP Integer Cells : "
         << cells1D << "\n";

    cout << "Integer Cells Saved : "
         << cellsSaved << "\n";

    cout << "Memory Cell Reduction : "
         << reduction << "%\n";

    cout << "\n2D Space : O(nW)";

    cout << "\n1D Space : O(W)";


    // ========================================================
    // TIME COMPARISON
    // ========================================================

    cout << "\n\n============== TIME COMPARISON ==============\n";

    cout << "2D DP Time : "
         << time2D.count()
         << " ns\n";

    cout << "1D DP Time : "
         << time1D.count()
         << " ns\n";

    cout << "\n2D Operations : "
         << operations2D;

    cout << "\n1D Operations : "
         << operations1D;


    // ========================================================
    // CORRECTNESS COMPARISON
    // ========================================================

    cout << "\n\n============== CORRECTNESS ==============\n";

    if(result2D == result1D)
    {
        cout << "Both approaches give the same maximum profit.\n";
        cout << "Result is verified successfully.\n";
    }
    else
    {
        cout << "Results are different. Check implementation.\n";
    }


    // ========================================================
    // FINAL ANALYSIS
    // ========================================================

    cout << "\n\n============== FINAL ANALYSIS ==============\n";

    cout << "\n2D DP:";
    cout << "\nTime  : O(nW)";
    cout << "\nSpace : O(nW)";

    cout << "\n\n1D DP:";
    cout << "\nTime  : O(nW)";
    cout << "\nSpace : O(W)";

    cout << "\n\nConclusion:";

    cout << "\nBoth have the same theoretical time complexity.";

    cout << "\n1D DP is better in space because it stores only";
    cout << "\nthe current DP row instead of the complete table.";

    cout << "\n\n=============================================\n";


    return 0;
}
