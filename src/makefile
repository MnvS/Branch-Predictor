CC=g++
OPTS=-g

all: main.o traceread.o predictor21264.o
	$(CC) $(OPTS) -lm -o predictor main.o traceread.o predictor21264.o

main.o: main.C traceread.h predictor.h
	$(CC) $(OPTS) -c main.C

traceread.o: traceread.h traceread.C
	$(CC) $(OPTS) -c traceread.C

predictor21264.o: predictor21264.h predictor21264.C
	$(CC) $(OPTS) -c predictor21264.C

clean:
	rm -f *.o predictor;
