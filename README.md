# Lexical_analyzer
## what it is
a dfa-based simple lexical analyzer.

by editing whichDFA.txt, you can choose which DFA, and tokens you are going to use.

by editing ~.dfa, you can define dfa

by editing ~.token, you can define token.

### whichDFA.txt
<dfa file to use>
  
<nfa file to use>

### .dfa files
<# of nodes>

<tokens of each nodes>
  
repeat #nodes times:

  <#comment> <# of edges on i-th node>

  repeat #edges times:

    <if next token is this,> <then go to this node>
    
### .token files
token files are only for printing names of token, on case that token number is given.

<tokenNumber> <tokenName>

---
## how to run
./Lexical_Analyzer [option:<input_file_name>] [option:<output_file_name>]

you can try console mode without typing any arguments.

