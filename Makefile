CC = gcc
CFLAGS = -g -Wall -Werror

vector: vector.c
	$(CC) -o $@ $<

test: test.o bitcpy.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAG) -o $@ -c $<

perf:
	sudo perf stat -e branch-instructions,branch-misses ./test

plot:
	sh do_measurement.sh > /dev/null

clean:
	rm -f *.o test