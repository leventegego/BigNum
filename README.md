
# BigNum tool

This project implements a big number class, that can represent
arbitrarily large integers. This is used to run a read-eval-print loop,
interpreting algebraic expressions in reverse polish notation.

## How to build

1. Set a 64-bit compatible c++ compiler as COMP in Makefile
2. run make

## Usage

This program has been designed such that it is easy to use as a command line tool,
e.g. `echo "11 12 +" | bin/program.exe` works as exptected. Besides, you can use
it on its own as well.

- The program waits for expressions on the standard input and prints the
evaluated result to the standard output in a loop.

- Each expression should be in a separate line. The program stops, when an
end-of-file is reached.

- On invalid input, an error message is printed, but the remaining expressions
are still evaluated.






