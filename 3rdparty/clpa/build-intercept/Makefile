all: libintercept.so intercept-run

libintercept.so: intercept.c
	$(CC) -fPIC -shared -Wall -g intercept.c -o libintercept.so -ldl 

intercept-run: intercept-run.c
	$(CC) -o intercept-run intercept-run.c

clean:
	-rm -f *.o *.so intercept-run
