### Status: Work In Progress
Utilix
======

A set of POSIX-inspired utilities

The idea is to rethink how these utilities work and how they can be made to
work better.

*N.B. These are not POSIX-compliant and are not intended to be*
*This is a Work In Progress and is not guaranteed to be bug-free*
These are intended to be a replacement base system for any POSIX-based system
but will not be compliant with the POSIX standard by default. Wrappers will
be considered, but I won't be writing any.

Utilities needed
----------------
* ~~cat~~ 
* ~~ls~~
* ~~new (Make new file)~~
* ~~mkdir~~
* ~~dd~~
* ~~rm~~
* ~~rmdir~~
* ~~mv~~
* stat (print one-line status of file)
* cut (Get a specific token)
* df
* du
* sort (sort strings; punctution, numbers, letters)
* column
* match (search for exact string)
* ~~sponge (write all of stdin to file; inspired by moreutils)~~
* append (like sponge except appending)
