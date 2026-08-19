# 🚀 Milestone 1 — 42 School

This repository contains my completed projects for **Milestone 1** of the 42 programming curriculum.

---

## 📚 Projects

### 🖨️ ft_printf

Reimplementation of the standard `printf` function in C.

**Features:**

* Supports conversions: `c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, `%`
* Handles flags, width, and formatting
* Modular and extensible design

**Usage:**

```bash
make
```

```c
ft_printf("Hello %s!\n", "world");
```

---

### 📖 get_next_line

Function that reads a file descriptor line by line.

**Features:**

* Reads from any file descriptor
* Handles multiple file descriptors (if bonus implemented)
* Efficient buffer management
* No memory leaks

**Usage:**

```c
char *line = get_next_line(fd);
```

---

### 🔢 push_swap

Sorting algorithm project using two stacks and limited operations.

**Goal:**
Sort a list of integers with the minimum number of operations.

**Features:**

* Multiple sorting strategies:

  * Simple (O(n²))
  * Chunk-based (O(n√n))
  * Radix (O(n log n))
  * Adaptive (default)
* Custom flags:

  * `--simple`
  * `--medium`
  * `--complex`
  * `--adaptive`
  * `--bench`
* Includes checker program

**Usage:**

```bash
make
./push_swap 3 2 1
```

```bash
ARG="5 3 1 4 2"
./push_swap $ARG | ./checker $ARG
```

---

## 🛠️ Technologies

* Language: C
* Compiler: `cc`
* Flags: `-Wall -Wextra -Werror`

---

## 🎯 Learning Outcomes

* Memory management
* Data structures (linked lists, stacks)
* Algorithm optimization
* Parsing and error handling
* Low-level I/O operations

---

## 📊 Performance

### push_swap benchmarks:

* **100 numbers:** ~530–620 operations ✅ (full score)
* **500 numbers:** ~4950–5200 operations ✅ (full score)

---

## 📌 Notes

* All projects follow 42 Norm
* No external libraries used (except allowed ones)
* Code reviewed and tested extensively

---

## 👩‍💻 Author

**agaleksa**

---

> Part of the 42 Network curriculum — focused on low-level programming and algorithmic thinking.
