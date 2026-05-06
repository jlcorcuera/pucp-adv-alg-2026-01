# 🧭 Chapter 3: Heuristics and Greedy Algorithms

This folder contains the theoretical foundations and practical C++ implementations related to **Heuristics** and **Greedy Algorithms**. In combinatorial optimization, exact methods can sometimes be computationally prohibitive. Heuristics provide a way to find "good enough" approximate solutions in a reasonable amount of time, especially for NP-hard problems.

## 📖 Theoretical Concepts

### Combinatorial Optimization
Solving a combinatorial optimization problem involves finding the "best" or "optimal" solution from a set of alternative solutions. To solve large problems, there are generally two paths:
1. **Exact Optimality:** Methods like Dynamic Programming or Linear Programming guarantee the best solution but risk immense, sometimes impractical, computation times.
2. **Approximation (Heuristics):** Methods that obtain solutions quickly, accepting the risk of sub-optimality.

### Heuristics
Heuristics are exploratory algorithms that evaluate a progressive set of elements without an exhaustive search. They are justified when:
- No exact method exists or it requires too much processing time.
- An exact solution is not strictly necessary.
- There are time, data, or hardware limitations.
- They are used as an intermediate step for other algorithms.

### Greedy Algorithms (Algoritmos Voraces)
A specific type of heuristic that builds a solution piece by piece, always choosing the next piece that offers the most immediate benefit.
- **Greedy:** It always picks the candidate with the best immediate objective function value.
- **Myopic:** The choice is unique and unmodifiable; it does not analyze the long-term effects of selecting an element.

## 📑 Table of Problems
- [1. Backpack Problem](#1-backpack-problem-backpackmaincpp)
- [2. Coin Change Problem](#2-coin-change-problem-coin_changemaincpp)
- [3. Fabric Cutter / Task Scheduling Problem](#3-fabric-cutter-task-scheduling-fabric_cuttermaincpp)
- [4. Project Selection Problem](#4-project-selection-problem-project_selectionmaincpp)

## 📝 Problem Descriptions and Algorithms

### 1. Backpack Problem (`backpack/main.cpp`)
- **Goal:** Given a set of $n$ objects with specific weights and a backpack with a maximum capacity, fill the backpack using the minimum remaining space without exceeding the limit.
- **Algorithm:** The greedy approach sorts the packages in ascending order of their weights. It then sequentially adds packages to the backpack as long as the remaining capacity allows it, prioritizing the lightest items first to potentially fit more items.
- **How to run:**
  ```bash
  cd backpack
  g++ -O2 -o backpack_solver main.cpp
  ./backpack_solver
  ```

### 2. Coin Change Problem (`coin_change/main.cpp`)
- **Goal:** Return a specific amount of money using the minimum possible number of coins from a given set of denominations.
- **Algorithm:** The code implements and compares two approaches:
  1. **Dynamic Programming:** Finds the exact optimal solution by building a table of minimum coins needed for all values up to the target amount.
  2. **Greedy Approach:** Sorts denominations in descending order and repeatedly picks the largest denomination coin that is less than or equal to the remaining amount.
- **How to run:**
  ```bash
  cd coin_change
  g++ -std=c++11 -O2 -o coin_change main.cpp
  ./coin_change
  ```

### 3. Fabric Cutter / Task Scheduling (`fabric_cutter/main.cpp`)
- **Goal:** Given $K$ looms (machines) with different weaving speeds and $N$ fabrics (tasks) of different sizes, find the minimum time (makespan) to finish weaving all fabrics, with the constraint that one fabric cannot be split across multiple looms.
- **Algorithm:** A greedy algorithm that assigns each fabric to the loom that will finish its current assigned workload the earliest. It iterates through the fabrics and adds each to the machine with the minimum expected completion time (`workload + fabric_size * machine_time_per_meter`).
- **How to run:**
  ```bash
  cd fabric_cutter
  g++ -O2 -o fabric_cutter main.cpp
  ./fabric_cutter
  ```

### 4. Project Selection Problem (`project_selection/main.cpp`)
- **Goal:** Select the most convenient investment projects without exceeding a maximum budget $P$. Projects have associated costs, profits, benefits, and potentially prerequisite projects (predecessors) that must be selected first.
- **Algorithm:** A greedy strategy that first sorts the projects based on a custom heuristic metric: `(benefit * profit) / cost`. It then continually evaluates the sorted candidate list and selects projects if they fit within the remaining budget and all their precedence constraints are met.
- **How to run:**
  ```bash
  cd project_selection
  g++ -O2 -o project_selection main.cpp
  ./project_selection
  ```

---

[← Back to course root](../README.md)
