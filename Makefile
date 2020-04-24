CXXFLAGS += -g -pg
CXXFLAGS += -fsanitize=address,leak,undefined
CXXFLAGS += -std=c++17
BFLAGS += -v

all: Lexical_Analyzer

Lexical_Analyzer: main.cpp Finite_Automata.cpp token.cpp Lexical_Analyzer.cpp lexeme.cpp Node.cpp
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	rm -rf Lexical_Analyzer