# Exitor - A Minimal Text Editor for xv6

**Exitor** is a minimalist VI-like text editor built for the [xv6 operating system](https://pdos.csail.mit.edu/6.828/2021/xv6.html). It provides basic file editing capabilities, copy-paste functionality, and a custom dynamic memory management system via user-defined system calls.

---

## Features

- **Modes**
  - `Insert Mode` – Press `i` to start typing.
  - `Command Mode` – Press `ESC` to enter command input.

- **Commands**
  - `:w`  → Save the file  
  - `:q`  → Quit without saving  
  - `:wq` → Save and quit  
  - `:y`  → Yank (copy) lines  
     - After typing `:y`, press `Enter`, then input the start line, press `Enter`, and input the end line.
  - `:p`  → Paste the previously yanked lines

- **Clipboard Support**
  - Yanked lines are stored in a fixed-size clipboard buffer (1024 bytes).
  - Only line-based copy-paste is supported.

- **Dynamic Memory Allocation (Custom)**
  - `xmalloc()`, `xfree()`, `xcalloc()`, and `xrealloc()` system calls implemented.
  - Uses a simple header-based allocator with validation and free-list management.

---

## System Calls Added

| System Call           | Description                                      |
|------------------------|--------------------------------------------------|
| `xmalloc(n)`           | Allocate `n` bytes of memory                     |
| `xfree(ptr)`           | Free previously allocated memory at `ptr`        |
| `xcalloc(n, s)`        | Allocate and zero-initialize `n * s` bytes       |
| `xrealloc(ptr, size)`  | Reallocate memory at `ptr` to `size`             |
| `clear()`              | Clears the screen (terminal)                     |
| `hello()`              | Prints "Hello World" to the console              |
| `exitor()`             | Prints Exitor banner and usage instructions      |

---

## Building & Running

1. Clone or integrate this project into your xv6 source tree.
2. Rebuild xv6 using:

   ```bash
   make clean
   make qemu
   ```

---

## Usage

To run **Exitor** inside xv6:

```bash
exitor <filename>
```

### Example:

```bash
exitor notes.txt
```

---

## Hint

If you are cloning this repo for your xv6 project, consider making the **copy** and **paste** functions system calls for better modularity and privilege separation. Since I added them as normal functions.

---
