# 🧩 Chapter 2: Dynamic Programming

This folder contains the class exercises and algorithm implementations related to **Dynamic Programming**. Dynamic programming is a method for solving complex problems by breaking them down into simpler subproblems. It is applicable to problems exhibiting the properties of overlapping subproblems and optimal substructure. Rather than solving the same subproblems repeatedly, dynamic programming algorithms save the results of these subproblems, significantly improving performance.

> [!WARNING]  
> **A Note on Indexing (0-based vs 1-based):** Pay close attention to array indexing when implementing these algorithms. It is a very common practice in Dynamic Programming to use 1-based indexing for the state arrays (e.g., `dp[1]` referring to the first item) or to pad the original input arrays with a dummy value at index `0`. This helps logically align the $i$-th item with `dp[i]`, easily manages base cases (like `dp[0] = 0`), and prevents out-of-bounds errors when calculating states that rely on previous elements, such as `dp[i-1]` or `dp[i-2]`.

## 📑 Table of Problems
- [1. Fibonacci Sequence](#1-fibonacci-sequence-fibonaccimaincpp)
- [2. Coin Row Problem](#2-coin-row-problem-coin_row_problemmaincpp)
- [3. Longest Increasing Subsequence](#3-longest-increasing-subsequence-longest_increasing_subsequencemaincpp)
- [4. Knapsack Problem](#4-knapsack-problem-knapsack_problemmaincpp)
- [5. Bird Cage Problem (Examen Parcial 2023-1)](#5-bird-cage-problem-examen-parcial-2023-1-202301_middle_term_birds_problemmaincpp)
- [6. Robot Wood Cutter (Examen Parcial 2023-1)](#6-robot-wood-cutter-examen-parcial-2023-1-202301_middle_term_exam_robot_cut_woodsmaincpp)
- [7. Coin Line Problem](#7-coin-line-problem-coin_line_problemmaincpp)

## 📝 Problem Descriptions and Algorithms

### 1. Fibonacci Sequence (`fibonacci/main.cpp`)
In this example, we demonstrate the calculation of the $N$-th Fibonacci number, comparing the simple recursive approach against the optimized dynamic programming approach.

- **Goal:** Calculate the $N$-th Fibonacci number efficiently (the provided example code computes it for $N = 40$).
- **Idea:** Instead of recalculating the same Fibonacci numbers repeatedly (which results in an exponential time complexity), we compute them iteratively from the bottom up. By caching the results of the two previous subproblems, we can compute the current sequence number in $O(1)$ time, essentially turning an exponential algorithm into a purely linear one.
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
- **Idea:** For each position in the coin row, we store the maximum amount of money collected so far. When a new position is evaluated, we determine whether adding the current coin to the optimal sum (or subsequence of coins) found in the previous non-adjacent cells yields a better total than simply carrying forward the maximum amount found in the immediately preceding cell (in this temporal storage or structure at the position N we will have the maximum total sum of coins).
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
- **Idea:** To discover the longest increasing subsequence ending at a particular element, we can look backwards at all the previous elements that are strictly smaller than the current one. We then safely "extend" the longest of those valid previous subsequences by 1. By doing this iteratively from left to right, we build the globally longest sequence (In contrast to the previous exercise where the solution was found at the end of `dp`, here we have to find the maximum value in `dp`).
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

### 4. Knapsack Problem (`knapsack_problem/main.cpp`)
In this example, we apply dynamic programming to solve the 0/1 Knapsack Problem, a classic optimization problem. *(See the [Spanish explanation](knapsack_problem/README.md))*

The Knapsack Problem is defined as follows:
Given $n$ items with:
- Integer weights: $w_1, w_2, \dots, w_n$
- Values: $v_1, v_2, \dots, v_n$

and a knapsack of integer capacity $W$.

- **Goal:** Find the most valuable subset of items that fit into the knapsack. In our provided code, we have 4 items with weights `{2, 1, 3, 2}` and values `{12, 10, 20, 15}`, and a total knapsack capacity of `W = 5`.
- **Idea:** To maximize the value, we consider items piece by piece while varying the intermediate capacity limit up to the maximal capacity $W$. At each step while sequentially going through the items, for each possible capacity limit, we evaluate whether to include the current item or not. If we include it, the remaining capacity decreases by the item's weight, and we add its value to the optimal value found for the remaining capacity among the items we have already considered.
- **Algorithm:** The proposed solution makes use of a bottom-up, 2D dynamic programming approach.
  - A state array `dp[N+1][W+1]` is used, where `dp[i][j]` represents the maximum value that can be obtained from a subset of the first `i` items, considering a knapsack with maximum weight capacity `j`.
  - First, we iterate over all item counts `i` from $1$ to $N$, and nested inside we iterate over all capacities `j` from $1$ to $W$. Base cases (0 items or 0 capacity) are initialized to 0.
  - For each element evaluation, we check if the current item's weight (`weights[i-1]`) fits the capacity restriction (`j`). If it does not, we cannot select the item and pull the optimal value from the previous phase: `dp[i][j] = dp[i-1][j]`.
  - If we can pack the item, we branch between two decisions: either discarding the item, getting a value of `dp[i-1][j]`, or putting the item in the knapsack, gaining its value plus the optimal configuration of the remaining capacity `value + dp[i-1][j - weight]`.
  - The maximum of both choices is stored in `dp[i][j]`.
  - The final maximum value is obtained in `dp[N][W]`.
- **How to run:**
  ```bash
  cd knapsack_problem
  g++ -O2 -o knapsack main.cpp
  ./knapsack
  ```

- **Example Output:**
  ```bash
  37
  ```

### 5. Bird Cage Problem (Examen Parcial 2023-1) (`202301_middle_term_birds_problem/main.cpp`)
In this example, we apply dynamic programming to solve a combinatorial problem about arranging canaries and lovebirds (agapornis) in a 2-row cage grid, where no two lovebirds can be placed adjacent to each other (horizontally or vertically). *(See the [Spanish explanation](202301_middle_term_birds_problem/README.md))*

- **Goal:** Determine the total number of valid bird arrangements for a cage grid of 2 rows and $n$ columns, respecting the adjacency constraint for lovebirds.
- **Idea:** Each column can be in one of 3 valid states: both canaries (C/C), lovebird on top (A/C), or lovebird on bottom (C/A). The number of valid arrangements for $n$ columns can be built iteratively by tracking how many ways each state can be reached based on the previous column's state.
- **Algorithm:** The solution implements a State Machine DP approach using a `dp[3][N]` matrix.
  - `dp[0][i]`: number of valid arrangements ending in state C/C at column `i`.
  - `dp[1][i]`: number of valid arrangements ending in state A/C at column `i`.
  - `dp[2][i]`: number of valid arrangements ending in state C/A at column `i`.
  - State C/C can follow any previous state. States A/C and C/A cannot follow themselves (to avoid adjacent lovebirds).
  - The final answer is `dp[0][n] + dp[1][n] + dp[2][n]`.
- **How to run:**
  ```bash
  cd 202301_middle_term_birds_problem
  g++ -O2 -o birds main.cpp
  ./birds
  ```

- **Example Output (n=2):**
  ```bash
  7
  ```

### 6. Robot Wood Cutter (Examen Parcial 2023-1) (`202301_middle_term_exam_robot_cut_woods/main.cpp`)
In this example, we apply dynamic programming to solve a variation of the Weighted Interval Scheduling Problem where we want to cut logs to maximize benefit without using structural objects or classes. *(See the [Spanish explanation](202301_middle_term_exam_robot_cut_woods/README.md))*

- **Goal:** Maximize the total benefit obtained from cutting $N = 10$ logs, choosing among $M = 4$ possible presentations. Overlapping presentations in a given log cannot be cut.
- **Idea:** Using dynamic programming, after sorting the presentations by their end positions, we can determine the maximum theoretical value for a single log. For each presentation piece, we calculate whether to include it (summing its benefit with the best non-overlapping past configuration) or simply discard it and keep the previously found optimal benefit. Because every log is equal, calculating the maximum benefit for one and multiplying the result by $N$ produces the optimal total result.
- **Algorithm:** The solution implements a bottom-up 1D dynamic programming approach inside a primitive multidimensional array.
  - A matrix acts as the data source to hold start times, end times, and benefits. It is strictly sorted by the `end` time component.
  - An array `dp` of size `N_PRESENTATIONS + 1` tracks accumulated optimums.
  - Exploring each presentation index `i`, we find the largest valid past presentation index `j` that doesn't overlap the new one's start time (`data[1][j] <= data[0][i]`).
  - The equation calculates `dp[i]` as the maximum between `dp[i-1]` (not cutting the piece) and `data[2][i] + dp[j]` (cutting the piece and adding its benefit).
- **How to run:**
  ```bash
  cd 202301_middle_term_exam_robot_cut_woods
  g++ -O2 -o robot_cut_woods main.cpp
  ./robot_cut_woods
  ```

- **Example Output (Showing DP values per index):**
  ```bash
  Sorted data 
  Presentation 1
  2
  4
  40
  Presentation 2
  5
  10
  30
  Presentation 3
  6
  12
  80
  Presentation 4
  4
  15
  100
  0). 40
  1). 80
  2). 80
  3). 120
  4). 140
  ```

### 7. Coin Line Problem (`coin_line_problem/main.cpp`)
In this example, we apply dynamic programming (top-down memoization) to count the number of valid ways to arrange a line of coins given a fixed set of denominations, subject to the constraint that no two adjacent coins in the line may share the same denomination.

The problem is defined as follows:
> Given `p` coins of 1 sol, `q` coins of 2 soles, and `r` coins of 5 soles, in how many ways can we arrange all coins in a single line such that no two coins of the same type are placed next to each other?

- **Goal:** Count every distinct ordering of the `p + q + r` coins where no two consecutive coins have the same denomination. For the provided example (`p=2`, `q=2`, `r=1`), the answer should be printed to standard output.
- **Idea:** Model the problem as a recursive search over the remaining coin counts. At each step we choose which denomination to place next, with the only restriction being that we cannot repeat the denomination that was just placed. Memoizing the result for every `(p, q, r, last)` tuple avoids recomputing the same subproblem multiple times, turning an otherwise exponential search into a polynomial one.
- **Algorithm:** The solution implements a top-down memoization approach using a 4-dimensional DP table.
  - The state is defined by `dp[p][q][r][last_idx]`, where `p`, `q`, and `r` represent the remaining counts of each coin type and `last_idx ∈ {0, 1, 2, 3}` encodes the denomination of the coin placed last (`0` = none yet).
  - **Base case:** When `p == 0 && q == 0 && r == 0`, all coins have been placed successfully → return `1`.
  - **Recursive case:** For each denomination that still has coins left *and* differs from `last_idx`, recursively count the ways of completing the arrangement, summing all valid branches.
  - Computed values are stored in the `dp` table (initialized to `-1`) before returning, so each state is solved at most once.
  - The total number of valid arrangements is obtained by calling `count_ways(dp, p, q, r, 0)`.
- **How to run:**
  ```bash
  cd coin_line_problem
  g++ -O2 -o coin_line main.cpp
  ./coin_line
  ```

- **Example Output (`p=2, q=2, r=1`):**
  ```bash
  Para p=2, q=2, r=1
  El numero de formas validas es: 12
  ```

---

[← Back to course root](../README.md)
