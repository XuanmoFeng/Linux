clent=clent
server=server
cc=gcc
cleSrc=clent.c
serSrc=server.c
commSrc=comm.c
.PHONY:all
all:$(clent) $(server)
$(clent):$(cleSrc) $(commSrc)
	$(cc) -g -o $@ $^
$(server):$(serSrc) $(commSrc)
	$(cc) -g -o $@ $^
.PHONY:clean
clean:
	rm $(clent) $(server)
