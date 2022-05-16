build:
	gcc ./src/*.c -I ./includes -o srv -lcrypto -lssl -lpthread
clean:
	rm srv