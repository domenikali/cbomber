# c bomber
this is a little project to learn c++ coming from c

## protocol
the game protocol is the following (still not complete)

### 1
client connect to server and send packet with a request to join the queue in a specifig gmae mode

### 2
server respond with a packet to confirm request accepted or denied

### 3
server send game info to client

### 4 
client respond to confirm it has recived the information and it's still running

### 5 
server multidiffuse grid information and the game can start

(continue)

## packets structure

### Header
16 bits packet
code is first 13 bit
id is the following 2
team is the remaining 1


                    1
                    
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5

+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

|        code           |id |t|

+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

code is:
  - status
    - 0 request accepted / no errors
    - 1 generic error stop execution

  - game request
    - 2 for single player
    - 3 for team match
    - 4 reserved (coming)
    - 5 reserved (coming)

(continue)

