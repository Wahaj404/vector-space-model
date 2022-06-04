# brief

Information Retrieval (CS4051) assignment #01, Spring 2022

Implements a vector space model capable of serving free text queries on a free-text corpus.

# compilation

**requires a compiler that supports C++20 or higher**

`make test` to build tests

`make main` to build main

`make` to build both

# execution

Both the main executable and the test suite take the source dataset as command line arguments.
For example, `out/main Abstracts/*.txt` would run the program with the entire Abstracts dataset.

The main executable prompts the user for a free text query. To terminate, enter EOF (Ctrl + D on most systems).

See Gold Query-VSM.txt for query examples.

# directory structure

| Folder    | Purpose                                                           |
| --------- | ----------------------------------------------------------------- |
| .vscode   | vscode debugging configurations I used while developing           |
| Abstracts | the main free text dataset this program was built around          |
| out       | compilation output - executables and object files (\*.o)          |
| include   | header files (_h or _.hpp) - my own as well as external libraries |
| src       | the implementation source files (\*.cpp) for the program          |

| File                               | Purpose                                                                                                                                            |
| ---------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------- |
| .clang-format                      | my custom c++ formatting rules                                                                                                                     |
| CS4051- IR-A2-Spring 2022.pdf      | the assignment problem statement                                                                                                                   |
| Gold Query-VSM.txt                 | set of example queries with expected outputs (most of expected output is wrong - see test.cpp)                                                     |
| Makefile                           | compilation rules for the program                                                                                                                  |
| Stopword-List.txt                  | list of stopwords to be excluded when conducting information retrieval                                                                             |
| random numerically named text file | the serialization file of the vector space model, the name of the file is a collective hash of the filenames from the corpus it was generated from |

# external dependencies

uses the [Oleander Stemming Library](https://github.com/OleanderSoftware/OleanderStemmingLibrary) for stemming
