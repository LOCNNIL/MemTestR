## MemTestr - Memory Allocation and Deallocation Tester

This is a simple C program that is done to test memory allocation and dealocation on a system.

It can be useful do diagnostic problems such as the [fixed by this kernel patch](https://lkml.org/lkml/2020/5/19/886/) where the hyper-V of WSL2 doesn't reported the free of memory.


## Compiling

As this **until now** is a simple `C` file we can compile the program just by running:

```bash
gcc memo_usage.c -o memtestr -Wall
```

## Use Memory tool

This utility is designed to be a tester tool to memory usage, it works like that: 

```bash
./memtestr <amount-of-memory> <unit> <interval>
```

In the example bellow:

```bash
./memtestr 10 MB 15
```

The mem usage tool will operate this way:

1 - It will alloc `10MB` of memory
2 - Sleep for `15` seconds
3 - `free` the 10 MB of memory 
4 - Sleep for `15` seconds 
5 - Start all over until you press CTRL+C

The possible units are: 

- `B` -> Bytes
- `KB` -> Kilobytes
- `MB` -> Megabytes
- `GB` -> Gigabytes

The default values are `5 KB` under a interval of `10` (s)

