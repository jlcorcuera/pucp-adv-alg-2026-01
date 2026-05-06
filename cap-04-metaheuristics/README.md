# 🧬 Chapter 4: Metaheuristics

This folder contains the theoretical foundations and concepts related to **Metaheuristics**, specifically focusing on the **GRASP (Greedy Randomized Adaptive Search Procedure)** algorithm based on the course materials. Metaheuristics combine ideas from algorithm design techniques, specific problem-dependent algorithms, real-world inspiration, and statistical methods to find good solutions to complex combinatorial optimization problems.

## 📖 Key Concepts in Combinatorial Optimization

Regardless of the technique used, solving a combinatorial optimization problem requires specifying three basic concepts:

1. **Representation:** Encodes feasible solutions so they can be manipulated. It determines the size (cardinality) of the Search Space ($SS$) for each problem.
2. **Objective:** Describes the purpose to be achieved for a given representation. It is a mathematical predicate expressing the task to perform.
3. **Evaluation Function:** Associates a value to each feasible solution to determine its quality. It maps points from the solution space to $\mathbb{R}$. A solution must not only be found but must be a *feasible solution*, satisfying the problem's constraints. Thus, there is a clear difference between the broader Search Space ($SS$) and the Feasible Solutions Space ($F \subseteq SS$).

## 🔍 Fundamental Definitions

- **Neighborhood:** Given a solution $x \in SS$, its neighborhood $N(x)$ is a subset of the solution space containing solutions that are considered "close" to $x$.
- **Local Optimum:** Given an optimization problem $P = (f, SS, F)$ and a neighborhood structure $N$, a feasible solution $x \in F \subseteq SS$ is a local optimum (e.g., maximum) with respect to $N$ if:
  $$\forall y \in N(x), f(x) \ge f(y)$$

## 🚀 GRASP (Greedy Randomized Adaptive Search Procedure)

Developed by T. Feo and M. Resende in the late 1980s, GRASP relaxes the pure greedy criterion. Instead of strictly selecting a single best element at each step, it forms a set of candidate elements that meet certain conditions, and then randomly selects an element from this set to build the solution.

### Main Characteristics
- **Search Procedures:** They search within a space of possible solutions without exhaustively evaluating every element.
- **Greedy:** In each evaluation, they choose the best candidates satisfying certain conditions.
- **Adaptive:** They adapt to the structure of the specific problem instance being solved.
- **Randomized:** They randomly choose from the candidate list, effectively relaxing the strict greedy criterion.

### Algorithm Phases

A general GRASP algorithm runs iteratively, executing two main phases in a loop until a stopping condition is met:

#### 1. Construction Phase
Builds a relaxed or extended greedy solution where multiple candidates exist.
- It evaluates the greedy cost function $c(x)$ for all elements to find the best ($\beta$) and worst ($\tau$) values.
- It builds a **Restricted Candidate List (RCL)** containing elements $x$ that satisfy a certain threshold. For example:
  $$RCL = \{x \in N : \beta \le c(x) \le \beta + \alpha(\tau - \beta)\}$$
- The parameter $\alpha$ is the **GRASP relaxation parameter** ($0 \le \alpha \le 1$):
  - $\alpha = 0 \rightarrow$ Totally greedy criterion.
  - $\alpha = 1 \rightarrow$ Totally random criterion.
  - $0 < \alpha < 1 \rightarrow$ Conventional criterion requiring calibration for each problem.
- An element is chosen at random from the RCL and added to the solution. This process repeats until a complete solution is constructed.

#### 2. Improvement Phase (Local Search)
Since constructed solutions are not necessarily local optima, an improvement procedure (local search) is applied.
- It defines a neighborhood $F$ around the constructed solution.
- The local search iteratively replaces the current solution with a better one from its neighborhood, finishing when no better solution can be found to replace it.
- **Two basic improvement approaches:**
  1. **First Move:** The current solution is replaced by the *first* neighbor found that is better.
  2. **Best Move:** All neighbors in the neighborhood are analyzed, and the current solution is replaced by the *best* overall neighbor.

## 📚 References
- Feo, T. A., & Resende, M. G. (1995). "Greedy randomized adaptive search procedures". *Journal of global optimization*, 6(2), 109-133.
- Duarte, Pantrigo y Gallego. *Metaheurísticas*. Madrid. Universidad Rey Juan Carlos, 2007.
- TUPIA, M. *Fundamentos de Inteligencia Artificial*. 2da edición. Perú: 2014.

---

[← Back to course root](../README.md)
