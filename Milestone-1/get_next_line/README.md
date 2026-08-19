# get_next_line

## 📌 Description

`get_next_line` is a C function that reads a file descriptor line by line.
Each call returns the next line, including the newline character (`\n`) if present.

---

## ⚙️ Features

* Reads from file descriptor using `read()`
* Handles arbitrary `BUFFER_SIZE`
* Supports multiple file descriptors (bonus)
* Efficient buffer and memory management
* Returns `NULL` on EOF or error

---

## 🛠️ Technologies

* C
* Linux
* File I/O
* Static variables

---

## 🚀 Compilation

```bash id="b4b1n7"
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c -o gnl
```

---

## 🚀 Usage

```c id="yngk1k"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}
```

---

## 📌 Example Output

```id="9x14au"
Line 1
Line 2
Line 3
```

---

## 🧠 How It Works

* Uses a `static` buffer to store leftover data between calls
* Reads from file descriptor until a newline is found
* Extracts one line and keeps the rest for the next call

---

## 🎯 Purpose

This project builds understanding of file I/O, memory management, and persistent state using static variables.

---

## 👤 Author

Aghvan Aleksanyan
42 Yerevan Student
