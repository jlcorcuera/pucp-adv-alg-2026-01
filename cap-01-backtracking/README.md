# ♟️ Chapter 1: Backtracking

This folder contains the class exercises and algorithm implementations related to **Backtracking**. Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, primarily constraint satisfaction problems. It incrementally builds candidates for the solutions, and abandons a candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

## 📑 Table of Problems
- [1. Maze Escape Problem](#1-maze-escape-problem-maze_problempath_findingcpp)
- [2. N-Queens Problem](#2-n-queens-problem-n_queen_problemmaincpp)
- [3. Meat Orders Problem (Lab 01 2024-1)](#3-meat-orders-problem-lab-01-2024-1-meat_problemmaincpp)

## 📝 Problem Descriptions and Algorithms

### 1. Maze Escape Problem (`maze_problem/path_finding.cpp`)
In this example, we show how to use backtracking to navigate a 2D matrix representing a maze in order to find the **first escape route**.

- **Goal:** Find a valid path from the Start (`S`) to the Exit (`E`) avoiding walls (`#`).
- **Algorithm:** The proposed solution makes use of a recursive approach. From any given position, it tries 4 possible directions (Up, Right, Down, Left). 
  - If it finds a wall (`#`) or the cell was previously visited, it ignores it.
  - If a path reaches a dead end, the recursion unwinds (backtracks) and it tries the remaining directions (from previous recursive calls). 
  - The correct path taken is marked with `.`.
- **How to run:**
  ```bash
  cd maze_problem
  g++ -O2 -o path_finding path_finding.cpp
  ./path_finding
  ```

- **Example Output (The Path Found):**

  | Initial State | Solution |
  | ------------- | -------- |
  | <pre>S   #               <br>#   #   # # # # #   <br>#       #           <br># # #   #   # # # # <br>                  # <br>  # # # # # # #   # <br>  #           #   # <br>  #   # # #   #   # <br>      #           # <br># # # # # # # #   E </pre> | <pre>S . # . . . . . . . <br># . # . # # # # # . <br># . . . # . . . . . <br># # #   # . # # # # <br>          . . . . # <br>  # # # # # # # . # <br>  #           # . # <br>  #   # # #   # . # <br>      #         . # <br># # # # # # # # . E </pre> |

### 2. N-Queens Problem (`n_queen_problem/main.cpp`)
In this example, we show how to use backtracking to place $N$ non-attacking queens on an $N \times N$ chessboard. The code provided solves the classic 8-Queens problem.

- **Goal:** Place 8 queens on an $8 \times 8$ chessboard such that no two queens threaten each other. Thus, a solution requires that no two queens share the same row, column, or diagonal.
- **Algorithm:** The solution uses a recursive backtracking approach, iterating column by column. For a given column, it attempts to place a queen in every row. It checks if the placement is valid (no other queen is attacking it from the left).
  - If valid, it places the queen (`Q`) and proceeds to the next column recursively.
  - If it cannot place a queen in a valid position for the current column, it backtracks to the previous column and tries another valid row.
  - If all 8 queens are placed successfully, a solution is found and printed. The code will continue to find and print all valid solutions.
- **How to run:**
  ```bash
  cd n_queen_problem
  g++ -O2 -o n_queen main.cpp
  ./n_queen
  ```

- **Example Output (First Solution Found):**

  <pre>Q . . . . . . . <br>. . . . . . Q . <br>. . . . Q . . . <br>. . . . . . . Q <br>. Q . . . . . . <br>. . . Q . . . . <br>. . . . . Q . . <br>. . Q . . . . . </pre>

### 3. Meat Orders Problem (Lab 01 2024-1) (`meat_problem/main.cpp`)
This problem was evaluated during Lab 01 in the 2024-01 semester. It is based on the "Vaca Lola" livestock company, which fulfills large premium meat orders by assembling several pieces of meat to exactly match the requested weight.

- **Goal:** Fulfill meat orders of weight `P` using an available inventory of meat pieces represented by the vector `t` (where each $t_i \le P$). The selection of meat pieces for an order must satisfy two conditions:
  1. The sum of the pieces' weights equals exactly `P`.
  2. The weight of any added piece must differ by at most `k` units from at least one other piece already present in the order.
  Once a valid combination to fulfill an order is found, those pieces are reserved and can no longer be used for subsequent orders.
- **Algorithm:** The solution uses a recursive backtracking approach to build valid orders. For each recursive step, it iterates through the available pieces in the inventory vector `t`:
  - It sequentially tries to add a piece of meat from `t` if its weight doesn't exceed the remaining required weight to reach `P`.
  - It validates the tolerance condition: the piece's weight must have a difference of at most `k` when compared to at least one piece already in the current order (unless the order is empty).
  - If a valid combination reaching weight `P` is found, the pieces are confirmed as an order, their corresponding elements are erased from the inventory vector `t`, and the algorithm repeats the process from the beginning to satisfy as many orders as possible. If it fails, it backtracks to explore other combinations.
- **How to run:**
  ```bash
  cd meat_problem
  g++ -O2 -o meat_solver main.cpp
  ./meat_solver
  ```

- **Example Output (Satisfied Orders):**
  ```bash
  2
  Orden: 
  2 6 7 
  Orden: 
  9 6
  ```

---

[← Back to course root](../README.md)
