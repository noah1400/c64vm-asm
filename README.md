# c64vm-asm - Assembler for the c64vm Custom Assembly Language

Welcome to the **c64vm-asm** project! This repository houses the assembler designed specifically for the custom assembly language used with the **c64vm** project. This tool aims to facilitate the conversion of human-readable assembly code into binary machine code that can be executed by the virtual machine.

## Table of Contents

- [Introduction](#introduction)
- [Compile](#compile)
- [Usage](#usage)
- [Note](#note)
- [License](#license)

## Introduction

The **c64vm-asm** project serves as a vital companion to the **c64vm** virtual machine project. This assembler is designed to take assembly code written in the custom assembly language and convert it into the binary format compatible with the **c64vm** environment. As part of the development process, this project is undergoing continuous refinement and improvement.

Please note that **c64vm-asm** is still a work in progress. While it currently focuses on tokenizing the assembly code and checking for syntax errors, the implementation of code generation is not yet available.

## Compile

To compile the **c64vm-asm** project, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the repository directory.
3. Run the following command to compile the project:

    ```sh
    gcc -o c64asm c64asm.c c64token.c c64tokenizer.c c64utils.c -Iinclude -std=c99 -Wall -Wextra -Wpedantic
    ```

## Usage

While the project is still under active development, the current usage involves running the compiled `c64asm` executable, providing it with input and output filenames as arguments:

```sh
./c64asm.exe input.c64asm output.c64bin
```

## Note

Please keep in mind that **c64vm-asm** is currently a work in progress. While the tool is capable of tokenizing assembly code and checking for syntax errors, the critical code generation phase has not been implemented yet.

## License

This project is licensed under the [MIT License](LICENSE), allowing you to use, modify, and distribute the software according to the terms outlined in the license.

---

**Disclaimer:** **c64vm-asm** is actively being developed, and as a result, the information provided here might evolve over time.
