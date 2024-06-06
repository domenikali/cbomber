# c bomber
this is a little project to learn c++ coming from c

## protocol
the game protocol is the following (still not complete)

### 1
&emsp;client connect to server and send packet with a request to join the queue in a specifig game mode

### 2
&emsp;server add player in the queue of the requested mode then respond with a packet to confirm request accepted or denied

### 3
&emsp;once the queue is full the server send game info to client

### 4 
&emsp;client respond to confirm it has recived the information and it's still running

### 5 
&emsp;server multidiffuse grid information and the game can start

(continue)

## packets structure

### Header
16 bits packet:
 - code is first 13 bit [0:8191]
 - id is the following 2
 - team is the remaining 1

<pre>
 0                   1
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|            code         |id |t|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
</pre>

### Match info
22 byte packet:
 - 16 bit header 
    - code = 0, id = of the player, team = of the player (all 0 if free4all)
 - 16 bit udp port
 - 16 bit multicast port
 - 16 X 8 bit ipv6 multicast adress

<pre>
 0                   1
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|            code         |id |t|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|          udp port             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|       multicast port          |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     ip[0]   |     ....
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
</pre>

code is:
  - status
    - 0 request accepted / no errors
    - 1 generic error stop execution

  - game request [1:9]
    - 2 for single player
    - 3 for team match
    - remaining reserved

  - game action [10:20]
    - 10 player death
    - 11 player won
    - 12 player lost a life
    - remaining reserved 

  - \> 100 describing packet number

(continue)

