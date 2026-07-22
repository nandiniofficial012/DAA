#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Linear Search Function
int linearSearch(const vector<int> &arr, int key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// Binary Search Function
int binarySearch(const vector<int> &arr, int key)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    int n = 10;
    vector<int> arr(n);

    srand(time(0));

    // Generate Random Numbers
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }

    // Sort Array for Binary Search
    sort(arr.begin(), arr.end());

    cout << "Generated Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    int key;
    cout << "\nEnter element to search : ";
    cin >> key;

    int index;

    // Linear Search Timing
    auto start = high_resolution_clock::now();
    index = linearSearch(arr, key);
    auto stop = high_resolution_clock::now();

    cout << "\nLinear Search\n";
    if (index != -1)
        cout << "Element Found at Index : " << index << endl;
    else
        cout << "Element Not Found" << endl;

    cout << "Time Taken : "
         << duration_cast<nanoseconds>(stop - start).count()
         << " nanoseconds\n";

    // Binary Search Timing
    start = high_resolution_clock::now();
    index = binarySearch(arr, key);
    stop = high_resolution_clock::now();

    cout << "\nBinary Search\n";
    if (index != -1)
        cout << "Element Found at Index : " << index << endl;
    else
        cout << "Element Not Found" << endl;

    cout << "Time Taken : "
         << duration_cast<nanoseconds>(stop - start).count()
         << " nanoseconds\n";

    return 0;
}