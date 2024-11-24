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


// 1. **Quicksort Algorithm Concept:**
//    - Quicksort is a divide-and-conquer sorting algorithm
//    - It works by selecting a 'pivot' element and partitioning the array around it
//    - Elements smaller than pivot go to the left, larger to the right
//    - The process is recursively applied to the sub-arrays

// 2. **Key Components:**

//    a) **Partition Function:**
//    ```cpp
//    int partition(std::vector<int>& arr, int low, int high)
//    ```
//    - Selects last element as pivot
//    - Rearranges array so that:
//      - Elements smaller than pivot are on left
//      - Elements larger than pivot are on right
//    - Returns the final position of pivot
//    - Time Complexity: O(n) where n is the size of subarray

//    b) **Sequential Quicksort:**
//    ```cpp
//    void quicksort(std::vector<int>& arr, int low, int high)
//    ```
//    - Traditional recursive implementation
//    - Calls partition and recursively sorts subarrays
//    - Time Complexity: 
//      - Average case: O(n log n)
//      - Worst case: O(n²)

//    c) **Parallel Quicksort:**
//    ```cpp
//    void parallel_quicksort(std::vector<int>& arr, int low, int high)
//    ```
//    - Uses OpenMP for parallelization
//    - Key OpenMP directives:
//      - `#pragma omp parallel sections`: Creates parallel sections
//      - `#pragma omp section`: Defines individual parallel sections

// 3. **OpenMP Parallelization:**
//    - `omp_set_num_threads(4)`: Sets number of threads to 4
//    - Parallel sections allow different parts of the array to be sorted simultaneously
//    - Each recursive call can potentially run on a different thread
//    - Benefits most when sorting large arrays

// 4. **Time Complexity Analysis:**
//    - Sequential Quicksort:
//      - Best/Average case: O(n log n)
//      - Worst case: O(n²)
   
//    - Parallel Quicksort:
//      - Theoretical speedup: O(n log n / p) where p is number of processors
//      - Practical speedup limited by:
//        - Overhead of thread creation
//        - Memory access patterns
//        - System architecture

// 5. **Space Complexity:**
//    - Sequential: O(log n) average case for recursion stack
//    - Parallel: O(p log n) where p is number of threads

// 6. **Trade-offs and Considerations:**
//    - Parallelization overhead vs. speedup
//    - Effective for large datasets
//    - Memory bandwidth can become a bottleneck
//    - Thread creation overhead for small subarrays

// 7. **Optimization Possibilities:**
//    - Hybrid approach: Use sequential sort for small subarrays
//    - Dynamic thread allocation based on array size
//    - Better pivot selection strategies
//    - Cache-aware partitioning

// 8. **Advantages of This Implementation:**
//    - Simple and straightforward parallelization
//    - Maintains the basic quicksort algorithm structure
//    - Scalable with number of available cores
//    - No additional memory overhead for parallelization

// 9. **Limitations:**
//    - May not be optimal for small arrays due to threading overhead
//    - Performance depends heavily on hardware and system load
//    - Load balancing can be an issue with uneven partitions

// This implementation provides a good balance between code simplicity and parallel performance, making it suitable 
// for educational purposes and moderate-sized sorting tasks. 
// For production use, 
// additional optimizations might be needed based on specific requirements and hardware capabilities.