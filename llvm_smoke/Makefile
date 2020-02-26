CC=clang
CFLAGS=-g `llvm-config --cflags`
LD=clang++
LDFLAGS=`llvm-config --cxxflags --ldflags --libs core executionengine mcjit interpreter analysis native bitwriter --system-libs`

all: sum

sum.o: sum.c
	clang $< -g `llvm-config --cflags` -c $<

sum: sum.o
	clang++ $< `llvm-config --cxxflags --ldflags --libs core executionengine mcjit interpreter analysis native bitwriter --system-libs` -o $@

#\
sum.o: sum.c\
	$(CC) $(CFLAGS) -c $<\
\
sum: sum.o\
	$(LD) $< $(LDFLAGS) -o $@\
\
sum.bc: sum\
	./sum 0 0\
\
sum.ll: sum.bc\
	llvm-dis $<\
\
clean:\
	-rm -f sum.o sum sum.bc sum.ll\
