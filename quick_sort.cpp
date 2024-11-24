//Implementing Parallel Quick Sort
#it is the library used for parallel processing 
#we have used the two pointer technique 
#pragma omp parallel sections: Creates a team of threads to execute the sections in parallel
#pragma omp section: Marks a section of code to be executed by one of the threads
#g++ -fopenmp -std=c++17 quick_sort.cpp -o quick_sort

#-fopenmp: Enables OpenMP support
#-std=c++17: Uses C++17 standard
#-o quick_sort: Names the output executable
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <omp.h>


// PS C:\Users\ADMIN> cd "c:\Users\ADMIN\OneDrive\Desktop\OFFICIAL ADA CODES\" ; if ($?) { g++ quick_sort.cpp -o quick_sort } ; if ($?) { .\quick_sort }



// g++ -fopenmp -std=c++17 quick_sort.cpp -o quick_sort
// Enter num of elements: 8
// Enter elements: 20 18 5 14 3 11 7 9
//  cd "c:\Users\ADMIN\OneDrive\Desktop\" ; if ($?) { g++ quick_sort.cpp -o quick_sort } ; if ($?) { .\quick_sort }
using namespace std;

class QSMultiThreading 
{
    private:
        int strt_;
        int end_;
        vector<int>& arr_;

    public:
        QSMultiThreading(int strt, int end, vector<int>& arr) 
            : strt_(strt), end_(end), arr_(arr) {}
        
        int partition(int strt, int end, vector<int>& arr) 
        {
            int i = strt;
            int j = end;

            int pivoted = rand() % (j - i + 1) + i;

            swap(arr[j], arr[pivoted]);
            j--;

            while (i <= j) 
            {
                if (arr[i] <= arr[end]) 
                {
                    i++;
                    continue;
                }
                if (arr[j] >= arr[end]) 
                {
                    j--;
                    continue;
                }
                swap(arr[i], arr[j]);
                j--;
                i++;
            }

            swap(arr[j + 1], arr[end]);

            return j + 1;
        }

        void operator() () 
        {
            if (strt_ >= end_) 
            {
                return;
            }

            int p = partition(strt_, end_, arr_);

            QSMultiThreading left(strt_, p - 1, arr_);
            QSMultiThreading right(p + 1, end_, arr_);

            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    left();
                }
                #pragma omp section
                {
                    right();
                }
            }
        }

};

int main() 
{
    srand(time(NULL));

    int n;
    cout << "Enter num of elements: ";
    cin >> n;
    vector<int> arr(n);

    cout << "Enter elements: ";

    for (int i = 0; i < n; ++i) 
    {
        cin >> arr[i];
    }

    QSMultiThreading(0, n - 1, arr)();

    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) 
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}




// Let's break it down into key components:

// 1. **Headers and Compilation**
// ```cpp
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstdlib>
// #include <ctime>
// #include <omp.h>
// ```
// - Standard C++ headers for I/O, vectors, algorithms
// - `omp.h` is included for OpenMP parallel processing support
// - The compilation command `-fopenmp` flag enables OpenMP support

// 2. **QSMultiThreading Class**
// This class encapsulates the parallel quicksort implementation:

// ```cpp
// class QSMultiThreading {
//     private:
//         int strt_;         // Start index
//         int end_;          // End index
//         vector<int>& arr_; // Reference to array
// ```
// - The class maintains references to the sorting range and array
// - Uses trailing underscores to distinguish member variables

// 3. **Constructor**
// ```cpp
// QSMultiThreading(int strt, int end, vector<int>& arr)
//     : strt_(strt), end_(end), arr_(arr) {}
// ```
// - Initializes the sorting range and array reference
// - Uses member initializer list for efficient initialization

// 4. **Partition Method**
// ```cpp
// int partition(int strt, int end, vector<int>& arr)
// ```
// This method implements the partitioning logic:
// - Randomly selects a pivot element using: `rand() % (j - i + 1) + i`
// - Moves elements smaller than pivot to left side
// - Moves elements larger than pivot to right side
// - Uses two-pointer technique (i and j) for partitioning
// - Returns the final position of the pivot

// 5. **Operator() - The Main Sorting Function**
// ```cpp
// void operator() ()
// ```
// This is where the parallel processing happens:
// - Checks base case (strt_ >= end_)
// - Partitions the array
// - Creates two QSMultiThreading objects for left and right subarrays
// - Uses OpenMP parallel sections for concurrent processing:
//   ```cpp
//   #pragma omp parallel sections
//   {
//       #pragma omp section
//       {
//           left();
//       }
//       #pragma omp section
//       {
//           right();
//       }
//   }
//   ```

// 6. **Main Function**
// ```cpp
// int main()
// ```
// - Seeds the random number generator
// - Takes input for array size and elements
// - Creates QSMultiThreading object and calls it
// - Prints the sorted array

// Key Features of this Implementation:

// 1. **Parallel Processing**
//    - Uses OpenMP to parallelize the quicksort algorithm
//    - Each recursive call can potentially run in a separate thread
//    - The `parallel sections` directive creates two concurrent tasks

// 2. **Random Pivot Selection**
//    - Uses random pivot selection to avoid worst-case scenarios
//    - Helps in maintaining balanced partitions

// 3. **In-Place Sorting**
//    - Modifies the array in-place without requiring extra space
//    - Uses swapping to rearrange elements

// 4. **Exception Safety**
//    - Uses references to avoid copying large arrays
//    - Properly scoped variables and RAII principles

// Time Complexity:
// - Average case: O(n log n)
// - Worst case: O(n²) (rare due to random pivot)
// - The parallel implementation can significantly reduce actual running time on multi-core processors

// Space Complexity:
// - O(log n) for the recursion stack
// - O(1) additional space for partitioning

// This implementation is particularly efficient because:
// 1. It uses parallel processing for larger subarrays
// 2. Random pivot selection helps avoid worst-case scenarios
// 3. In-place partitioning saves memory
// 4. The code is well-structured and maintainable
