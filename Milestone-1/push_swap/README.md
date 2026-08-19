*This project has been created as part of the 42 curriculum by agaleksa, ssaghate.*

# push_swap

## Description

`push_swap` is a sorting algorithm project from the 42 curriculum. The goal is to sort a stack of integers using a limited set of operations, in as few moves as possible, using two stacks — `a` and `b`.

The program reads a list of integers as arguments, outputs the sequence of operations needed to sort stack `a` in ascending order, then exits. If the input is already sorted, nothing is printed.

### Available operations

**agaleksa**
| Operation | Effect                                |
|-----------|---------------------------------------|
| `sa`      | Swap the top 2 elements of stack a    |
| `sb`      | Swap the top 2 elements of stack b    |
| `ss`      | `sa` and `sb` simultaneously          |
| `pa`      | Push top of b onto a                  |
| `pb`      | Push top of a onto b                  |
| `ra`      | Rotate a upward (top becomes bottom)  |
| `rb`      | Rotate b upward                       |
| `rr`      | `ra` and `rb` simultaneously          |
| `rra`     | Reverse rotate a (bottom becomes top) |
| `rrb`     | Reverse rotate b                      |
| `rrr`     | `rra` and `rrb` simultaneously        |

---

## Instructions

### Compilation
**agaleksa**
```bash
make        # build push_swap
make clean  # remove object files
make fclean # remove object files and binary
make re     # full rebuild
```

Compiled with `cc -Wall -Wextra -Werror`.

### Usage
```bash
./push_swap 3 1 2
./push_swap "5 4 3 2 1"
./push_swap 42 -7 0 100 -3
```

### Optional flags
**agaleksa**
These flags are non-standard extensions added beyond the base project requirements:
```bash
./push_swap --simple   3 1 2    # force simple sort  (O(n²))
./push_swap --medium   3 1 2    # force medium sort  (chunk-based)
./push_swap --complex  3 1 2    # force complex sort (radix)
./push_swap --adaptive 3 1 2    # adaptive sort       (default)
./push_swap --bench    3 1 2    # print performance report after sorting
```

### Checking correctness
**ssaghate**
Pipe the output into a checker (if available):
```bash
ARG="5 3 1 4 2"
./push_swap $ARG | ./checker $ARG
```

Or use the included test suite:
```bash
chmod +x test_push_swap.sh
bash test_push_swap.sh ./push_swap
```

### Operation count reference (42 grading thresholds)

| Input size   | Full marks | Good   | Passing |
|--------------|------------|--------|---------|
| 3 elements   | ≤ 3 ops    | —      | —       |
| 5 elements   | ≤ 12 ops   | —      | —       |
| 100 elements | ≤ 700 ops  | ≤ 900  | ≤ 1500  |
| 500 elements | ≤ 5500 ops | ≤ 7000 | ≤ 11500 |

---

## Algorithms
**ssaghate**

This project implements four sorting strategies.

### Simple sort — O(n²) - selection

Used for very small inputs (≤ 5 elements via `sort_2`, `sort_3`, `sort_5`).

For slightly larger inputs: repeatedly find the minimum element in stack `a`, rotate it to the top, then push it to `b`. Once `a` is empty, push everything back. This is a selection sort adapted to stack operations.

**Justification:** straightforward to implement correctly and optimal for tiny inputs where the overhead of more complex algorithms is not worth it.

### Medium sort — O(n √n) — chunk-based

Used for inputs up to ~500 elements.

1. Assign each element a rank (0 to n−1) using `index_stack`.
2. Divide the ranked elements into chunks of size ~15 (for n ≤ 100) or ~30 (for n > 100).
3. Push elements from `a` to `b` chunk by chunk. Elements in the current chunk go straight to `b`; the next chunk also goes to `b` but gets rotated to the back, keeping higher-priority elements at the top.
4. Pull elements back from `b` to `a` by repeatedly finding and rotating the maximum to the top, then pushing to `a`.

**Justification:** medium sort consistently achieves ~550 ops on 100 elements and ~5000 ops on 500 elements, comfortably within 42's full-mark thresholds. Its chunk strategy minimises unnecessary rotations by keeping elements in a useful order on `b` during the push phase.

### Complex sort — O(n log n) — radix

Used for very large inputs.

1. Assign each element a rank (0 to n−1).
2. Sort by bits from least significant to most significant using LSD radix sort:
   - For each bit position: scan all elements in `a`. If the current bit is 0, push to `b`; if 1, rotate to the bottom of `a`.
   - After each pass, push everything from `b` back to `a`.

**Justification:** radix sort has a predictable, input-independent operation count. For 500 elements it uses ~6800 ops — slightly above medium sort for this range, so it is reserved for inputs where medium sort's O(n √n) chunk scanning becomes expensive.

### Adaptive sort (default)

Selects the algorithm based on input size:

- n ≤ 5 → simple sort
- n > 5 → medium sort

**Justification:** empirical testing showed that medium sort outperforms radix sort for all tested input sizes (up to 500 elements), so disorder-based routing was replaced with a simpler size-based decision. The disorder metric (`compute_disorder`, counting inversions) is still computed and shown in `--bench` output for informational purposes.

---

## Resources

- 42 intranet push_swap subject
- Stack data structure references
- Sorting algorithm resources
- GNU C Library documentation
- peer discussions and code reviews
- AI tools used only for reviewing code for potential issues

### AI usage

Claude (Anthropic) was used during this project for the following tasks:

- **Code review:** identifying bugs in `print_bench.c` (incorrect `t_stats*` to `t_program*` cast), `medium_sort.c` (missing `index_stack` call before chunk sorting), and `pars.c` (premature duplicate check inside the argv loop).
- **Norm compliance:** detecting misaligned variable declarations, commented-out code, and dead declarations in the header.
- **Test suite:** generating and iteratively fixing a bash test script (`test_push_swap.sh`) covering error handling, correctness verification via operation simulation, operation count thresholds, and edge cases.
