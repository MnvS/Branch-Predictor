#include "predictor21264.h"

//These tables are for the global and choosing predictors
gPredictionTable globalPrediction;
chooserTable cPredictionTable;

//Initializes Predictor by setting all table values to 0
void init_predictor ()
{
	int i;
	//Set Global History to 0
	globalHistory.history = 0;
	//Set all table entries to 0
	for (i = 0; i < 1024; i++) {
		globalPrediction.table[i] = 0;
		cPredictionTable.table[i] = 0;

		//Bit fields
		localHist[i].entry = 0;
		localPredict[i].entry = 0;
	}
	//Continue setting larger tables to 0
	for (; i < 4096; i++) {
		globalPrediction.table[i] = 0;
		cPredictionTable.table[i] = 0;
	}
}
//Makes a prediction based upon a tournament of a global and local history
bool make_prediction (unsigned int pc)
{
	//Retrieve lowest 10 bits from PC
	unsigned int bitMask = 0x3FF;
	unsigned short index = pc & bitMask;
	unsigned short historyIndex = globalHistory.history;
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
	//Extract lowest 10 bits of PC for indexing
	unsigned short index = pc & bitMask;	
	//Update Predictors
	update_chooser(index, outcome);
	update_local_predictor(index, outcome);
	update_global_predictor(outcome);	

}

/*
 * This function updates the chooser table
 */
void update_chooser(unsigned short index, bool outcome) {
	//Get last prediction of local and global predictors
	bool localChoice = local_prediction(index);
	bool globalChoice = global_prediction();
	//Obtain the History Index (to find the correct Choosing table member)
	unsigned short historyIndex = globalHistory.history;
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

/*
 * This function makes a local prediction
 */
bool local_prediction(unsigned short index) {
	unsigned short predictIndex;
	//Retrieve 10-bit local history and generate prediction index
	predictIndex = localHist[index].entry;
	//Determine if branch is taken or not by looking at the Local Prediction saturation
	if (localPredict[predictIndex].entry < 4) {
		//Assume not taken
		return false;
	}
	//Assume taken
	return true;
	
}

/*
 * This function updates the local predictor table
 */
void update_local_predictor (unsigned short index, bool outcome) {
	//Update Prediction Table
	unsigned short predictIndex = localHist[index].entry; //Gets the Index to be used in the Local Prediction table
	unsigned short prediction = localPredict[predictIndex].entry; //Gets the prediction saturation count
	//If outcome is true then add 1 to local saturation, decrement if otherwise
	if (outcome) {
		if (prediction < 7)
			localPredict[predictIndex].entry++;
	} else {
		if (prediction > 0)
			localPredict[predictIndex].entry--;
	}
	//Update Local History
	//Shift history to push last outcome
	
	localHist[index].entry = (localHist[index].entry) << 1;
	if (outcome) {
		localHist[index].entry++;
	}
}

/*
 * This function makes a global prediction
 */
bool global_prediction () {
	//Create index from 12 bit history
	unsigned int index = globalHistory.history;
	//Retrieve saturation counter
	if (globalPrediction.table[index] <= 1) {
		//Not taken
		return false;
	} else {
		return true;
	}
}

/*
 * This function updates the global predictor
 */
void update_global_predictor (bool outcome) {
	//Left shift global history
	globalHistory.history = globalHistory.history << 1;
	//Flip the newest bit if outcome was true
	if (outcome)
		globalHistory.history++;
}
