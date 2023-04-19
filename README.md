This repository contains an example of the implementation and use of expression templates.
In particular, it contains an example *dual number* class, similar to what might be used in an automatic differentiation library.

To build the quarto document, use the GNUmakefile in this directory.
To build the source code, `cd` into the appropriate *build* directory and use the CMake build.

To build the quarto document you will need to have the `include-code-files` filter installed:

    quarto add quarto-ext/include-code-files
