#include "predictor21264.h"

localTable localHistory;
predictionTable localPrediction;

gPredictionTable globalPrediction;
chooserTable cPredictionTable;

//Initializes Predictor by setting all table values to 0
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
//Makes a prediction based upon a tournament of a global and local history
bool make_prediction (unsigned int pc)
{
	//Retrieve lowest 10 bits from PC
	unsigned int bitMask = 0x3FF;
	unsigned short index = pc & bitMask;
	unsigned short historyIndex = globalHistory & 0xFFF;
	//printf("PC: %u Index: %hu\n", pc, index);
	//Determine to use global or local predictors
	if (cPredictionTable.table[historyIndex] <= 1) {
		//Use Local Table
		return local_prediction(index);
	} else {
		//Use Global Table
		return global_prediction();
	}
  return false;
}

//Trains the predictor with most recent branch outcome
void train_predictor (unsigned int pc, bool outcome)
{
	unsigned int bitMask = 0x3FF;
	unsigned short index = pc & bitMask;	
	update_chooser(index, outcome);
	update_local_predictor(index, outcome);
	update_global_predictor(outcome);	

}

void update_chooser(unsigned short index, bool outcome) {
	//Get prediction of local and global predictors
	bool localChoice = local_prediction(index);
	bool globalChoice = global_prediction();
	unsigned short historyIndex = globalHistory & 0xFFF;
	//Cross check choices to actual outcome
	if (localChoice == outcome && globalChoice != outcome) {
		//Local Choice was correct
		if (cPredictionTable.table[historyIndex] > 0)
			cPredictionTable.table[historyIndex]--;
	} else if (localChoice != outcome && globalChoice == outcome) {
		//Global Choice was correct
		if (cPredictionTable.table[historyIndex] < 3)
			cPredictionTable.table[historyIndex]++;
	}
}


bool local_prediction(unsigned short index) {
	unsigned short predictIndex;
	//Retrieve 10-bit local history and generate prediction index
	predictIndex = localHistory.table[index] & 0x3FF;
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
	unsigned short predictIndex = localHistory.table[index] & 0x3FF;
	unsigned short prediction = localPrediction.table[predictIndex] & 7;
	//Ensure that saturation values remain in defined domains (0-3)
	/*if (prediction >= 0 && prediction < 7) {
		if (outcome) {
			//Outcome was taken so increment local prediction saturation
			localPrediction.table[predictIndex]++;
		} else {
			//Outcome was not taken so decrement local prediction saturation
			localPrediction.table[predictIndex]--;
		}
	}*/
	if (outcome) {
		if (prediction < 7)
			localPrediction.table[predictIndex]++;
	} else {
		if (prediction > 0)
			localPrediction.table[predictIndex]--;
	}

	//Update Local History
	//Shift history to push last outcome
	localHistory.table[index] = (localHistory.table[index]) << 1;
	if (outcome) {
		//If outcome was true, set history bit
		localHistory.table[index]++;
	}
}

/*
 * 
 */
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

void update_global_predictor (bool outcome) {
	//TODO Update global predictor
	globalHistory = globalHistory << 1;
	if (outcome)
		globalHistory++;
}
