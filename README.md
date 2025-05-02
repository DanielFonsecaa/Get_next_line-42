<div align="center">
  
  ![get_next_linee](https://github.com/user-attachments/assets/5240b10b-79f2-4812-a575-be0e34f9ee63)
</div>

# get_next_line

`get_next_line` is a function that reads a line from a file descriptor (like standard input, files, or sockets) and returns the line, including its newline character. The function is designed to handle large files and works without using libraries like `getline`.

## 📝 Overview

This project focuses on writing a function `get_next_line` that reads one line at a time from a file descriptor. The function should return a string (a line) when it’s called repeatedly. The function is useful for reading lines from a file or input stream one by one, instead of reading the entire file at once.

## ✨ Features

- Reads one line at a time from a file descriptor.
- Handles reading from files, `stdin`, and other sources.
- Efficient and optimized for handling large files or data streams.
- Does not use the `getline` function (i.e., you implement the line-reading behavior from scratch).

## 🚀 Getting Started

### Prerequisites

- GCC or any C-compatible compiler
- `make`

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/get_next_line.git
   cd get_next_line
2. Compile the program:

        make

Testing the Function
To test get_next_line, create a C file that includes get_next_line.h, call the function, and print the result to the console.

Example main.c:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("sample.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```
💡 Example of Usage:
If you have a file sample.txt:

```txt
Hello, world!
This is a second line.
And this is the third.
```
After running the program with get_next_line, it will output:
```
Hello, world!
This is a second line.
And this is the third.
```
Each line will be printed separately as get_next_line returns one line at a time.

