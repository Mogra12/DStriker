````markdown
# DStriker 🔍📂

A simple directory brute-force tool developed in C++ for educational purposes and authorized web application security testing.

---

## ⚙️ Features

- Sends HTTP requests using a wordlist.
- Terminal color support (Linux and Windows).
- Counts and displays the number of requests made.
- Accepts URL and wordlist via command-line arguments.

---

## 🖥️ How to Use

### Compilation

Linux:
```bash
g++ dstriker.cpp -lcurl -o dstriker -std=c++17 -pthread
````

Windows (using MinGW):

```bash
g++ dstriker.cpp -lcurl -o dstriker.exe -std=c++17
```

---

### Execution

```bash
./dstriker -u http://example.com -wl wordlist.txt
```

Parameters:

* `-u`: Target URL.
* `-wl`: Path to the wordlist file.

---

## 🧠 Example

```bash
./dstriker -u http://localhost -wl /usr/share/wordlists/dirb/common.txt
```

---

## 💡 Future Improvements

* Filter by HTTP status code.
* Save results to a file.
* Proxy support.
* Multi-threaded execution.
* Support for custom headers.

---

## ⚠️ Legal Disclaimer

This project is intended **for educational use and authorized security testing only**.
**Do not use this tool on systems for which you do not have explicit permission.**

---

## 👨‍💻 Author

* **Santto0x1** – [github.com/Mogra12](https://github.com/Mogra12)
