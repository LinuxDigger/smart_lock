CC = gcc
CPP = g++
INCLUDE  = -I/usr/local/openssl/include/openssl
LIB = -Wl,-dn -L/usr/local/openssl/lib -lssl -lcrypto -Wl,-dy -ldl -lm -lpthread


all:test rsa_test

test:test.o
	$(CPP) -o $@ $^ $(LIB)
test.o:test.cpp
	$(CPP) -g $(INCLUDE) -c -o $@ $^

rsa_test:rsa_test.o rsa_aes.o
	$(CC) -o $@ $^ $(LIB)

rsa_test.o:rsa_test.c
	$(CC) -g $(INCLUDE) -c -o $@ $^

rsa_aes.o:rsa_aes.c
	$(CC) -g $(INCLUDE) -c -o $@ $^

clean:
	rm -f *.o test rsa_test credit
