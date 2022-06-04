CXX=g++
# CXXFLAGS=-std=c++20 -g -Wall -Werror -I./include
CXXFLAGS=-std=c++20 -g -I./include

all: main play test

main: out/main

play: out/play

test: out/test

# executables

out/main: out/main.o out/document.o out/query.o out/vector_space_model.o out/word_processing.o
	$(CXX) $(CXXFLAGS) out/main.o out/document.o out/query.o out/vector_space_model.o out/word_processing.o -o out/main

out/play: out/play.o out/document.o out/query.o out/vector_space_model.o out/word_processing.o
	$(CXX) $(CXXFLAGS) out/main.o out/document.o out/query.o out/vector_space_model.o out/word_processing.o -o out/play

out/test: out/test.o out/document.o out/query.o out/vector_space_model.o out/word_processing.o
	$(CXX) $(CXXFLAGS) out/test.o out/document.o out/query.o out/vector_space_model.o out/word_processing.o -o out/test

# headers

include/vector_space_model.hpp: include/document.hpp include/query.hpp

# sources

src/main.cpp: include/vector_space_model.hpp

src/play.cpp: include/vector_space_model.hpp

src/test.cpp: include/vector_space_model.hpp


src/document.cpp: include/document.hpp include/util.hpp include/word_processing.hpp

src/query.cpp: include/query.hpp include/word_processing.hpp

src/vector_space_model.cpp: include/vector_space_model.hpp include/util.hpp include/word_processing.hpp

src/word_processing.cpp: include/word_processing.hpp

# objects

out/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o out/main.o

out/play.o: src/play.cpp
	$(CXX) $(CXXFLAGS) -c src/play.cpp -o out/play.o

out/test.o: src/test.cpp
	$(CXX) $(CXXFLAGS) -c src/test.cpp -o out/test.o


out/document.o: src/document.cpp
	$(CXX) $(CXXFLAGS) -c src/document.cpp -o out/document.o

out/query.o: src/query.cpp
	$(CXX) $(CXXFLAGS) -c src/query.cpp -o out/query.o

out/vector_space_model.o: src/vector_space_model.cpp
	$(CXX) $(CXXFLAGS) -c src/vector_space_model.cpp -o out/vector_space_model.o

out/word_processing.o: src/word_processing.cpp
	$(CXX) $(CXXFLAGS) -c src/word_processing.cpp -o out/word_processing.o


clean:
	rm -f out/main out/test out/*.o