This repository contains an example of the implementation and use of expression
templates. The file `overload.cpp` contains the original code, which does not
use expression templates. The file `overload2.cpp` contains a version of the
same facility implemented using expression templates.

`overload3.cpp` is a failed experiment to produce a version that doesn't use
`operator()` to access struct elements, but instead uses the function members
`real()` and `dual()`. I have not yet been able to get this to work.

