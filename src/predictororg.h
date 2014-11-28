#ifndef PREDICTORORG_H
#define PREDICTORORG_H

#define GLOBAL_MASK 16383

struct gtable {
	unsigned val : 14;
} ;

struct btable {
	unsigned counter : 2;
};

/*
  Initialize the predictor.
*/
void init_predictor();

/*
  Make a prediction for conditional branch instruction at PC 'pc'.
  Returning true indicates a prediction of taken; returning false
  indicates a prediction of not taken.
*/
bool make_prediction(unsigned int pc);

/*
  Train the predictor the last executed branch at PC 'pc' and with
  outcome 'outcome' (true indicates that the branch was taken, false
  indicates that the branch was not taken).
*/
void train_predictor(unsigned int pc, bool outcome);

#endif
