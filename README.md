lisplike
=
*"LISP for the rest of us"*

Because, you know, you wanted another LISP-like language, right???

Requires
=
C++14, Flex, Bison 3.0.4

HTML generation requires xsltproc.

Building
=
To build the executable, run `make`.

To generate an HTML representation of the grammar, run `make genhtml`. If you have a weird 'share' directory for Bison (i.e. not /usr/share/bison), you can set that using `make genhtml BISON_SHARE_DIR=/path/to/my/share/dir`.

License
=
For now, I am retaining all rights to this project until I get around to choosing a license. It will be more permissive soon, I just have to get the code in a more stable place.