# lisplike
## v0.1
*"LISP for the rest of us"*

Because, you know, you wanted another LISP-like language, right???

Requires
=
C++14, Flex, Bison 3.0.4, Boost Filesystem

HTML generation requires xsltproc.

Building
=
To build/install the executable, run `make` and `make install`. 

To generate an HTML representation of the grammar, run `make html`. If you have a weird 'share' directory for Bison (i.e. not /usr/share/bison), you can set that using `make html BISON_SHARE_DIR=/path/to/my/share/dir`.

Using
=
Program usage to come. A rudimentary build script is provided for your compiling pleasure. Usage for that is also to come.

Roadmap
=
There are a number of things that need to be done. Here is a list of the stuff:
* ~~Build tools that allow us to type something along the lines of `llbuild file1.ll file2.ll file3.ll`, and result in the C++ compiler being called (with appropriate flags) and a binary to be generated.~~
* ~~Imports, indicating where to import something from. This is an analogue to the C++ #include. Headers are covered in the next bullet point.~~ COMPLETE
* ~~Header generation. This either need to happen (a) by default or (b) by adding an option for it to be generated at compile-time.~~ (mostly) COMPLETE
* Obligatory support for Window$. I don't have immediate access to a Windows box, so I can't verify anything I'm writing is correct.
* Moving over to some autobuild system. If we want Windows support, it will likely have to be CMake.
* Move the code generation to a more friendly design pattern, rather than being hard-coded to C++.
* Syntactic analysis before generating the C++ code. Catch things like re-declarations, immutable assignment, invalid operands (lexer doesn't catch invalid boolean operators), etc.
* Better examples (i.e. more than just a factorial)
* Class/struct generation?

License
=
BSD 3-clause license. See the LICENSE file for the full license.
