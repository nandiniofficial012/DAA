#include <iostream>
#include <chrono>

using namespace std;

int iterativeOperations = 0;
int recursiveOperations = 0;

// Function for Iterative Factorial
// Time Complexity: O(n)
// Space Complexity: O(1)
unsigned long long factorialIterative(int n) {
    unsigned long long result = 1;

    for (int i = 1; i <= n; ++i) {
        result *= i;
        iterativeOperations++;   // Count multiplication
    }

    return result;
}

// Function for Recursive Factorial
// Time Complexity: O(n)
// Space Complexity: O(n)
unsigned long long factorialRecursive(int n) {

    recursiveOperations++;   // Count recursive calls

    if (n <= 1)
        return 1;

    return n * factorialRecursive(n - 1);
}

int main() {

    int n;

    cout << "Enter a non-negative integer (e.g., 20): ";

    if (!(cin >> n) || n < 0) {
        cerr << "Invalid input! Please enter a non-negative integer." << endl;
        return 1;
    }
    
    if (n > 20) {
        std::cout << "Factorial of " << n
                  << " cannot be stored accurately using unsigned long long." << std::endl;
        std::cout << "Please enter a number between 0 and 20." << std::endl;
        return 1;
    }

    // Measure Iterative Implementation
    auto startIter = chrono::high_resolution_clock::now();
    unsigned long long resIter = factorialIterative(n);
    auto endIter = chrono::high_resolution_clock::now();

    chrono::duration<double, nano> durationIter = endIter - startIter;

    // Measure Recursive Implementation
    auto startRec = chrono::high_resolution_clock::now();
    unsigned long long resRec = factorialRecursive(n);
    auto endRec = chrono::high_resolution_clock::now();

    chrono::duration<double, nano> durationRec = endRec - startRec;

    // Output Results
    cout << "\n--- Results for " << n << "! ---" << endl;

    cout << "Iterative Result : " << resIter << endl;
    cout << "Iterative Time   : " << durationIter.count() << " ns" << endl;
    cout << "Operations       : " << iterativeOperations << endl;

    cout << "-------------------------------" << endl;

    cout << "Recursive Result : " << resRec << endl;
    cout << "Recursive Time   : " << durationRec.count() << " ns" << endl;
    cout << "Recursive Calls  : " << recursiveOperations << endl;

    return 0;
}