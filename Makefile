CC = g++
OBJ = TicTacToe.o

TicTacToe: $(OBJ)
	$(CC) -o $@ $^
%.o: %.cxx
	$(CC) -c -o $@ $^
clean:
	rm *.o TicTacToe
