# Exitor - A Minimal Text Editor for xv6

**Exitor** is a minimalist VI-like text editor built for the [xv6 operating system](https://pdos.csail.mit.edu/6.828/2021/xv6.html). It provides basic file editing capabilities, copy-paste functionality, and a custom dynamic memory management system via user-defined system calls.

---

## ✨ Features

- **Modes**
  - `Insert Mode` – Press `i` to start typing.
  - `Command Mode` – Press `ESC` to enter command input.

- **Commands**
  - `:w`  → Save the file
  - `:q`  → Quit without saving
  - `:wq` → Save and quit
  - `:y <start> <end>` → Yank (copy) lines from `<start>` to `<end>`
  - `:p` → Paste the previously yanked lines

- **Clipboard Support**
  - Yanked lines are stored in a fixed-size clipboard buffer (1024 bytes).
  - Only line-based copy-paste is supported.

- **Dynamic Memory Allocation (Custom)**
  - `xmalloc()`, `xfree()`, `xcalloc()`, `xrealloc()` system calls implemented.
  - Uses a simple header-based allocator with validation and free-list management.

---

## 🛠️ System Calls Added

| System Call   | Description                                      |
|---------------|--------------------------------------------------|
| `xmalloc(n)`  | Allocate `n` bytes of memory                     |
| `xfree(ptr)`  | Free previously allocated memory at `ptr`        |
| `xcalloc(n, s)` | Allocate and zero-initialize `n * s` bytes     |
| `xrealloc(ptr, size)` | Reallocate memory at `ptr` to `size`     |
| `clear()`     | Clears the screen (terminal)                     |
| `hello()`     | Prints "Hello World" to the console              |
| `exitor()`    | Prints Exitor banner and usage instructions      |

---

## 🧪 Usage

To run Exitor inside xv6:

```bash
$ exitor <filename>
