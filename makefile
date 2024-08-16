CC = g++
CFLAGS = -Wall -Wextra -std=c++20

EXEC = server client

CLASSES = ./src/server_connection.o ./src/client_connection.o ./src/utils.o ./src/header.o ./src/match_info.o ./src/domes_library.o ./src/game.o ./src/action.o
SOBJS = ./src/server.o 
COBJS = ./src/client.o 
TESTS = ./tests/tests.o ./tests/game_tests.o ./tests/tests_librarys.o ./tests/action_tests.o 

all: $(EXEC)
	./server


server:  $(CLASSES) $(SOBJS)
	$(CC) $(CFLAGS) $^ -o $@ 

client: $(CLASSES) $(COBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS_CLIENT)

./src/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(CLASSES) $(TESTS)
	$(CC) $(CFLAGS) $^ -o $@
	./test


clean:
	rm -f $(EXEC) $(SOBJS) $(COBJS) $(TESTS) $(CLASSES)

