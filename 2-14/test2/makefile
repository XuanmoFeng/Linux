clent=Clent.c
server=Server.c
cc=gcc
.PHONY:all
all:clent server
clent:$(clent)
	$(cc) -o clent $(clent)
server:$(server)
	$(cc) -o server $(server)
.PHONY:clean
clean:
	rm clent server
clef:
	rm myfifo
