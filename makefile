build:
	gcc ./src/*.c -I ./includes -o srv -lcrypto -lssl
clean:
	rm srv