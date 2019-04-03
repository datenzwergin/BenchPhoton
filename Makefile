CC=gcc
# -std=c99 -Wall -Wextra -Wshadow -fsanitize=address,undefined -O2
CFLAGS=-Wall -Wextra -Wshadow --std=c99 -O3 -D_PHOTON80_
LDFLAGS=-lm
SRC=ref/photon.h ref/photon.c bench.c
BIN=bench bench-opt random.data

all:		$(BIN)

bench:		$(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o bench

bench-opt:	$(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o bench-opt -D_TABLE_

random.data:
	echo "The PHOTON Lightweight Hash Functions Family" > random.data
	cat random.data.raw >> random.data

clean:
	rm -f *.o $(BIN)

format:
	clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4}" \
	-i bench.c
