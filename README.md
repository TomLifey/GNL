
*This project has been created as part of the 42 curriculum by mabutair.*

# get_next_line

The **get_next_line** project is part of the 42 curriculum. The goal is to create a function that reads a file descriptor line by line, returning one line per function call.

This project introduces important concepts in C programming, including file descriptors, static variables, dynamic memory allocation, and buffer management.

## 📖 Table of Contents

- [Description](#description)
- [Features](#features)
- [Instructions](#instructions)
- [Algorithm](#algorithm)
- [Mandatory vs Bonus](#mandatory-vs-bonus)
- [Resources](#resources)
- [AI Usage](#ai-usage)

## Description

`get_next_line()` reads from a file descriptor and returns the next line whenever it is called.

The function handles different `BUFFER_SIZE` values and preserves unread data between calls. The bonus part extends this functionality to support multiple file descriptors simultaneously.

## Features

### Mandatory Part

- Read a file one line at a time.
- Support different `BUFFER_SIZE` values.
- Handle empty lines.
- Handle files ending with or without a newline.
- Return `NULL` when EOF is reached or an error occurs.
- Preserve unread data between function calls.

### Bonus Part

- Handle multiple file descriptors simultaneously.
- Support alternating reads from different files.
- Maintain independent buffers for each file descriptor.
- Preserve unread data separately for each file descriptor.

## Instructions

### Compilation

The project can be compiled using `cc` with the following flags:

**Mandatory:**

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

**Bonus:**

```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c
```

By default, `BUFFER_SIZE` is set to `42` in the header file.

You can specify a different buffer size during compilation using `-D BUFFER_SIZE`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 get_next_line.c get_next_line_utils.c
```

**Note:** Header files (`.h`) do not need to be passed to the compiler separately because they are included automatically through `#include`.

### Usage

Include the appropriate header in your C program.

**Mandatory:**

```c
#include "get_next_line.h"
```

**Bonus:**

```c
#include "get_next_line_bonus.h"
```

Example:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

Compile your program together with the appropriate source files.

## Algorithm

The algorithm reads data in chunks and stores unread characters until a complete line can be extracted.

### 1. Reading

- Allocate a temporary buffer of `BUFFER_SIZE + 1` bytes.
- Use `read()` to read data from the file descriptor.
- Continue reading until a newline (`\n`) is found, EOF is reached, or an error occurs.

### 2. Saving Data

- Join the newly read data with previously saved data using `ft_strjoin()`.
- Free the previous allocation after successfully creating the new string.
- Preserve accumulated data between function calls using a static variable.

### 3. Extracting a Line

- Once a newline is found or EOF is reached, `ft_get_line()` extracts the next line.
- The returned line includes the newline character when one exists.

### 4. Handling Leftovers

- `ft_get_leftovers()` stores the remaining characters for the next function call.
- The previous saved string is freed after the remaining data has been copied.

### Why This Algorithm?

Reading data in chunks makes the function independent of line length and buffer size.

Using a static variable allows unread data to remain available between function calls without requiring the user to manage the buffer manually.

Separating the logic into helper functions makes the implementation easier to understand, maintain, and debug.

## Mandatory vs Bonus

| Mandatory | Bonus |
|:---:|:---:|
| One static pointer | Array of static pointers |
| One file descriptor at a time | Multiple file descriptors |
| One saved buffer | Independent saved buffers |
| Basic line reading | Alternating file reading |

The bonus implementation uses an array of static pointers:

```c
static char *saved[OPEN_MAX];
```

This allows each file descriptor to maintain its own unread data independently.

## Resources

The following resources were useful for understanding the concepts used in this project:

- [`read()` — Linux Manual](https://man7.org/linux/man-pages/man2/read.2.html)
- [`open()` — Linux Manual](https://man7.org/linux/man-pages/man2/open.2.html)
- [`malloc()` and `free()` — Linux Manual](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [Static Variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [42 School](https://42.fr/)

## AI Usage

AI (ChatGPT) was used as a learning and assistance tool throughout this project.

It helped with:

- Understanding potential edge cases in the `get_next_line` implementation.
- Reviewing the mandatory and bonus algorithms.
- Identifying possible memory management issues.
- Suggesting test cases for different buffer sizes and file descriptors.
- Understanding Valgrind output.
- Assisting with debugging compilation errors.
- Preparing and organizing the README documentation.

The implementation, code modifications, testing, and final decisions were carried out by the student.

---

*Made as part of the 42 curriculum.*