// //Implementing Parallel Quick Sort

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstdlib>
// #include <ctime>
// #include <omp.h>


// // PS C:\Users\ADMIN> cd "c:\Users\ADMIN\OneDrive\Desktop\OFFICIAL ADA CODES\" ; if ($?) { g++ quick_sort.cpp -o quick_sort } ; if ($?) { .\quick_sort }



// // g++ -fopenmp -std=c++17 quick_sort.cpp -o quick_sort
// // Enter num of elements: 8
// // Enter elements: 20 18 5 14 3 11 7 9
// //  cd "c:\Users\ADMIN\OneDrive\Desktop\" ; if ($?) { g++ quick_sort.cpp -o quick_sort } ; if ($?) { .\quick_sort }
// using namespace std;

// class QSMultiThreading 
// {
//     private:
//         int strt_;
//         int end_;
//         vector<int>& arr_;

//     public:
//         QSMultiThreading(int strt, int end, vector<int>& arr) 
//             : strt_(strt), end_(end), arr_(arr) {}
        
//         int partition(int strt, int end, vector<int>& arr) 
//         {
//             int i = strt;
//             int j = end;

//             int pivoted = rand() % (j - i + 1) + i;

//             swap(arr[j], arr[pivoted]);
//             j--;

//             while (i <= j) 
//             {
//                 if (arr[i] <= arr[end]) 
//                 {
//                     i++;
//                     continue;
//                 }
//                 if (arr[j] >= arr[end]) 
//                 {
//                     j--;
//                     continue;
//                 }
//                 swap(arr[i], arr[j]);
//                 j--;
//                 i++;
//             }

//             swap(arr[j + 1], arr[end]);

//             return j + 1;
//         }

//         void operator() () 
//         {
//             if (strt_ >= end_) 
//             {
//                 return;
//             }

//             int p = partition(strt_, end_, arr_);

//             QSMultiThreading left(strt_, p - 1, arr_);
//             QSMultiThreading right(p + 1, end_, arr_);

//             #pragma omp parallel sections
//             {
//                 #pragma omp section
//                 {
//                     left();
//                 }
//                 #pragma omp section
//                 {
//                     right();
//                 }
//             }
//         }

// };

// int main() 
// {
//     srand(time(NULL));

//     int n;
//     cout << "Enter num of elements: ";
//     cin >> n;
//     vector<int> arr(n);

//     cout << "Enter elements: ";

//     for (int i = 0; i < n; ++i) 
//     {
//         cin >> arr[i];
//     }

//     QSMultiThreading(0, n - 1, arr)();

//     cout << "Sorted array: ";
//     for (int i = 0; i < n; ++i) 
//     {
//         cout << arr[i] << " ";
//     }
//     cout << endl;

//     return 0;
// }



#include <iostream>
#include <vector>
#include <omp.h>

// Partition function for quicksort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Using the last element as the pivot
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Sequential quicksort function
void quicksort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);    // Sort elements before partition
        quicksort(arr, pi + 1, high);   // Sort elements after partition
    }
}

// Parallel quicksort function using OpenMP
void parallel_quicksort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Parallelize recursive calls with OpenMP
        #pragma omp parallel sections
        {
            #pragma omp section
            parallel_quicksort(arr, low, pi - 1);
            
            #pragma omp section
            parallel_quicksort(arr, pi + 1, high);
        }
    }
}

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;
    
    std::vector<int> arr(n);
    std::cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    // Set number of threads for parallel execution
    omp_set_num_threads(4);
    
    // Perform parallel quicksort
    parallel_quicksort(arr, 0, arr.size() - 1);
    
    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}