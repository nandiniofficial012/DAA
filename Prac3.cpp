#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Max Heap Counters
int maxComparisons = 0;
int maxSwaps = 0;
int maxHeapifyCalls = 0;

// Min Heap Counters
int minComparisons = 0;
int minSwaps = 0;
int minHeapifyCalls = 0;

//------------------ MAX HEAP ------------------//
void maxHeapify(vector<int> &arr, int n, int i)
{
    maxHeapifyCalls++;
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    maxComparisons++;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    maxComparisons++;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        maxSwaps++;
        maxHeapify(arr, n, largest);
    }
}

void maxHeapSort(vector<int> &arr)
{
    int n = arr.size();

    // Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    // Heap Sort
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxSwaps++;
        maxHeapify(arr, i, 0);
    }
}

//------------------ MIN HEAP ------------------//
void minHeapify(vector<int> &arr, int n, int i)
{
    minHeapifyCalls++;
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    minComparisons++;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    minComparisons++;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        minSwaps++;
        minHeapify(arr, n, smallest);
    }
}

void minHeapSort(vector<int> &arr)
{
    int n = arr.size();

    // Build Min Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    // Heap Sort
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        minSwaps++;
        minHeapify(arr, i, 0);
    }

    // Reverse to get ascending order
    reverse(arr.begin(), arr.end());
}


bool isSorted(vector<int> &arr)
{
    for(int i=0;i<arr.size()-1;i++)
    {
        if(arr[i]>arr[i+1])
            return false;
    }

    return true;
}

//------------------ MAIN ------------------//
int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);

    srand(time(0));

    for (int i = 0; i < n; i++)
        original[i] = rand() % 1000;
        
    cout << "\nOriginal Array:\n";

for(int i = 0; i < n; i++)
{
    cout << original[i] << " ";
}

cout << endl;

    vector<int> maxHeapArray = original;
    vector<int> minHeapArray = original;

    //---------------- MAX HEAP SORT ----------------//
    auto startMax = high_resolution_clock::now();

    maxHeapSort(maxHeapArray);
    
    cout << "\nMax Heap Sorted Array:\n";

for(int i = 0; i < n; i++)
{
    cout << maxHeapArray[i] << " ";
}

cout << endl;

    auto endMax = high_resolution_clock::now();

    //---------------- MIN HEAP SORT ----------------//
    auto startMin = high_resolution_clock::now();

    minHeapSort(minHeapArray);
    
    cout << "\nMin Heap Sorted Array:\n";

for(int i = 0; i < n; i++)
{
    cout << minHeapArray[i] << " ";
}

cout << endl;

    auto endMin = high_resolution_clock::now();

    //---------------- DISPLAY TIME ----------------//

    auto nanoMax = duration_cast<nanoseconds>(endMax - startMax);
    auto microMax = duration_cast<microseconds>(endMax - startMax);
    duration<double> secMax = endMax - startMax;

    auto nanoMin = duration_cast<nanoseconds>(endMin - startMin);
    auto microMin = duration_cast<microseconds>(endMin - startMin);
    duration<double> secMin = endMin - startMin;

    cout<<"\n========== MAX HEAP ==========\n";

cout<<"Comparisons   : "<<maxComparisons<<endl;

cout<<"Swaps         : "<<maxSwaps<<endl;

cout<<"Heapify Calls : "<<maxHeapifyCalls<<endl;

cout<<"Sorted        : ";

if(isSorted(maxHeapArray))
    cout<<"Yes\n";
else
    cout<<"No\n";

cout<<"Nanoseconds   : "<<nanoMax.count()<<endl;

cout<<"Microseconds  : "<<microMax.count()<<endl;

cout<<"\n========== MIN HEAP ==========\n";

cout<<"Comparisons   : "<<minComparisons<<endl;

cout<<"Swaps         : "<<minSwaps<<endl;

cout<<"Heapify Calls : "<<minHeapifyCalls<<endl;

cout<<"Sorted        : ";

if(isSorted(minHeapArray))
    cout<<"Yes\n";
else
    cout<<"No\n";

cout<<"Nanoseconds   : "<<nanoMin.count()<<endl;

cout<<"Microseconds  : "<<microMin.count()<<endl;

    return 0;
}
