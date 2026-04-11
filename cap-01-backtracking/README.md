# ♟️ Chapter 1: Backtracking

This folder contains the class exercises and algorithm implementations related to **Backtracking**. Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, primarily constraint satisfaction problems. It incrementally builds candidates for the solutions, and abandons a candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

## 📑 Table of Problems
- [1. Maze Escape Problem](#1-maze-escape-problem-maze_problempath_findingcpp)
- [2. N-Queens Problem](#2-n-queens-problem-n_queen_problemmaincpp)
- [3. Meat Orders Problem (Lab 01 2024-1)](#3-meat-orders-problem-lab-01-2024-1-meat_problemmaincpp)
- [4. Equal Partition Problem (Lab 01 2026-1)](#4-equal-partition-problem-lab-01-2026-1-lab01_202601_equal_partitionmaincpp)
- [5. Wood Cut Problem (Lab 01 2026-1)](#5-wood-cut-problem-lab-01-2026-1-lab01_202601_wood_cut_problemmaincpp)

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

- **Note on Alternative Approach:** The approach applied to solve this problem here is similar to the ones previously implemented (iterating through standard choices in `build_order_with_loop`). *Is there any other way to solve this problem?* The answer is yes: by using a binary decision approach—considering whether to **include or not include** the current piece of meat in the solution at each recursive step—we can eliminate the need for the `for` loop inside our recursive method completely. This alternative has been implemented in the `build_order_with_binary_decision` method. Note that this alternative method may produce different results due to the differing nature of the search approach.

### 4. Equal Partition Problem (Lab 01 2026-1) (`lab01_202601_equal_partition/main.cpp`)
This problem was evaluated during Lab 01 in the current 2026-01 semester. It requires splitting an array of numbers into two subsets that have perfectly equal sums.

- **Goal:** Given a set of integers, divide it into two disjoint subsets such that the sum of the elements in both subsets is exactly the same.
- **Algorithm:** The algorithm first calculates the total sum of the array. If it is odd, equal partition is impossible. If even, it uses backtracking to find a subset that sums exactly to half of the total sum. The codebase features two different backtracking approaches to solve this:
  1. **Iterative Approach (`solve_backtracking`):** Uses a `for` loop within the recursive method to iterate over the remaining unselected elements. In each step, it attempts to include the chosen element and recursively checks if the remaining target sum can be satisfied.
  2. **Binary Decision Approach (`solve_backtracking_decision`):** Eliminates the `for` loop completely by making a direct binary choice at each recursive step. For the current element, it branches into two recursive paths: one that *includes* the element in the subset, and another that *excludes* it.
  
  In both methods, once the first subset that sums to `total/2` is successfully found, the remaining unpicked elements naturally form the second subset.
- **How to run:**
  ```bash
  cd lab01_202601_equal_partition
  g++ -O2 -o equal_partition main.cpp
  ./equal_partition
  ```

- **Example Output (Valid Partition subsets):**
  ```bash
  {5, 3} {4, 2, 1, 1}
  ```

### 5. Wood Cut Problem (Lab 01 2026-1) (`lab01_202601_wood_cut_problem/main.cpp`)
This problem was also evaluated during Lab 01 in the 2026-01 semester. Given an $N \times M$ matrix of wood, the goal is to make the maximum number of continuous cuts of length $C$ without overlapping. Both the board dimensions and the cut size can be modified via constants.

- **Goal:** Maximize the number of consecutive cuts of length $C$ (horizontal or vertical) on an $N \times M$ matrix structure without overlapping. A special constraint requires each subsequent cut search to originate from one of the 8 adjacent cells surrounding the *end* of the previously made cut.
- **Algorithm:** Uses a recursive backtracking approach to explore cuts. From any given position `(row, col)`, the algorithm:
  - Tries to make a cut of length `C` in 4 possible directions (Down, Left, Up, Right).
  - Verifies that the entire cut stays within the board boundaries and does not overlap with previously made cuts.
  - If a valid cut is made, the matrix is updated with the current cut number, and maximum tracking variables are updated if the new count is higher.
  - From the last position of the successfully made cut, it explores the 8 immediately neighboring cells to start the recursive search for the next cut.
  - Finally, it backtracks by undoing the cut completely to allow exploration of other alternative cuts.
- **How to run:**
  ```bash
  cd lab01_202601_wood_cut_problem
  g++ -O2 -o wood_cut main.cpp
  ./wood_cut
  ```

- **Example Output (Maximum Cuts and Placement Matrix):**
  ```bash
  max_num_cuts: 7
  Final result
  1   7 7 7 
  1 6 6 6 4 
  1 5 5 5 4 
  2 2 2   4 
      3 3 3 
  ```

---

[← Back to course root](../README.md)
