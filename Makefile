CC=gcc

OS=page_replacement

$(OS) : page_replacement.c
	$(CC) -o $@ $^

clean :
	rm -rf *.o
	rm -rf $(OS)