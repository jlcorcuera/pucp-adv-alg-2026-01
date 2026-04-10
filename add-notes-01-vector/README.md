# 📖 Notes on `std::vector` (Standard Template Library)

---

## 1. Introduction

A `std::vector` in C++ is a dynamic or resizable array. It provides the ability to push or pop elements at any time, allowing its size to increase or decrease dynamically. Unlike standard static arrays, it is not mandatory to specify the size of the vector at the time of declaration.

---

## 2. Declaration and Initialization

### 2.1 Declaration

A vector is declared using the following syntax, where the `type` can represent any data type (e.g., `int`, `char`, `std::string`, `double`, etc.).

```cpp
#include <vector>
#include <string>

std::vector<int> v;
std::vector<std::string> vs;
std::vector<char> vc;
std::vector<std::vector<char>> vv; // 2D Vector
```

It is permitted to specify the initial size of the vector upon instantiation. By default, all elements are initialized to zero (or the data type's default state). Alternatively, they can be initialized to a specific value immediately at the time of declaration.

```cpp
std::vector<int> v(5);       // Initialized as: {0, 0, 0, 0, 0}
std::vector<int> v(5, 10);   // Initialized as: {10, 10, 10, 10, 10}
```

### 2.2 Initialization

Vectors can be initialized directly with a predefined set of values:

```cpp
std::vector<int> v = {10, 20, 15, 50};
std::vector<std::string> vs = {"Hello", "Ujjal"};
```

---

## 3. Traversing and Accessing Elements

Once declared, a vector can be used in a manner functionally similar to standard arrays, which includes zero-based indexing for element access:

```cpp
std::cout << v[0] << std::endl; // Output: 10
v[1] = 100;                     // Modifying element
std::cout << v[1] << std::endl; // Output: 100
```

### 3.1 Loop Traversal

Various iteration loops (`for`, `while`, `do-while`, or `range-based for`) can be used to traverse the sequential structure.

**Using a standard index-based `for` loop:**
```cpp
std::vector<int> v = {10, 20, 15, 50};
for (int i = 0; i < 4; i++) {
    std::cout << v[i] << std::endl;
}
```

**Using a modern range-based loop:**
```cpp
std::vector<int> v = {10, 20, 15, 50};
for (auto u : v) {
    std::cout << u << std::endl;
}
```

---

## 4. Member Functions and Complexities

### 4.1 Insertion and Deletion

- **`push_back()`**: Appends an element to the end of the vector.
  - **Time Complexity:** $O(1)$ amortized.

```cpp
std::vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);
```

- **`insert()`**: Adds a new element at a specific index via an iterator coordinate (position). 
  - **Time Complexity:** $O(n)$, since all subsequent elements located after the insertion point must be shifted.

```cpp
std::vector<int> v = {1, 2, 3, 4};
v.insert(v.begin() + 1, 10); // Resulting state: {1, 10, 2, 3, 4}
```

- **`erase()`**: Removes an element or a contiguous range of elements from the vector.
  - **Time Complexity:** $O(n)$, due to element shifting post-deletion.

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
v.erase(v.begin()); // Resulting state: {2, 3, 4, 5}
v.erase(v.begin(), v.begin() + 2); // Resulting state: {4, 5}
```

- **`clear()`**: Removes all the elements from the vector structure, leaving it fully empty.
  - **Time Complexity:** $O(n)$ proportional to the size of the container as destructors may be called, but typically evaluates to $O(1)$ for raw primitive types.

```cpp
std::vector<int> v = {10, 20, 30, 40};
v.clear();
std::cout << v.size() << std::endl; // Output: 0
```

### 4.2 Capacity and Constraints

- **`size()`**: Returns the total amount of elements present inside the vector.
  - **Time Complexity:** $O(1)$.

```cpp
std::vector<int> v = {10, 20, 30, 40};
std::cout << v.size() << std::endl; // Output: 4
```

- **`empty()`**: Evaluates to boolean `true` (1) if the container contains no elements, otherwise `false` (0).
  - **Time Complexity:** $O(1)$.

```cpp
std::vector<char> vc = {'A', 'B'};
std::cout << vc.empty() << std::endl; // Output: 0
```

- **`resize()`**: Specifically changes the dimension of the vector. If expanded, any new uninitialized spaces are filled with zero constraints.
  - **Time Complexity:** $O(n)$.

```cpp
std::vector<int> v(5, 2); // Size: 5. Elements: {2, 2, 2, 2, 2}
v.resize(10);             // Size: 10. Elements: {2, 2, 2, 2, 2, 0, 0, 0, 0, 0}
```

### 4.3 Target Iterators

- **`front()` and `back()`**:
  `front()` directly exposes a reference to the first element; `back()` performs similarly but targets the absolute last element.
  - **Time Complexity:** $O(1)$.

```cpp
std::vector<long long int> v = {10, 20, 30, 40, 50};
std::cout << v.front() << " " << v.back() << std::endl; // Output: 10 50
```

---

## 5. Algorithms and Advanced Extractions

### 5.1 Reversing a Vector Space

Using `<algorithm>`, the `std::reverse()` function can invert the index positioning of all respective elements.
- **Time Complexity:** $O(n)$.

```cpp
#include <algorithm>

std::vector<int> v = {1, 2, 3, 4};
std::reverse(v.begin(), v.end()); // Vector transformed to: {4, 3, 2, 1}
```

### 5.2 Minimum and Maximum Extrema Detection

The `std::max_element()` and `std::min_element()` routines return iterative address points correlating to the highest/lowest values.
- **Time Complexity:** $O(n)$.

```cpp
#include <algorithm>

std::vector<int> v = {1, 2, 3, 5, 4, 1, 5};
auto it = std::max_element(v.begin(), v.end());

std::cout << *it << std::endl; // Output: 5 (Maximum value)
std::cout << it - v.begin() << std::endl; // Output: 3 (Zero-indexed placement layout)
```

### 5.3 Quick Sorting Mechanisms

The `std::sort()` function efficiently orders the elements. By default, standard comparisons resolve in **ascending sequence**.
- **Time Complexity:** $O(n \log n)$.

**Ascending Pattern Mapping:**
```cpp
#include <algorithm>

std::vector<int> v = {4, 1, 2, 3, 2, 5, 1};
std::sort(v.begin(), v.end());
// Array sequence sorted as: {1, 1, 2, 2, 3, 4, 5}
```

**Descending Pattern Mapping:**
To reverse sequence priorities, introduce `std::greater<type>()` or bind `.rbegin()` and `.rend()` pointers respectively.
```cpp
#include <algorithm>

std::vector<int> v = {4, 1, 2, 3, 2, 5, 1};
std::sort(v.begin(), v.end(), std::greater<int>());
// Explicit equivalent mapping: std::sort(v.rbegin(), v.rend());
// Final sort generated correctly: {5, 4, 3, 2, 2, 1, 1}
```

### 5.4 Cloning Copies

A vector is treated like any primitive form variable during copy instructions via assignment (`=`). 

```cpp
std::vector<char> vc = {'U', 'j', 'j', 'a', 'l'};
std::vector<char> vc1;

vc1 = vc; // A full deep copy is explicitly registered, leaving the source unaffected.
```

---

**Source:** [Codeforces Blog Entry 120289](https://codeforces.com/blog/entry/120289)
