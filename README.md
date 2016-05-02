# joos-2-compiler

This compiler project focuses mainly on compiler architecture and the usage of high-level language features in compiler development; in order to develop a maintainable, extendable compiler.

As for performence, this is clearly a secondary goal, however this will be looked into, once a fully complete joos2 compiler has been developed.

The compiler is loosely based of the OCaml compiler developed as a part of the dOvs project at Aarhus University anno 2012.

## Technologies used
This project tries to implement a joos2 compiler, in C++11, using;

1 boost::spirit, for lexing and parsing;

* http://boost-spirit.com/

2 Open Type Switching, for tree processing;

* https://parasol.tamu.edu/~yuriys/pm/
* http://www.stroustrup.com/OOPSLA-typeswitch-draft.pdf

3 Option Type, rather than null;

* https://github.com/simonask/simonask.github.com/blob/master/maybe.markdown
* https://github.com/simonask/reflect/blob/master/base/maybe.hpp
