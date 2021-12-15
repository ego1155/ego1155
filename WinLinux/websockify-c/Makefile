TARGETS=websockify
CFLAGS += -fPIC

all: $(TARGETS)

websockify: websockify.o websocket.o
	$(CC) $(LDFLAGS) -static -m64 -no-pie -s -W -Wall -Wextra -Os $^ -lssl -lcrypto -lWs2_32 -lwsock32 -o $@

websocket.o: websocket.c websocket.h
websockify.o: websockify.c websocket.h

clean:
	rm -f websockify *.o

