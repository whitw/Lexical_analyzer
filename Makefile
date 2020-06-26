CXXFLAGS += -std=c++17
OBJFLAGS += -c -W -Wall -O2

.PHONY: all test clean testClean run

all: lexical_analyzer

lexical_analyzer: main.o finite_automata.o token.o lexical_analyzer.o lexeme.o node.o
	${CXX} ${CXXFLAGS} -o $@ $^

main.o: main.cpp
	${CXX} ${OBJFLAGS} $^
finite_automata.o: finite_automata.cpp
	${CXX} ${OBJFLAGS} $^
token.o: token.cpp
	${CXX} ${OBJFLAGS} $^
lexical_analyzer.o: lexical_analyzer.cpp
	${CXX} ${OBJFLAGS} $^
lexeme.o: lexeme.cpp
	${CXX} ${OBJFLAGS} $^
node.o: node.cpp
	${CXX} ${OBJFLAGS} $^

clean:
	rm -rf lexical_analyzer
	rm -rf *.o
run:
	./lexical_analyzer

test: lexical_analyzer
	for f in Testcase/*; do echo $$f ; ./lexical_analyzer $$f; done

testClean:
	rm -rf Testcase/*.out
