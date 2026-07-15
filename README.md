# simpleC — Simple Calculator
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
A lightweight terminal calculator for quick everyday calculations.  
Supports arithmetic expressions, parentheses, percentages, and unary minus.

## Features

- **Basic arithmetic**: addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`)
- **Operator precedence**: `2+3*4` equals `14`, not `20`
- **Parentheses**: `(2+3)*4` for grouping expressions
- **Unary minus**: `-5+3` for negative numbers at the start of expressions
- **Percentages**: `100+10%` calculates 10% of 100 and adds it, giving `110`
- **REPL mode**: interactive prompt for continuous calculations
- **Error handling**: clear messages for division by zero and syntax errors

## Build from Source

### Requirements

- g++ (GCC) with C++17 support
- make

### Compilation

Clone the repository and build with make:

`git clone https://github.com/vladik50/simpleC.git`  
`cd simpleC`  
`make`

Or compile manually:

`g++ -std=c++17 -O2 -o simpleC simpleC.cpp`

### Install (optional)

`sudo make install`

This copies `simpleC` to `/usr/local/bin`. To uninstall:

`sudo make uninstall`

## Usage

Launch the calculator:

`./simpleC`

You will see the `>>` prompt. Type an expression and press Enter.

### Examples

**Basic arithmetic:**

`>> 2+2`  
`4`  
`>> 10-3`  
`7`  
`>> 6*7`  
`42`  
`>> 15/3`  
`5`

**Operator precedence:**

`>> 2+3*4`  
`14`  
`>> 10-8/2`  
`6`

**Parentheses:**

`>> (2+3)*4`  
`20`  
`>> (10-5)*(2+3)`  
`25`

**Unary minus:**

`>> -5+3`  
`-2`  
`>> 10+-3`  
`7`  
`>> 2*-4`  
`-8`

**Percentages:**

`>> 100+10%`  
`110`  
`>> 200-15%`  
`170`  
`>> 50+20%-10%`  
`54`

**Error handling:**

`>> 5/0`  
`Error: division by zero`  
`>> (2+3`  
`Error: expected ')'`  
`>> hello`  
`Error: expected a number or '('`

**Exiting:**

`>> exit`  
`Goodbye!`

You can also use `quit` to exit.

## License

GNU GPL v3.0 or later. See LICENSE for full text.
