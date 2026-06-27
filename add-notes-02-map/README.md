# 📖 Notes on `std::map` (Standard Template Library)

---

## 1. Introduction

A `std::map` in C++ is an **associative container** that stores elements as **key-value pairs**, where each key is unique and automatically kept in sorted order. Unlike sequential containers such as `std::vector`, a `std::map` organizes its data internally as a **self-balancing Binary Search Tree (BST)** (typically a Red-Black Tree), which guarantees $O(\log n)$ time complexity for insertion, deletion, and lookup operations.

The key distinction of `std::map` over other containers is the ability to index elements by an arbitrary key type rather than by a numeric position.

---

## 2. Declaration and Initialization

### 2.1 Declaration

A map is declared using the following syntax, where `KeyType` and `ValueType` can represent any comparable and copyable data types respectively.

```cpp
#include <map>
#include <string>

std::map<int, std::string> m;          // int keys, string values
std::map<std::string, int> wordCount;  // string keys, int values
std::map<char, double> m2;             // char keys, double values
```

### 2.2 Initialization

Maps can be initialized directly with a predefined set of key-value pairs using an initializer list:

```cpp
std::map<std::string, int> m = {
    {"Alice", 90},
    {"Bob",   75},
    {"Carol", 88}
};
```

Elements can also be inserted individually after declaration using the subscript operator or `insert()`:

```cpp
std::map<std::string, int> m;
m["Alice"] = 90;
m["Bob"]   = 75;
```

> **Note:** If a key does not exist and the subscript operator `[]` is used, the key is automatically inserted with its value default-initialized (e.g., `0` for `int`). This is a common source of unintended behavior and must be handled carefully.

---

## 3. Traversing and Accessing Elements

### 3.1 Element Access

Elements are accessed by key. The two primary access methods are the subscript operator and `at()`:

```cpp
std::map<std::string, int> m = {{"Alice", 90}, {"Bob", 75}};

std::cout << m["Alice"] << std::endl;   // Output: 90
std::cout << m.at("Bob") << std::endl;  // Output: 75
```

The `at()` method is preferred in academic and production contexts because it performs **bounds checking** and throws `std::out_of_range` if the key does not exist, whereas `[]` silently inserts a default value.

### 3.2 Loop Traversal

Since `std::map` stores key-value pairs, iteration yields `std::pair<const KeyType, ValueType>` elements. The modern range-based loop with structured bindings (C++17) is the recommended approach:

**Using a range-based loop (C++17 structured binding):**
```cpp
std::map<std::string, int> m = {{"Alice", 90}, {"Bob", 75}, {"Carol", 88}};

for (const auto& [key, value] : m) {
    std::cout << key << ": " << value << std::endl;
}
// Output (sorted by key):
// Alice: 90
// Bob: 75
// Carol: 88
```

**Using an explicit iterator:**
```cpp
for (auto it = m.begin(); it != m.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
}
```

> **Observation:** Iteration always proceeds in **ascending order of keys**, regardless of insertion order. This is a guaranteed property of `std::map`.

---

## 4. Member Functions and Complexities

### 4.1 Insertion and Deletion

- **`insert()`**: Inserts a key-value pair only if the key does not already exist. Returns a `std::pair<iterator, bool>` where the boolean indicates whether the insertion succeeded.
  - **Time Complexity:** $O(\log n)$.

```cpp
std::map<std::string, int> m;
m.insert({"Alice", 90});
m.insert({"Alice", 100}); // Ignored: key "Alice" already exists
```

- **`emplace()`**: Constructs and inserts a key-value pair in-place, avoiding unnecessary copies. Preferred over `insert()` for complex value types.
  - **Time Complexity:** $O(\log n)$.

```cpp
std::map<std::string, int> m;
m.emplace("Bob", 75);
```

- **`erase()`**: Removes the element associated with a given key, or removes elements via an iterator or iterator range.
  - **Time Complexity:** $O(\log n)$ by key; $O(1)$ amortized by iterator.

```cpp
std::map<std::string, int> m = {{"Alice", 90}, {"Bob", 75}, {"Carol", 88}};
m.erase("Bob"); // Removes the entry with key "Bob"
```

- **`clear()`**: Removes all elements from the map, leaving it empty.
  - **Time Complexity:** $O(n)$.

```cpp
m.clear();
std::cout << m.size() << std::endl; // Output: 0
```

### 4.2 Lookup

- **`find()`**: Returns an iterator to the element with the specified key, or `m.end()` if the key is not present. This is the standard and safest method for key existence checks.
  - **Time Complexity:** $O(\log n)$.

```cpp
std::map<std::string, int> m = {{"Alice", 90}, {"Bob", 75}};

auto it = m.find("Alice");
if (it != m.end()) {
    std::cout << "Found: " << it->second << std::endl; // Output: Found: 90
}
```

- **`count()`**: Returns `1` if the key exists, `0` otherwise (since keys are unique in `std::map`). Commonly used as a boolean existence check.
  - **Time Complexity:** $O(\log n)$.

```cpp
if (m.count("Carol") == 0) {
    std::cout << "Carol not found" << std::endl;
}
```

- **`contains()`** *(C++20)*: Returns a boolean directly indicating whether the key is present.
  - **Time Complexity:** $O(\log n)$.

```cpp
if (m.contains("Alice")) {
    std::cout << "Alice is registered" << std::endl;
}
```

### 4.3 Capacity

- **`size()`**: Returns the number of key-value pairs currently stored in the map.
  - **Time Complexity:** $O(1)$.

```cpp
std::map<std::string, int> m = {{"Alice", 90}, {"Bob", 75}};
std::cout << m.size() << std::endl; // Output: 2
```

- **`empty()`**: Evaluates to `true` if the map contains no elements, `false` otherwise.
  - **Time Complexity:** $O(1)$.

```cpp
std::map<int, int> m;
std::cout << m.empty() << std::endl; // Output: 1 (true)
```

---

## 5. Algorithms and Advanced Usage

### 5.1 Lower and Upper Bounds

Since `std::map` is always sorted, it supports efficient range queries using `lower_bound()` and `upper_bound()`:

- **`lower_bound(key)`**: Returns an iterator to the first element whose key is **greater than or equal to** the given key.
- **`upper_bound(key)`**: Returns an iterator to the first element whose key is **strictly greater than** the given key.
- **Time Complexity:** $O(\log n)$ for both.

```cpp
std::map<int, std::string> m = {{1, "a"}, {3, "b"}, {5, "c"}, {7, "d"}};

auto lo = m.lower_bound(3); // Points to {3, "b"}
auto hi = m.upper_bound(5); // Points to {7, "d"}

for (auto it = lo; it != hi; ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
}
// Output:
// 3: b
// 5: c
```

### 5.2 Frequency Counting Pattern

One of the most common applications of `std::map` is counting element frequencies. The default-initialization behavior of `[]` is intentionally exploited here:

```cpp
#include <map>
#include <string>
#include <vector>

std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
std::map<std::string, int> freq;

for (const auto& w : words) {
    freq[w]++; // Inserts with value 0 if absent, then increments
}

for (const auto& [word, count] : freq) {
    std::cout << word << ": " << count << std::endl;
}
// Output (sorted alphabetically):
// apple: 3
// banana: 2
// cherry: 1
```

### 5.3 Custom Sort Order (Comparator)

By default, `std::map` sorts keys in **ascending order** using `std::less<KeyType>`. A custom comparator can be provided as a third template argument to change this behavior:

```cpp
std::map<int, std::string, std::greater<int>> m = {
    {1, "a"}, {3, "b"}, {5, "c"}
};

for (const auto& [key, val] : m) {
    std::cout << key << ": " << val << std::endl;
}
// Output (descending key order):
// 5: c
// 3: b
// 1: a
```

### 5.4 Copying a Map

Like `std::vector`, a `std::map` supports deep copy via the assignment operator. The resulting copy is entirely independent of the source:

```cpp
std::map<std::string, int> original = {{"Alice", 90}, {"Bob", 75}};
std::map<std::string, int> copy;

copy = original; // Full deep copy; modifying 'copy' does not affect 'original'
```

---

## 6. `std::map` vs. `std::unordered_map`

A common design decision is choosing between `std::map` and `std::unordered_map`. The key trade-offs are:

| Property | `std::map` | `std::unordered_map` |
|----------|-----------|----------------------|
| **Internal structure** | Red-Black Tree (BST) | Hash Table |
| **Key ordering** | Sorted (ascending by default) | No guaranteed order |
| **Lookup complexity** | $O(\log n)$ | $O(1)$ average, $O(n)$ worst |
| **Insertion complexity** | $O(\log n)$ | $O(1)$ average, $O(n)$ worst |
| **Use case** | When sorted iteration or range queries are needed | When only fast lookup is needed |

Use `std::map` when the **ordering of keys matters** or when **range-based queries** (e.g., `lower_bound`) are required. Use `std::unordered_map` when **raw lookup speed** is the primary concern and key ordering is irrelevant.

---

**Source:** [cppreference.com — std::map](https://en.cppreference.com/w/cpp/container/map)

