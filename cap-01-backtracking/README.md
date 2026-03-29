# ♟️ Chapter 1: Backtracking

This folder contains the class exercises and algorithm implementations related to **Backtracking**. Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, primarily constraint satisfaction problems. It incrementally builds candidates for the solutions, and abandons a candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

## 📁 Directory Contents

### 1. Maze Escape Problem (`maze_problem/path_finding.cpp`)
In this example, we show how to use backtracking to navigate a 2D matrix representing a maze in order to find an escape.

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
  *(Note: The code was slightly fixed from the original commit to ensure it properly compiles with `main()`).*

- **Example Output (The Path Found):**

  | Initial State | Solution |
  | ------------- | -------- |
  | <pre>S   #               <br>#   #   # # # # #   <br>#       #           <br># # #   #   # # # # <br>                  # <br>  # # # # # # #   # <br>  #           #   # <br>  #   # # #   #   # <br>      #           # <br># # # # # # # #   E </pre> | <pre>S . # . . . . . . . <br># . # . # # # # # . <br># . . . # . . . . . <br># # #   # . # # # # <br>          . . . . # <br>  # # # # # # # . # <br>  #           # . # <br>  #   # # #   # . # <br>      #         . # <br># # # # # # # # . E </pre> |

### 2. N-Queens Problem *(to be developed during the lecture)*
Code for the classic 8-Queens problem will be added here shortly. This will demonstrate how to place 8 non-attacking queens on a chessboard using state-space search pruning.

### 3. Previous Labs problems *(to be developed during the lecture)*
Code and solutions for problems covered in previous laboratory sessions are included under this section.

---

[← Back to course root](../README.md)
