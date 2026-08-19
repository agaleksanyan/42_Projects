# ft_printf

## 📌 Description

`ft_printf` is a custom implementation of the standard C `printf` function, developed as part of the 42 Yerevan curriculum.
It replicates core formatting behavior and returns the number of printed characters.

---

## ⚙️ Features

Supported format specifiers:

| Specifier  | Description             |
| ---------- | ----------------------- |
| `%c`       | Character               |
| `%s`       | String                  |
| `%p`       | Pointer address         |
| `%d`, `%i` | Signed integer          |
| `%u`       | Unsigned integer        |
| `%x`       | Hexadecimal (lowercase) |
| `%X`       | Hexadecimal (uppercase) |
| `%%`       | Percent sign            |

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

This will generate the **libftprintf.a** static library.

To clean files:

```bash
make clean
make fclean
make re
```

---

## 🚀 Usage

```c
#include "ft_printf.h"

int main(void)
{
    int ret;

    ret = ft_printf("Hello, %s! Score: %d%%\n", "Alice", 95);
    ft_printf("Printed characters: %d\n", ret);

    return 0;
}
```

---

## 📌 Example Output

```
Hello, Alice! Score: 95%
Printed characters: 33
```

---

## 🧠 Implementation Details

* Uses low-level `write()` for output
* Handles `NULL` strings (`(null)`)
* Handles `NULL` pointers (`(nil)`)
* Supports variadic arguments (`va_list`)
* Recursive handling of numbers and hex values

---

## 📂 Project Structure

* **Parsing** – format string processing
* **Printing** – character, string, number output
* **Utilities** – helper functions for conversion

---

## 🎯 Purpose

This project strengthens understanding of variadic functions, formatting logic, and low-level output handling in C.

---

## 👤 Author

Aghvan Aleksanyan
42 Yerevan Student
