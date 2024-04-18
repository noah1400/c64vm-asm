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

Please note that **c64vm-asm** is still a work in progress.

## Compile

To compile the **c64vm-asm** project, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the repository directory.
3. Run the following command to compile the project:

    ```sh
    make
    ```

## Usage

The current usage involves running the compiled `c64asm` executable, providing it with input filenames as arguments:

```sh
./c64asm input.c64asm input2.c64asm input3.c64asm
```
## Assembly language
```asm
DEF loop_start ; export label for usage in other files
REF sub_routine ; import label defined and exported using 'DEF' in other file

:loop_start

ADDI R3, $1 ; Add 1 to register r3 ( r3 = r3 + 1 )

CMP R3, #50 ; Compare R3 with 0x50
JNE loop_start ; Jump if not equal

JMP sub_routine ; Jump to external sub routine

HLT ; HALT all operations
```

Since the project is a work in progress the syntax usage example might not be up to date. 

## License

This project is licensed under the [MIT License](LICENSE), allowing you to use, modify, and distribute the software according to the terms outlined in the license.

---

**Disclaimer:** **c64vm-asm** is actively being developed, and as a result, the information provided here might evolve over time.
