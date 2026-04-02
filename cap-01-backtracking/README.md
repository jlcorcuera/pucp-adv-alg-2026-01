# ♟️ Chapter 1: Backtracking

This folder contains the class exercises and algorithm implementations related to **Backtracking**. Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, primarily constraint satisfaction problems. It incrementally builds candidates for the solutions, and abandons a candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

## 📁 Directory Contents

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

### 3. Previous Labs problems *(to be developed during the lecture)*
Code and solutions for problems covered in previous laboratory sessions are included under this section.

---

[← Back to course root](../README.md)
