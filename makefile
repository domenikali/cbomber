CC = g++
CFLAGS = -Wall -Wextra -std=c++20

EXEC = server client

SOBJS = ./src/server.o ./src/server_connection.o  ./src/utils.o ./src/header.o ./src/match_info.o ./src/domes_library.o
COBJS = ./src/client.o ./src/client_connection.o ./src/utils.o ./src/header.o ./src/match_info.o ./src/domes_library.o

all: $(EXEC)


server: $(SOBJS)
	$(CC) $(CFLAGS) $^ -o $@ 

client: $(COBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS_CLIENT)

./src/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(SOBJS) $(COBJS)

