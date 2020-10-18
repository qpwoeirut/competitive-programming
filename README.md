# Compritive Programming

This is Stanley Zhong's (a.k.a. qpwoeirut) repository for all things competitive programming.


# Some notes for myself which you may or may not find helpful

## To include bits/stdc++ on Mac

Check if the compiler has `/usr/local/include` in its path.
For g++ do `g++ -v file.cpp` and check the directories listed after `#include <...> search starts here:`.
If it doesn't then go find some other thing and figure that out.

Go to /usr/local/include and create a folder called bits.
This can be done with terminal (cd and mkdir) or with Finder (cmd+shift+g, type in "/usr/local/include")

Download the stdc++.h file from GitHub or some other place. Some headers may be deprecated so those might need to be commented out.

Test to make sure that the bits/stdc++.h file can be found by writing a program that includes it and then running that program.


## Precompiling bits/stdc++.h

[GCC Documentation](https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_headers.html)


### The `g++` command on Macs is a SCAM
Note that on Macs, the backend of `g++` is actually Clang, so you'll need to install the actual GCC for this.
Once you install it (probably through Homebrew), the command should be something like `g++-x`, where x is some number.
For example I'm using `g++-10`.

Inside the `bits` folder, run the command you normally use to compile files, but with an extra flag: `-x c++-header`.
This should generate a `stdc++.h.gch` file.

To use the precompiled file, just compile normally.
*Note that the compiler flags must be the same as the ones used to precompiled stdc++.h for this to work.*
