# Lexical_analyzer
## what it is
a dfa-based simple lexical analyzer.</br>
by editing whichDFA.txt, you can choose which DFA, and tokens you are going to use.</br>
by editing ~.dfa, you can define dfa</br>
by editing ~.token, you can define token.</br>

### whichDFA.txt

	<dfa file to use>
	<token file to use>

### .dfa files

	<# of nodes>
	<tokens of each nodes>
	repeat #nodes times:
		  <#comment> <# of edges on i-th node>
		  repeat #edges times:
			  <if next token is this,> <then go to this node>
a simple example of this is like:</br>

	4
	0
	0
	5
	5
	0번 3
	0 3
	- 1
	1-9 2
	1번 1
	1-9 2
	2번 1
	0-9 2
	3번 0
It will make a dfa for signed integer,</br>
where tokennumber 0 == INVALID</br>
and tokennumber 5 == INTEGER_VALUE</br>
    
### .token files
token files are only for printing names of token, on case that token number is given.

	<tokenNumber> <tokenName>

---
## how to run
./Lexical_Analyzer [option:<input_file_name>] [option:<output_file_name>]</br>
you can try console mode without typing any arguments.

