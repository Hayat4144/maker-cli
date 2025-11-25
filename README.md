# 📦 **maker-cli**

A lightweight and beginner-friendly CLI tool written in **C** that helps you quickly set up new JavaScript or TypeScript projects by:

- creating project folders
- resolving absolute & relative paths
- cloning template repositories
- providing a clean, colorful CLI UI

---

## 🚀 Features

- ✔ Create project folder automatically
- ✔ Works with **absolute**, **relative**, and **current (`.`)** paths
- ✔ Clean UI with colors & emojis
- ✔ Choose between **JavaScript** and **TypeScript** templates
- ✔ Git clone support
- ✔ Fully cross-platform (Linux, macOS, Windows via Git Bash/WSL)

---

## 📁 Folder Structure Created

Example:

```
/your/root/path/
    └── your-folder/
          └── (template files cloned here)
```

---

## 🔧 Installation

### 1. Clone the repository

```bash
git clone https://github.com/your-username/maker-cli.git
cd maker-cli
```

### 2. Build the CLI

```bash
gcc maker-cli.c -o maker-cli
```

### 3. Run the CLI

```bash
./maker-cli
```

On Windows (Git Bash / MinGW):

```bash
gcc maker-cli.c -o maker-cli.exe
./maker-cli.exe
```

---

## 📘 Usage

When you run the CLI, follow the interactive steps:

### ### **Step 1 — Enter paths**

You will be asked for:

```
Root path (blank or '.' = current dir):
Folder name:
```

### **Step 2 — Directory creation**

maker-cli automatically builds:

- `./folder`
- `root/folder`
- `/absolute/path/folder`

### **Step 3 — Select language**

Choose:

```
→ 1. JavaScript
→ 2. TypeScript
```

or type:

```
js
ts
```

### **Step 4 — Cloning template**

maker-cli will run:

```
git clone <template_repo> <target_folder>
```

---

## 📌 Supported Templates

| Type       | Template Repo             |
| ---------- | ------------------------- |
| JavaScript | `text-editor` template    |
| TypeScript | `folder-cleaner` template |

You can customize repositories inside `place_file()`.

---

## 🖥 Requirements

- **gcc** or clang
- **git** installed
- Unix-like terminal (Linux, macOS, WSL, Git Bash)

---

## 🔧 Customizing Templates

Inside `place_file()`:

```c
const char *repo =
    strcmp(type, "ts") == 0
        ? "https://github.com/Hayat4144/folder-cleaner.git"
        : "https://github.com/Hayat4144/text-editor.git";
```

Change URLs to your own boilerplates.

---

## 🧩 Contributing

Pull requests and issues are welcome!

---

## 📝 License

MIT License.

---
