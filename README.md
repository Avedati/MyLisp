# My Lisp

My lisp is a hobby project of mine. It is a minimal, but working and expandable lisp interpreter. It is written in C11.

## Getting Started

To play with this project and test it out for yourself, you will need a c compiler capable of compiling c11. I recommend gcc.

Clone this repository and run:
```
make
./bin/my_lisp <file>
```

## How It Works

There are two main parts to this interpreter, lexing and parsing.

The first stage, lexing, is dividing the user's input in tokens. Lexing is also known as tokenization.
For example, for the input
```lisp
( print "hello, world!" )
```
would be tokenized into
```
"(", "print", "\"hello, world!\", ")"
```

The second stage, parsing, is forming the tokens into meaningful statements. MyLisp uses a stack to carry the current state of the program's execution.
The lisp language (as far as I am aware) is written in Polish notation. Therefore, if MyLisp sees a function, MyLisp can push numbers, strings, and variables onto our stack, and
then pop them off of the stack after there are enough arguments to call a function.
For example, for the tokens
```
"(", "+", "1", "2", ")"
```
after we see the "+" function, we will accept the numbers "1" and "2" as arguments, and then add them and push the result onto the stack.
