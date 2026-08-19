# libft

## 📌 Description

Libft is a custom implementation of standard C library functions developed as part of the 42 Yerevan curriculum.
The project focuses on understanding how low-level functions work and building a personal reusable C library.

---

## ⚙️ Features

* Reimplementation of core libc functions (`strlen`, `memcpy`, `atoi`, etc.)
* Advanced string and memory manipulation
* Dynamic memory allocation (`malloc`, `calloc`, `free`)
* Full linked list implementation
* Clean and modular code structure

---

## 🛠️ Technologies

* C
* Linux
* Makefile

---

## 🚀 Compilation

```bash
make
```

This will generate the **libft.a** static library.

---

## 🚀 Usage

Include the library in your project:

```c
#include "libft.h"
```

---

## 📌 Example

```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *str = "42 Yerevan";
    printf("Length: %d\n", ft_strlen(str));

    char *dup = ft_strdup(str);
    printf("Duplicate: %s\n", dup);

    free(dup);
    return 0;
}
```

---

## 🧠 What I Learned

* Memory management and pointer manipulation
* Implementation of low-level standard functions
* Writing clean, reusable, and modular C code
* Debugging and handling edge cases
* Understanding data structures (linked lists)

---

## 📂 Project Structure

* **Libc functions** – basic standard functions reimplemented
* **Additional functions** – extended string and utility functions
* **Linked list** – full implementation of list operations

---

## 🎯 Purpose

This project serves as a foundation for future C projects, allowing reuse of custom-built functions and deeper understanding of system-level programming.

---

## 👤 Author

Aghvan Aleksanyan
42 Yerevan Student
