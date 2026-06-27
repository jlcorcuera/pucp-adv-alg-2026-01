# 🧬 Chapter 5: Evolutionary Algorithms

This folder contains the theoretical foundations and concepts related to **Evolutionary Computation**, specifically focusing on **Genetic Algorithms (GA)** based on the course materials. Evolutionary computation is a branch of Artificial Intelligence that simulates natural evolutionary processes — such as selection, reproduction, and mutation — through algorithmic methods, providing a robust framework for solving complex combinatorial optimization problems.

## 🌿 Key Concepts in Evolutionary Computation

Evolutionary computation is grounded in the biological theory of evolution proposed by Charles Darwin in 1859. The following components define the evolutionary process that GAs replicate:

1. **Population:** A set of candidate individuals (solutions) subject to evolutionary pressure at each generation.
2. **Variation:** Changes in one or more characteristics across individuals, enabling exploration of the solution space.
3. **Inheritance:** Transmission of traits (genes) from parent individuals to their offspring.
4. **Selection:** Differential survival and reproduction rates — fitter individuals reproduce more, driving the population toward better solutions.

## 🔍 Fundamental Definitions

- **Individual (Chromosome):** A candidate solution to the problem, encoded as a string of bits or characters (genes). The encoding strategy is the most critical design decision in any GA.
- **Population:** The set of all individuals in a given generation. GAs operate over populations, not single states.
- **Fitness Function:** A function $f: SS \rightarrow \mathbb{R}$ that measures the quality (adaptation level) of each individual. It plays the role of the objective function and drives the selection process.
- **Generation:** One complete cycle of evaluation, selection, and reproduction applied to a population.
- **Selection Probability:** Given a population of $N$ individuals, the probability that individual $i$ is selected for reproduction is:
  $$P_i = \frac{f(x_i)}{\sum_{j=1}^{N} f(x_j)}$$

## 🚀 Genetic Algorithms (GA)

Introduced by John Holland in 1975 in his foundational book *"Adaptation in Natural and Artificial Systems"*, Genetic Algorithms are computational search methods that operate over populations of encoded candidate solutions, imitating evolution and natural selection. David Goldberg, Holland's student, achieved the first industrial applications of GAs in 1980.

### Main Characteristics
- **Population-based:** GAs operate on an entire population of individuals simultaneously, not on a single state.
- **Encoded individuals:** Each candidate solution is encoded as a chromosome — typically a binary string (bit chain).
- **Fitness-guided:** A fitness function assigns a quality value to each individual, directing the search toward better solutions.
- **Probabilistic operators:** Selection, crossover, and mutation use probabilistic rules, enabling exploration of the solution space without exhaustive search.

### Algorithm Stages

A Genetic Algorithm executes the following stages iteratively until a stopping condition is met (e.g., maximum number of generations or convergence):

#### 1. Chromosomal Encoding
Each candidate solution is mapped to a chromosome — a binary string of $N$ bits or a sequence of characters acting as genes. The encoding determines the structure of the search space.
- **Example:** To maximize $f(x) = x^2$ for $x \in [0, 63]$, each individual is encoded as a 6-bit binary string (since $2^6 = 64$). The number 12 is encoded as `001 100`, and 61 as `111 101`.
- The chromosome size $N$ must be large enough to represent all valid individuals in the domain.

#### 2. Fitness Evaluation
Each individual in the population is evaluated using the fitness function to determine how well-adapted it is.
- The fitness value guides selection: individuals with higher fitness have a higher probability of being chosen to reproduce.
- **Example:** For the initial population $\{1, 12, 20, 61\}$ with $f(x) = x^2$, the fitness values are $1$, $144$, $400$, and $3721$ respectively. Individual 61 dominates with an 87.22% selection probability.

#### 3. Selection
The fittest individuals are selected for reproduction using pseudo-random techniques. The most common method is the **Roulette Wheel**:
- A roulette with 100 slots is defined; each individual is assigned slots proportional to its selection probability.
- The wheel is spun $k$ times to determine the selected individuals, where $k$ is the **population rate (density)** expressed as a percentage of the original population.

#### 4. Application of Genetic Operators
Selected individuals undergo reproduction and variation through three genetic operators:

- **Crossover (Casamiento):** Two parent individuals exchange portions of their chromosomes to produce offspring. The number of genes exchanged is the **crossover rate**.
  - *Example:* Crossing `001 100` (12) and `111 101` (61) at position 3 produces children `001 101` (13) and `111 100` (60).
- **Mutation (Mutex):** A gene at a specific position is flipped (negated) with a given **mutation rate** (probability). Mutation rates are kept low to avoid disrupting well-adapted individuals and to prevent producing aberrations (offspring worse than their parents) or clones (identical duplicates).
- **Inversion:** The chromosomal representation of an individual is reversed. This operator is applied only when a poorly adapted individual has slipped into the population, since inverting a good individual typically produces a worse one.

## 📚 References
- Goldberg, D. (1989). *Genetic Algorithms in Search, Optimization and Machine Learning*. Addison-Wesley, England.
- Davis, L. (1990). *Handbook of Genetic Algorithms*. VNR Company Library, USA.
- Pacheco, M. (1996). *Algoritmos genéticos: princípios e aplicações*. PUCP-Río, Brazil.
- Holland, J. H. (1975). *Adaptation in Natural and Artificial Systems*. University of Michigan Press, USA.

---

[← Back to course root](../README.md)
