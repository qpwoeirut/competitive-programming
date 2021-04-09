# Competitive Programming

This is Stanley Zhong's (a.k.a. qpwoeirut) repository for all things competitive programming.

# Some notes for myself which you may or may not find helpful

Install g++ with HomeBrew.
My include directory is currently /usr/local/Cellar/gcc/10.2.0/include/c++/10.2.0.
You can find the include directory by doing `g++-10 -v file.cpp` and checking the directories listed after `#include <...> search starts here`.

## Precompiling bits/stdc++.h

[GCC Documentation](https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_headers.html)

### The `g++` command on Macs is a SCAM
On Macs, the backend of `g++` is actually Clang, so you'll need to install the actual GCC for this.
Once you install it (probably through Homebrew), the command should be something like `g++-x`, where x is some number.
For example I'm using `g++-10`.

Inside the `bits` folder, run the command you normally use to compile files, but with an extra flag: `-x c++-header`.
Also don't include the `-lm` flag since apparently that breaks things. Not sure why but there's probably an explanation elsewhere on the internet.
This should generate a `stdc++.h.gch` file.

To use the precompiled file, just compile normally.
*Note that the compiler flags must be the same as the ones used to precompiled stdc++.h for this to work.*

