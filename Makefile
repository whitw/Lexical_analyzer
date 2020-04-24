CXXFLAGS += -g -pg
CXXFLAGS += -fsanitize=address,leak,undefined
CXXFLAGS += -std=c++17
BFLAGS += -v

.PHONY: all clean

all: Lexical_Analyzer

Lexical_Analyzer: main.cpp Finite_Automata.cpp token.cpp Lexical_Analyzer.cpp lexeme.cpp Node.cpp Finite_Automata.h lexeme.h Lexical_Analyzer.h Node.h token.h
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	rm -rf Lexical_Analyzer

run:
	./Lexical_Analyzer