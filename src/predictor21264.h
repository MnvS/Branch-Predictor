#ifndef PREDICTOR21264_H
#define PREDICTOR21264_H

/*
  Define all your tables and their sizes here.
  All tables must be statically-sized.
  Please don't call malloc () or any of its relatives within your
  program.  The predictor will have a budget, namely (64K + 256) bits
  (not bytes).  That encompasses all storage (all tables, plus GHR, if
  necessary -- but not PC) used for the predictor.  That may not be
  the amount of storage your predictor uses, however -- for example,
  you may implement 2-bit predictors with a table of ints, in which
  case the simulator will use more memory -- that's okay, we're only
  concerned about the memory used by the simulated branch predictor.
*/

//Create 10-bit sizes for entries on the local history table
typedef struct localEntry {
	unsigned int entry:10;
} lEntry;

//Create 1024 entries for local history table
typedef struct localHistory {
	lEntry table[1024];
} localTable;

//Create 3-bit sizes for prediction table entries
typedef struct predictEntry {
	unsigned int entry:3;
} pEntry;

//Create 1024 entries for local prediction table
typedef struct localPredict {
	pEntry table[1024];
} predictionTable;

//Create Global History Table
typedef struct globalHistory {
	unsigned int history:12;
} globalTable;

//Create entry sizes for the global prediction table and the chooser prediction table
typedef struct globalEntry {
	unsigned int entry:2;
} gEntry;

//Create Global Prediction Table
typedef struct globalPrediction {
	gEntry table[4096];
} gPredictionTable;

//Create Chooser Prediction table
typedef struct predictionTable {
	gEntry table[4096];
}


/*
  Initialize the predictor.
*/
void init_predictor ();

/*
  Make a prediction for conditional branch instruction at PC 'pc'.
  Returning true indicates a prediction of taken; returning false
  indicates a prediction of not taken.
*/
bool make_prediction (unsigned int pc);

/*
  Train the predictor the last executed branch at PC 'pc' and with
  outcome 'outcome' (true indicates that the branch was taken, false
  indicates that the branch was not taken).
*/
void train_predictor (unsigned int pc, bool outcome);

#endif
