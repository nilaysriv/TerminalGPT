# Terminal-GPT

**Terminal-GPT** is a high-performance, C++ based terminal agent that uses local LLMs (via Ollama) to translate natural language into executable Linux commands. It allows you to control your shell using plain English while keeping all processing local or on your own hardware.

## Features

* **Local Model Integration:** Connects to any Ollama-compatible model (optimized for `Qwen2.5-Coder`).
* **Safety First:** Commands are proposed and highlighted; execution only happens after manual user confirmation (`y/n`).
* **Clean Parsing:** Automatically strips AI-generated markdown backticks and conversational filler.
* **Modern Tech Stack:** Utilizes `libcurl` for robust HTTP communication and `nlohmann/json` for modern JSON manipulation.

## Tech Stack

* **Language:** C++17
* **Backend:** [Ollama](https://ollama.com/)
* **Libraries:** * `libcurl`: For REST API communication.
* `nlohmann/json`: For parsing LLM responses.


* **OS:** Linux (Fedora/Ubuntu/Arch)

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/nilaysriv/TerminalGPT
cd TerminalGPT

```

### 2. Prerequisites

Ensure you have the necessary development headers installed:

```bash
# Fedora/RHEL
sudo dnf install libcurl-devel json-devel gcc-c++

# Ubuntu/Debian
sudo apt install libcurl4-openssl-dev nlohmann-json3-dev build-essential

```

### 3. Configure Your Server

Update the `server_url` in `terminalgpt.cpp` with your server's IP address:

```cpp
std::string server_url = "http://YOUR_SERVER_IP:11434/api/generate";

```

### 4. Compilation

Using the Makefile:

```bash
make

```

### 5. Global System Access

To access the agent from any directory without typing `./`, move the binary to your system's bin folder:

```bash
sudo mv terminalgpt /usr/local/bin/

```

Now you can start the agent from any terminal window simply by typing `terminalgpt`.

---

## Usage

1. **Run the agent:**
```bash
terminalgpt

```


2. **Enter a task:**
`[Nilay] > find all py files and count the lines`

3. **Review & Execute:**
`🤖 Proposed: find . -name "*.py" | xargs wc -l`
`Confirm execution? (y/n): y`

---

## Screenshots
https://github.com/nilaysriv/TerminalGPT/blob/main/Screenshots/Screenshot_20251229_122103-1.png
