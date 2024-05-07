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
./c64asm input2.c64asm input.c64asm
```
The program will initiate execution starting from the first line of the last provided file (`input.c64asm`).

## Assembly language

**input.c64asm**
```asm
REF SQRT_SUBROUTINE

    LDI r1, $119699        ; Load the number to check for primality

    TF r3, r1             ; Copy r1 to r3 to keep the original number intact
    CMPI r1, $2           ; Compare the number with 2

    JLT NOT_PRIME         ; Jump to NOT_PRIME if the number is less than 2
    JEQ PRIME             ; Jump to PRIME if the number is exactly 2

:CHECK_EVEN
    TF r4, r3             ; Copy r3 to r4
    MODI r4, $2           ; r4 = r4 % 2
    JEQ NOT_PRIME         ; If even, it's not prime

    TF r1, r3             ; Copy the number to r1 before calling square root subroutine
    BRA SQRT_SUBROUTINE   ; Branch to the square root subroutine
    TF r4, r1             ; Copy the result back to r4 to use as limit in the loop

    LDI r5, $3            ; Start divisor from 3

:LOOP
    CMP r5, r4            ; Compare divisor with sqrt(n)
    JGT PRIME             ; If divisor > sqrt(n), it is prime

    TF r6, r3             ; Copy the number to r6 for modulus operation
    MOD r6, r5            ; r6 = r6 % r5
    JEQ NOT_PRIME         ; If divisible, not prime

    ADDI r5, $2           ; Increment divisor by 2 (check only odd numbers)
    JMP LOOP              ; Repeat loop

:PRIME
    LDI r2, $1            ; Mark as prime
    JMP END               ; Go to end

:NOT_PRIME
    LDI r2, $0            ; Mark as not prime

:END
    HLT                   ; Halt the program

```

**input2.c64asm**
```asm
DEF SQRT_SUBROUTINE

:SQRT_SUBROUTINE
    PUSH R2           ; Save R2 on stack
    PUSH R3           ; Save R3 on stack
    PUSH R4           ; Save R4 on stack

    TF R2, R1         ; Copy R1 to R2, initial guess (assume starting guess is the number itself)
    SHRI R2, $1        ; R2 = R2 / 2 (half the number as initial guess)

    LDI r4, $20    ; Number of iterations, adjust based on required precision

:LOOP
    TF R3, R1         ; Copy R1 to R3 for division
    DIV R3, R2        ; R3 = R1 / R2
    ADD R2, R3        ; R2 = R2 + R3
    SHRI R2, $1        ; R2 = R2 / 2, new guess

    SUBI R4, $1        ; Decrement R4
    CMPI R4, $0        ; Check if R4 is zero
    JNE LOOP          ; If R4 is not zero, loop again

    TF R1, R2         ; Copy the final guess back to R1

    POP R4            ; Restore R4 from stack
    POP R3            ; Restore R3 from stack
    POP R2            ; Restore R2 from stack

    RET               ; Return from subroutine

```

Since the project is a work in progress the syntax usage example might not be up to date. 

## License

This project is licensed under the [MIT License](LICENSE), allowing you to use, modify, and distribute the software according to the terms outlined in the license.

---

**Disclaimer:** **c64vm-asm** is actively being developed, and as a result, the information provided here might evolve over time.
