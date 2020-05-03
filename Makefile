CXXFLAGS += -std=c++17
OBJFLAGS += -c

.PHONY: all clean

all: Lexical_Analyzer

Lexical_Analyzer: main.o Finite_Automata.o token.o Lexical_Analyzer.o lexeme.o Node.o
	${CXX} ${CXXFLAGS} -o $@ $^

main.o: main.cpp
	${CXX} ${OBJFLAGS} $^
Finite_Automata.o: Finite_Automata.cpp
	${CXX} ${OBJFLAGS} $^
token.o: token.cpp
	${CXX} ${OBJFLAGS} $^
Lexical_Analyzer.o: Lexical_Analyzer.cpp
	${CXX} ${OBJFLAGS} $^
lexeme.o: lexeme.cpp
	${CXX} ${OBJFLAGS} $^
Node.o: Node.cpp
	${CXX} ${OBJFLAGS} $^

clean:
	rm -rf Lexical_Analyzer
	rm -rf *.o
run:
	./Lexical_Analyzer

test:
	for f in Testcase/*; do echo $$f ; ./Lexical_Analyzer $$f; done

testClean:
	rm -rf Testcase/*.out
