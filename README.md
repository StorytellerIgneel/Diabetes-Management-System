# Diabetes Management System

A console-based C++ application designed to manage users and administrators in a diabetes care system. This project focuses on access control, data handling, and modularity using C++ features like `map`, function pointers, and file I/O across multiple custom header files.

## 📌 Features

- **User & Admin Login** system with access control
- **Cyclic Data Management**: Supports auto-overwrite beyond 100 users (circular buffer)
- **Persistent Storage** via plain text data files
- **Modular Architecture** with 10+ headers (e.g., validation, access control, file handling)
- ~**1000+ lines of code**, demonstrating robust C++ fundamentals
- Menu-driven interface using clean and organized code logic

## 📂 Structure

├── headers.hpp
├── validation.hpp / .cpp
├── access_control.hpp / .cpp
├── file_handling.hpp / .cpp
├── main.cpp
├── users.txt
├── admins.txt
└── ...

markdown
复制
编辑

## 🛠️ Technologies

- Language: **C++ (C++11 and above)**
- No external libraries required
- Built for **Windows CLI**

## 🧪 How to Run

1. Clone the repository or download as ZIP.
2. Compile using your preferred compiler (e.g. `g++ main.cpp -o dms` or use an IDE like Code::Blocks).
3. Ensure `users.txt` and `admins.txt` are present in the directory.
4. Run the executable from a terminal.

```bash
g++ main.cpp -o dms
./dms
```

✨ Notes
- This project was initially created as an academic and exploratory system with minimal UI.
- While not based on modern OOP patterns, it is highly modular and extensible.
- Good for those learning file handling, structured input validation, and menu-based logic in C++
- Let me know if you want a version that also includes screenshots (if any), sample output, or a cleaner intro for recruiters specifically!
