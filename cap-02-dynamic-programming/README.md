# 🧩 Chapter 2: Dynamic Programming

This folder contains the class exercises and algorithm implementations related to **Dynamic Programming**. Dynamic programming is a method for solving complex problems by breaking them down into simpler subproblems. It is applicable to problems exhibiting the properties of overlapping subproblems and optimal substructure. Rather than solving the same subproblems repeatedly, dynamic programming algorithms save the results of these subproblems, significantly improving performance.

> [!WARNING]  
> **A Note on Indexing (0-based vs 1-based):** Pay close attention to array indexing when implementing these algorithms. It is a very common practice in Dynamic Programming to use 1-based indexing for the state arrays (e.g., `dp[1]` referring to the first item) or to pad the original input arrays with a dummy value at index `0`. This helps logically align the $i$-th item with `dp[i]`, easily manages base cases (like `dp[0] = 0`), and prevents out-of-bounds errors when calculating states that rely on previous elements, such as `dp[i-1]` or `dp[i-2]`.

## 📑 Table of Problems
- [1. Fibonacci Sequence](#1-fibonacci-sequence-fibonaccimaincpp)
- [2. Coin Row Problem](#2-coin-row-problem-coin_row_problemmaincpp)
- [3. Longest Increasing Subsequence](#3-longest-increasing-subsequence-longest_increasing_subsequencemaincpp)
- [4. Knapsack Problem (Upcoming)](#4-knapsack-problem-upcoming)
- [5. Other problems from previous lab sessions](#5-other-problems-from-previous-lab-sessions)

## 📝 Problem Descriptions and Algorithms

### 1. Fibonacci Sequence (`fibonacci/main.cpp`)
In this example, we demonstrate the calculation of the $N$-th Fibonacci number, comparing the simple recursive approach against the optimized dynamic programming approach.

- **Goal:** Calculate the 40th Fibonacci number efficiently.
- **Algorithm:** The solution implements two methods to compute the Fibonacci sequence:
  - **Recursive:** A top-down approach that calls `fibonacci(N - 1) + fibonacci(N - 2)`. This approach recalculates overlapping subproblems.
  - **Dynamic Programming:** A bottom-up approach that builds an array `dp` from `dp[0] = 0` and `dp[1] = 1`, filling each subsequent value as the sum of the two preceding ones. This avoids redundant calculations.
- **How to run:**
  ```bash
  cd fibonacci
  g++ -O2 -o fibonacci_solver main.cpp
  ./fibonacci_solver
  ```

- **Example Output:**
  ```bash
  Fibonacci N DP: 102334155
  Fibonacci N RECURSIVE: 102334155
  ```

### 2. Coin Row Problem (`coin_row_problem/main.cpp`)
In this example, we show how to use dynamic programming to solve the Coin Row Problem, which consists of finding the maximum sum of coins that can be picked up from a row of coins.

- **Goal:** Select coins from the row `{0, 5, 1, 2, 10, 6, 2}` to maximize the total sum, subject to the constraint that no two adjacent coins can be chosen.
- **Algorithm:** The proposed solution makes use of a bottom-up dynamic programming approach.
  - A state array `dp` is used, where `dp[i]` represents the maximum sum of coins that can be obtained using up to the $i$-th coin.
  - For each new coin starting from index 2, the algorithm decides between two choices: either not select the current coin (taking the optimal sum from `dp[i-1]`) or select the current coin (adding its value to the optimal sum from `dp[i-2]`).
  - The maximum of these two choices is stored in `dp[i]`.
  - The final answer is located at `dp[N]`.
- **How to run:**
  ```bash
  cd coin_row_problem
  g++ -O2 -o coin_row main.cpp
  ./coin_row
  ```

- **Example Output:**
  ```bash
  17
  ```

### 3. Longest Increasing Subsequence (`longest_increasing_subsequence/main.cpp`)
In this example, we solve the classical Longest Increasing Subsequence (LIS) problem. The objective is to find the length of the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order.

- **Goal:** Find the length of the longest increasing subsequence in the array `{-7, 1, 9, 8, 3, 8, 10, 1}`.
- **Algorithm:** The solution utilizes dynamic programming using a `dp` array.
  - The array `dp` is initialized with `1`s (implicitly or explicitly depending on logic), as each element is at least an increasing subsequence of length 1.
  - For each element in the array at index `i`, we iterate through all previous elements up to index `i-1` (let's call the index `j`).
  - If we find a previous element `X[j]` that is strictly less than `X[i]`, it means `X[i]` can be appended to the increasing subsequence ending at `X[j]`. We then update `dp[i] = max(dp[i], dp[j] + 1)`.
  - The overall longest increasing subsequence length will be the maximum value stored anywhere in the `dp` array.
- **How to run:**
  ```bash
  cd longest_increasing_subsequence
  g++ -O2 -o lis main.cpp
  ./lis
  ```

- **Example Output:**
  ```bash
  5
  ```

### 4. Knapsack Problem (Upcoming)
*(This problem will be implemented in the next lecture.)*

The Knapsack Problem is a classic optimization problem.
Given $n$ items with:
- Integer weights: $w_1, w_2, \dots, w_n$
- Values: $v_1, v_2, \dots, v_n$

and a knapsack of integer capacity $W$.

**Goal:** Find the most valuable subset of items that fit into the knapsack.

### 5. Other problems from previous lab sessions
*(To be added)*

---

[← Back to course root](../README.md)
