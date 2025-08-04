
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
  "postCreateCommand": "sudo apt-get update && sudo apt-get install -y gdb",
  "features": {},
  "runArgs": ["--rm"] //delete container after close vscode
}
```

---

### 2. 🐋 .devcontainer/Dockerfile

```Dockerfile
FROM debian:trixie

RUN apt-get update && apt-get install -y \
    gcc \
    gdb \
    vim \
    git \
    sudo \
    tzdata \
    && apt-get clean

# Set timezone environment variable
ENV TZ=America/Sao_Paulo

# Configure timezone non-interactively
RUN ln -sf /usr/share/zoneinfo/$TZ /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata

# Create user vscode with passwordless sudo
RUN useradd -m vscode && echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Set working directory
WORKDIR /workspace

# Use non-root user
USER vscode
```

---

### 3. 🧪 Example setup_test.c

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <time.h>

int main() {
    struct sysinfo info;
    struct statvfs stat;
    struct utsname osinfo;

    // Get current date/time
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char datetime_str[100];
    strftime(datetime_str, sizeof(datetime_str), "%Y-%m-%d %H:%M:%S", local);

    printf("*************************\n");
    printf("*  W  E  L  C  O  M  E  *\n");
    printf("*  %s  *\n", datetime_str);
    printf("*************************\n\n");

    
    

    printf("=========================\n");
    printf("= S Y S T E M   I N F O =\n");
    printf("=========================\n");

    if (uname(&osinfo) == 0) {
        printf("System Name: %s\n", osinfo.sysname);
        printf("Node Name: %s\n", osinfo.nodename);
        printf("Release: %s\n", osinfo.release);
        printf("Version: %s\n", osinfo.version);
        printf("Machine: %s\n", osinfo.machine);
    } else {
        perror("uname");
        return 1;
    }

    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs < 1) {
        perror("sysconf");
        return 1;
    }
    printf("Number of available processors: %ld\n", nprocs);

    if (sysinfo(&info) == 0) {
        printf("Total RAM: %lu MB\n", info.totalram / 1024 / 1024);
        printf("Free RAM: %lu MB\n", info.freeram / 1024 / 1024);
        printf("Available RAM: %lu MB\n", info.freeram / 1024 / 1024);
    } else {
        perror("sysinfo");
        return 1;
    }

    if (statvfs("/", &stat) == 0) {
        unsigned long total = stat.f_blocks * stat.f_frsize;
        unsigned long free = stat.f_bfree * stat.f_frsize;
        unsigned long available = stat.f_bavail * stat.f_frsize;
        printf("Total disk space: %lu MB\n", total / 1024 / 1024);
        printf("Free disk space: %lu MB\n", free / 1024 / 1024);
        printf("Available disk space: %lu MB\n", available / 1024 / 1024);
    } else {
        perror("statvfs");
        return 1;
    }
    printf("=========================\n");
    return 0;
}
```

---

### 4. 🚀 Using the DevContainer

1. Open your project folder in **VS Code**.
2. Press `F1` → `Dev Containers: Open Folder in Container`.
3. Open a terminal inside the container and compile:

```bash
Compile: gcc src/setup_test.c -o build/setup_test
Run: ./build/setup_test 
```

---

### ✅ Installed VS Code Extensions

- `ms-vscode.cpptools` — IntelliSense and debugging
- `jeff-hykin.better-c-syntax` — Enhanced C syntax highlighting
- `usernamehw.errorlens` — Inline error/warning display