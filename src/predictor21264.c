// A very stupid predictor.  It will always predict not taken.
#include "predictor21264.h"

localTable localHistory;
predictionTable localPrediction;

gPredictionTable globalPrediction;
chooserTable cPredictionTable;

void init_predictor ()
{
	int i;
	globalHistory = 3;
	for (i = 0; i < 1024; i++) {
		localHistory.table[i] = 0;
		localPrediction.table[i] = 0;
		globalPrediction.table[i] = 0;
		cPredictionTable.table[i] = 0;
	}
	for (; i < 4096; i++) {
		globalPrediction.table[i] = 0;
		cPredictionTable.table[i] = 0;
	}
	//printf("Successfully set everything to 0\n");
}

bool make_prediction (unsigned int pc)
{
	//Retrieve lowest 10 bits from PC
	unsigned int bitMask = 0x3FF;
	unsigned short index = pc & bitMask;
	printf("PC: %u Index: %hu\n", pc, index);
	//Determine to use global or local predictors
	if (cPredictionTable.table[index] <= 1) {
		//Use Local Table
		return local_prediction(index);
	} else {
		//Use Global Table
	}
  return false;
}

void train_predictor (unsigned int pc, bool outcome)
{	
	if (outcome == false) {

	} else if (outcome == true) {

	}
}


bool local_prediction(unsigned short index) {
	unsigned short predictIndex;
	//Retrieve 10-bit local history and generate prediction index
	predictIndex = localHistory.table[index];
	//Determine if branch is taken or not
	if (localPrediction.table[predictIndex] < 4) {
		//Assume not taken
		return false;
	} else {
		//Assume taken
		return true;
	}
}

void update_local_predictor (unsigned short index, bool outcome) {
	//Update Prediction Table
	unsigned short predictIndex = localHistory.table[index];
	unsigned short prediction = localPrediction.table[predictIndex];
	//Ensure that saturation values remain in defined domains (0-3)
	if (prediction > 0 && prediction < 3) {
		if (outcome) {
			//Outcome was taken so increment local prediction saturation
			localPrediction.table[predictIndex]++;
		} else {
			//Outcome was not taken so decrement local prediction saturation
			localPrediction.table[predictIndex]--;
		}
	}

	//Update Local History
	//Shift history to push last outcome
	localHistory.table[index] = (localHistory.table[index]) << 1;
	if (outcome) {
		//If outcome was true, set history bit
		localHistory.table[index]++;
	}
}

bool global_prediction () {
	//Create index from 12 bit history
	unsigned int index = globalHistory & 0xFFF;
	//Retrieve saturation counter
	if (globalPrediction.table[index] <= 1) {
		//Not taken
		return false;
	} else {
		return true;
	}
}

void update_global_predictor () {
	//TODO Update global predictor
}
