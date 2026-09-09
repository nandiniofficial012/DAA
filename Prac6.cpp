#include <iostream>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    int n;

    cout << "Enter number of matrices: ";
    cin >> n;

    int p[n + 1];

    cout << "Enter dimensions: ";
    for (int i = 0; i <= n; i++)
    {
        cin >> p[i];
    }

    int m[n + 1][n + 1];

    // Start time
    auto start = high_resolution_clock::now();

    // Cost of multiplying one matrix = 0
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    // len = length of matrix chain
    for (int len = 2; len <= n; len++)
    {
        cout << "\n========================================";
        cout << "\nChain Length = " << len;
        cout << "\n========================================\n";

        for (int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;

            m[i][j] = INT_MAX;

            cout << "\nCalculating m[" << i << "][" << j << "]\n";

            // Try every possible value of k
            for (int k = i; k < j; k++)
            {
                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                cout << "  k = " << k
                     << " : "
                     << m[i][k] << " + "
                     << m[k + 1][j] << " + "
                     << p[i - 1] << "*" << p[k] << "*" << p[j]
                     << " = " << cost;

                if (cost < m[i][j])
                {
                    m[i][j] = cost;

                    cout << "  <-- TAKEN";
                }

                cout << endl;
            }

            cout << "  Minimum for m[" << i << "][" << j << "] = "
                 << m[i][j] << endl;
        }
    }

    // End time
    auto end = high_resolution_clock::now();

    // Display DP matrix
    cout << "\n\n========================================";
    cout << "\n        DP MATRIX";
    cout << "\n========================================\n\n";

    cout << "\t";

    for (int j = 1; j <= n; j++)
    {
        cout << "A" << j << "\t";
    }

    cout << endl;

    for (int i = 1; i <= n; i++)
    {
        cout << "A" << i << "\t";

        for (int j = 1; j <= n; j++)
        {
            if (j < i)
                cout << "-\t";
            else
                cout << m[i][j] << "\t";
        }

        cout << endl;
    }

    // Final answer
    cout << "\nMinimum number of scalar multiplications = "
         << m[1][n] << endl;

    // Execution time
    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "Execution time = "
         << duration.count()
         << " nanoseconds" << endl;

    return 0;
}
