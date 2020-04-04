CC = gcc
CFLAGS = -g -Wall -Werror

vector: vector.c
	$(CC) $(CFLAGS) -o $@ $< -lm

test: test.o bitcpy.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

perf:
	sudo perf stat -e branch-instructions,branch-misses ./test

plot:
	sh do_measurement.sh > /dev/null

clean:
	rm -f *.o test