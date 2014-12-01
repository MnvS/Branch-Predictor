CC=g++
OPTS=-g

all: predictor21264 predictororg

predictor21264: main.o traceread.o predictor21264.o
	$(CC) $(OPTS) -lm -o predictor21264 main.o traceread.o predictor21264.o

predictororg: main.o traceread.o predictororg.o
	$(CC) $(OPTS) -lm -o predictororg main.o traceread.o predictororg.o

traceread.o: traceread.h traceread.C
	$(CC) $(OPTS) -c traceread.C

predictor21264.o: predictor21264.h predictor21264.c
	$(CC) $(OPTS) -c predictor21264.c

predictororg.o: predictororg.h predictororg.C
	$(CC) $(OPTS) -c predictororg.C
	
clean:
	rm -f *.o predictororg predictor21264;
