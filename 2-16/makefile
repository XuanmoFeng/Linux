server=server
cc=gcc
serSrc=server.c comm.c

.PHONY:all
all:$(server)
$(server):$(serSrc)
	$(cc) -g -o $@ $^

.PHONY:clean
clean:
	rm $(server)
