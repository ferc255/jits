all: recalc libgccjit ast libjitparser nfloatbug llvm

nfloatbug: nfloatbug.c
	gcc $< -ljit -lpthread -lm -ldl -o $@

recalc: recalc.c syn_tables.h my_yylex.h lex_automaton.h executions.h experiment.h
	$(CC) $< -lm -o $@

libgccjit: libgccjit.c syn_tables.h my_yylex.h lex_automaton.h executions.h experiment.h
	$(CC) $< -lm -lgccjit -o $@

ast: ast.c syn_tables.h my_yylex.h lex_automaton.h executions.h experiment.h
	$(CC) $< -lm -o $@

libjitparser: libjitparser.c syn_tables.h my_yylex.h lex_automaton.h executions.h experiment.h
	gcc $< -ljit -lpthread -lm -ldl -o $@

llvm.o: llvm.c
	clang $< -g `llvm-config --cflags` -c $<

llvm: llvm.o
	clang++ $< `llvm-config --cxxflags --ldflags --libs core executionengine mcjit interpreter analysis native bitwriter --system-libs` -o $@


syn_tables.h: GT
	./$< > $@

GT: gen_tables.c grammar.h
	$(CC) $< -o $@

grammar.h: PG grammar.txt
	./$< < $(word 2, $^) > $@

PG: parse_grammar.c
	$(CC) $< -o $@


lex_automaton.h: BLA
	./$< > $@

BLA: build_lex_autom.c lex_sequence.h grammar.h
	$(CC) $< -o $@

lex_sequence.h: PLR lex_rules.txt
	./$< < $(word 2, $^) > $@

PLR: parse_lex_rules.c
	$(CC) $< -o $@


executions.h: BE grammar.txt
	./$< < $(word 2, $^) > $@

BE: build_executions.c syn_tables.h
	$(CC) $< -o $@


clean:
	rm -f PG grammar.h GT syn_tables.h
	rm -f PLR lex_sequence.h BLA lex_automaton.h
	rm -f BE executions.h
	rm -f output.txt
