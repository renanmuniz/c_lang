
## C Programming language study repository

This guide will help you set up the local environment using **DevContainer** in **Visual Studio Code** to write and run C programs using **GCC**, with a minimal and focused environment.

---

### 📁 Project Structure

```
C_LANG/
├── .devcontainer/
│ ├── devcontainer.json # Dev container configuration for VS Code
│ └── dockerfile # Dockerfile to build the dev container
├── build/ # Directory for test-related build outputs
├── src/ # Directory for code source files and folders
├── .gitignore # Specifies intentionally untracked files to ignore
├── README.md # Project documentation
```

---

### 1. ⚙️ .devcontainer/devcontainer.json

```json
{
  "name": "C DevContainer",
  "build": {
    "dockerfile": "Dockerfile"
  },
  "customizations": {
    "vscode": {
      "extensions": [
        "ms-vscode.cpptools",
        "jeff-hykin.better-c-syntax",
        "usernamehw.errorlens"
      ],
      "settings": {
        "terminal.integrated.defaultProfile.linux": "bash"
      }
    }
  },
  "remoteUser": "vscode",
  "postCreateCommand": "sudo apt-get update && sudo apt-get install -y gdb"
}
```

---

### 2. 🐋 .devcontainer/Dockerfile

```Dockerfile
FROM debian:trixie

# Install GCC, GDB, and basic tools
RUN apt-get update && apt-get install -y \
    gcc \
    gdb \
    vim \
    git \
    sudo \
    && apt-get clean

# Create user vscode with passwordless sudo
RUN useradd -m vscode && echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Set working directory
WORKDIR /workspace

# Switch to non-root user
USER vscode
```

---

### 3. 🧪 Example hello.c

```c
#include <stdio.h>

int main() {
    printf("Hello from Debian Trixie DevContainer!\n");
    return 0;
}
```

---

### 4. 🚀 Using the DevContainer

1. Open your project folder in **VS Code**.
2. Press `F1` → `Dev Containers: Open Folder in Container`.
3. Open a terminal inside the container and compile:

```bash
Compile: gcc test.c -o build/test
Run./build/test 
```

---

### ✅ Installed VS Code Extensions

- `ms-vscode.cpptools` — IntelliSense and debugging
- `jeff-hykin.better-c-syntax` — Enhanced C syntax highlighting
- `usernamehw.errorlens` — Inline error/warning display