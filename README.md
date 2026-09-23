# simple-shell

A minimal Unix shell written in C.

## Features

- Interactive prompt
- Runs external programs using `fork`, `execvp` and `wait`
- Built-in commands: `cd`, `exit`
- Handles empty input and unknown commands

## Build

```
gcc -Wall main.c -o shell
```

## Run

```
./shell
```

## Example

```
< ls
main.c  README.md
< cd ..
< pwd
/home/djole
< asdf
asdf: command not found
< exit
```

## How it works

The shell reads a line, strips the trailing newline, and splits it into
arguments with `strtok`.

Built-in commands run inside the shell process itself. `cd` has to be a
built-in because every process has its own working directory — a child
process would only change its own copy and then exit, leaving the parent
where it was.

Any other command is run in a child process created with `fork`. The child
replaces itself with the requested program through `execvp`, while the parent
blocks in `wait` until the child finishes.

## Roadmap

- [ ] Output redirection (`>`, `<`)
- [ ] Pipes (`|`)
- [ ] Signal handling (Ctrl+C should not kill the shell)