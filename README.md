CSE331 Lab Project 3 Dynamic Branch Predictors
----------------------------------------------------------------------

Instructions:

1) Make the predictor (run make in your working source directory).

2) Run the predictor
(bunzip2 -c -k ../traces/DIST-INT-1.bz2 |./predictor)
where DIST-INT-1.bz is one of the trace files.
./predictor reads (in a binary format) from STDIN a trace
(decompressed with bzip2 on the fly). It outputs to STDOUT basic
statistics about how well the predictor did.

4) Create your own predictor.C file and predictor.h file (or modify
the existing ones).  Be sure to read the comment at the beginning
of the provided predictor.h and follow it's directions.  Just make
sure your predictor implements the three functions exactly as their
specification reads (init_predictor, make_prediction, and
train_predictor).  The only two files of yours you will turn in are
predictor.h and predictor.C (renaming the files after the testing 
is done to predictorg.c and predictorg.h for gshare or predictor21264.c 
and predictor21264.hfor Alpha21264 for submission). All other source 
files (and makefile) will remain the same.

5) Submit your two executable and four source files along with your
report (details of this specified in project description).  Upload the
tar ball in Moodle.

